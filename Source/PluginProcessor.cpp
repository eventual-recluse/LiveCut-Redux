/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LiveCutAudioProcessor::LiveCutAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
                        , apvts(*this, nullptr, "Parameters", addParameters())
                        , bbcutter(player)
                        , oldpositionInMeasure(0)
#endif
{
    apvts.state = juce::ValueTree("Parameters");
    bbcutter.RegisterListener(&crusher);
    bbcutter.RegisterListener(&comb);
    comb.SetOn(false);
    crusher.SetOn(false);
    registerParameterListeners();
    updateAllParameters();
}

LiveCutAudioProcessor::~LiveCutAudioProcessor()
{
}

//==============================================================================
const juce::String LiveCutAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LiveCutAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LiveCutAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LiveCutAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LiveCutAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LiveCutAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LiveCutAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LiveCutAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LiveCutAudioProcessor::getProgramName (int index)
{
    return {};
}

void LiveCutAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LiveCutAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    crusher.SetSampleRate(sampleRate);
    comb.SetSampleRate(sampleRate);
    updateAllParameters();
    // TODO Set minfreq and maxfreq ranges from sampleRate?
    //minfreq.range(100.f, sampleRate);
    //maxfreq.range(100.f, sampleRate);
}

void LiveCutAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LiveCutAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
  #endif
}
#endif

void LiveCutAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    uint64_t size = buffer.getNumSamples();
    int64_t div = subdivChoices[static_cast<int32_t>(*apvts.getRawParameterValue("subdiv"))];
  
    AudioPlayHead* playHead = getPlayHead();
    if(!playHead) return;
      
    juce::Optional<juce::AudioPlayHead::PositionInfo> info = playHead->getPosition();
    juce::Optional<juce::AudioPlayHead::TimeSignature> timeSig = *info->getTimeSignature();
    
    // The denomitor seems to instantiate with a junk value, which crashes the standalone version of the plugin.
    // However, if the DAW sets the denomitor value, there is no problem
    double samplePos = static_cast<double>(*info->getTimeInSamples());  // current location
    double sampleRate = getSampleRate();
    double ppqPos = *info->getPpqPosition();    // 1 ppq
    double tempo = *info->getBpm();        // in bpm
    double numerator = static_cast<double>(timeSig->numerator);  // time signature
    double denominator = static_cast<double>(timeSig->denominator);
    double ppqduration = (static_cast<double>(size)/sampleRate) * (tempo/60.0); //duration of the block
    double divPerSample = (static_cast<double>(div)/static_cast<double>(numerator))*ppqduration*(denominator/4.0)/static_cast<double>(size);
    double position = (static_cast<double>(div)/static_cast<double>(numerator)) * ppqPos * (denominator/4.0);
    double ref = 0.0;

    bbcutter.SetTimeInfos(tempo, numerator, denominator, sampleRate);

    int64_t oldmeasure = static_cast<int64_t>(std::floor((position-ref)/div));
    int64_t positionInMeasure = static_cast<int64_t>(std::floor(std::fmod(position-ref, div)));
        
    if (positionInMeasure != oldpositionInMeasure)
    {
        oldpositionInMeasure = positionInMeasure;
        bbcutter.SetPosition(oldmeasure, oldpositionInMeasure);
    }
  
    for(int64_t i=0; i<size; i++)
    {
        positionInMeasure = static_cast<int64_t>(std::floor(std::fmod(position-ref, div)));
        int64_t measure = static_cast<int64_t>(std::floor((position-ref)/div));
        
        if(positionInMeasure!=oldpositionInMeasure)
        {
            bbcutter.SetPosition(measure,positionInMeasure);
        }
        
        // Handle stereo or mono. Handling of mono is included so that
        // LiveCut doesn't crash the DAW if loaded into a mono track,
        // but otherwise, LiveCut is not designed for mono.
        if (totalNumInputChannels > 1)
        {
            float l=0.f;
            float r=0.f;
            player.tick(l,r,buffer.getSample(0, i),buffer.getSample(1, i));
            crusher.tick(l,r,l,r);
            comb.tick(l,r,l,r);
            buffer.setSample(0, i, l);
            buffer.setSample(1, i, r);
        }
        else if (totalNumInputChannels == 1)
        {
            float l=0.f;
            float r=0.f;
            player.tick(l,r,buffer.getSample(0, i),buffer.getSample(0, i));
            crusher.tick(l,r,l,r);
            comb.tick(l,r,l,r);
            buffer.setSample(0, i, (l+r) / 2.0f);
        }
        
        oldpositionInMeasure = positionInMeasure;
        oldmeasure           = measure;
        position            += divPerSample;
    }
}

//==============================================================================
bool LiveCutAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LiveCutAudioProcessor::createEditor()
{
    return new LiveCutAudioProcessorEditor (*this);
}

//==============================================================================
void LiveCutAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LiveCutAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

AudioProcessorValueTreeState& LiveCutAudioProcessor::getApvts()
{
    return apvts;
}

juce::AudioProcessorValueTreeState::ParameterLayout LiveCutAudioProcessor::addParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout paramLayout;

    paramLayout.add(std::make_unique<juce::AudioParameterChoice>("cutproc", "CutProc", juce::StringArray {"CUTPROC11", "WARPCUT", "SQPUSHER"}, 0));
    paramLayout.add(std::make_unique<juce::AudioParameterChoice>("subdiv", "SubDiv", juce::StringArray {"6", "8", "12", "16", "18", "24", "32"}, 1));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("fade", "Fade", juce::NormalisableRange<float>(0.0f, 100.0f, 0.0000001f, 0.231378f), 0.0f)); // LOGARITHMIC - NOTE 0.231378f is the skew factor, which sets 5.0 as the slider middle value.
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minamp", "Min Amp", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxamp", "Max Amp", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minpan", "Min Pan", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), -0.2f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxpan", "Max Pan", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.2f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minpitch", "Min Pitch", juce::NormalisableRange<float>(-2400.0f, 2400.0f, 1.0f), 0.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxpitch", "Max Pitch", juce::NormalisableRange<float>(-2400.0f, 2400.0f, 1.0f), 0.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("duty", "Duty", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("fillduty", "Fill Duty", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxphrs", "Max Phrase", juce::NormalisableRange<float>(1.0f, 8.0f, 1.0f), 4.0f)); // INTEGER
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minphrs", "Min Phrase", juce::NormalisableRange<float>(1.0f, 8.0f, 1.0f), 1.0f)); // INTEGER
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxrep", "CutProc11 Max Rep", juce::NormalisableRange<float>(0.0f, 4.0f, 1.0f), 1.0f)); // INTEGER
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minrep", "CutProc11 Min Rep", juce::NormalisableRange<float>(0.0f, 4.0f, 1.0f), 0.0f)); // INTEGER
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("stutter", "CutProc11 Stutter", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.8f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("area", "CutProc11 Area", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("straight", "Warpcut Straight", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.3f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("regular", "Warpcut Regular", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("ritard", "Warpcut Ritard", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("speed", "Warpcut Speed", juce::NormalisableRange<float>(0.5f, 0.999f, 0.001f), 0.9f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("activity", "SQPusher Activity", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    paramLayout.add(std::make_unique<juce::AudioParameterChoice>("crusher", "Crusher", juce::StringArray {"OFF", "ON"}, 0));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minbits", "Crusher Min Bits", 1.0f, 32.0f, 32.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxbits", "Crusher Max Bits", 1.0f, 32.0f, 32.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("minfreq", "Crusher Min Freq", juce::NormalisableRange<float>(441.0f, 44100.0f, 0.01f, 0.336317f), 44100.0f)); // LOGARITHMIC - NOTE 0.336317f is the skew factor, which sets 6000 as the slider middle value.
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxfreq", "Crusher Max Freq", juce::NormalisableRange<float>(441.0f, 44100.0f, 0.01f, 0.336317f), 44100.0f)); // LOGARITHMIC - NOTE 0.336317f is the skew factor, which sets 6000 as the slider middle value.
    paramLayout.add(std::make_unique<juce::AudioParameterChoice>("comb", "Comb", juce::StringArray {"OFF", "ON"}, 0));
    paramLayout.add(std::make_unique<juce::AudioParameterChoice>("type", "Comb Type", juce::StringArray {"FeedFwd", "FeedBack"}, 0));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("feedback", "Comb Feedback", juce::NormalisableRange<float>(0.0f, 0.9f, 0.001f), 0.5f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("mindelay", "Comb Min Delay", 1.0f, 50.0f, 10.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("maxdelay", "Comb Max Delay", 1.0f, 50.0f, 10.0f));
    paramLayout.add(std::make_unique<juce::AudioParameterFloat>("seed", "Seed", juce::NormalisableRange<float>(1.0f, 16.0f, 1.0f), 1.0f)); // INTEGER
    
    return paramLayout;
}

void LiveCutAudioProcessor::registerParameterListeners()
{
    apvts.addParameterListener("cutproc", this);
    apvts.addParameterListener("subdiv", this);
    apvts.addParameterListener("fade", this);
    apvts.addParameterListener("minamp", this);
    apvts.addParameterListener("maxamp", this);
    apvts.addParameterListener("minpan", this);
    apvts.addParameterListener("maxpan", this);
    apvts.addParameterListener("minpitch", this);
    apvts.addParameterListener("maxpitch", this);
    apvts.addParameterListener("duty", this);
    apvts.addParameterListener("fillduty", this);
    apvts.addParameterListener("maxphrs", this);
    apvts.addParameterListener("minphrs", this);
    apvts.addParameterListener("maxrep", this);
    apvts.addParameterListener("minrep", this);
    apvts.addParameterListener("stutter", this);
    apvts.addParameterListener("area", this);
    apvts.addParameterListener("straight", this);
    apvts.addParameterListener("regular", this);
    apvts.addParameterListener("ritard", this);
    apvts.addParameterListener("speed", this);
    apvts.addParameterListener("activity", this);
    apvts.addParameterListener("crusher", this);
    apvts.addParameterListener("minbits", this);
    apvts.addParameterListener("maxbits", this);
    apvts.addParameterListener("minfreq", this);
    apvts.addParameterListener("maxfreq", this);
    apvts.addParameterListener("comb", this);
    apvts.addParameterListener("type", this);
    apvts.addParameterListener("feedback", this);
    apvts.addParameterListener("mindelay", this);
    apvts.addParameterListener("maxdelay", this);
    apvts.addParameterListener("seed", this);
}

void LiveCutAudioProcessor::parameterChanged (const juce::String &parameterID, float newValue)
{
    if (parameterID == "cutproc") { bbcutter.SetCutProc(static_cast<long> (newValue)); }
    else if (parameterID == "subdiv") { bbcutter.SetSubdiv(subdivChoices[static_cast<int32_t>(newValue)]); }
    else if (parameterID == "fade") { bbcutter.SetFade(newValue); }
    else if (parameterID == "minamp") { bbcutter.SetMinAmp(newValue); }
    else if (parameterID == "maxamp") { bbcutter.SetMaxAmp(newValue); }
    else if (parameterID == "minpan") { bbcutter.SetMinPan(newValue); }
    else if (parameterID == "maxpan") { bbcutter.SetMaxPan(newValue); }
    else if (parameterID == "minpitch") { bbcutter.SetMinDetune(newValue); }
    else if (parameterID == "maxpitch") { bbcutter.SetMaxDetune(newValue); }
    else if (parameterID == "duty") { bbcutter.SetDutyCycle(newValue); }
    else if (parameterID == "fillduty") { bbcutter.SetFillDutyCycle(newValue); }
    else if (parameterID == "maxphrs") { bbcutter.SetMaxPhraseLength(static_cast<long> (newValue)); }
    else if (parameterID == "minphrs") { bbcutter.SetMinPhraseLength(static_cast<long> (newValue)); }
    else if (parameterID == "maxrep") { bbcutter.SetMaxRepeats(static_cast<long> (newValue)); }
    else if (parameterID == "minrep") { bbcutter.SetMinRepeats(static_cast<long> (newValue)); }
    else if (parameterID == "stutter") { bbcutter.SetStutterChance(newValue); }
    else if (parameterID == "area") { bbcutter.SetStutterArea(newValue); }
    else if (parameterID == "straight") { bbcutter.SetStraightChance(newValue); }
    else if (parameterID == "regular") { bbcutter.SetRegularChance(newValue); }
    else if (parameterID == "ritard") { bbcutter.SetRitardChance(newValue); }
    else if (parameterID == "speed") { bbcutter.SetAccel(newValue); }
    else if (parameterID == "activity") { bbcutter.SetActivity(newValue); }
    else if (parameterID == "crusher") { crusher.SetOn(static_cast<bool> (newValue)); }
    else if (parameterID == "minbits") { crusher.SetMinBits(newValue); }
    else if (parameterID == "maxbits") { crusher.SetMaxBits(newValue); }
    else if (parameterID == "minfreq") { crusher.SetMinFreq(newValue); }
    else if (parameterID == "maxfreq") { crusher.SetMaxFreq(newValue); }
    else if (parameterID == "comb") { comb.SetOn(static_cast<bool> (newValue)); }
    else if (parameterID == "type") { comb.SetType(static_cast<long> (newValue)); }
    else if (parameterID == "feedback") { comb.SetFeedBack(newValue); }
    else if (parameterID == "mindelay") { comb.SetMinDelay(newValue); }
    else if (parameterID == "maxdelay") { comb.SetMaxDelay(newValue); }
    else if (parameterID == "seed") { Math::randomseed(static_cast<long> (newValue)); }     
}

void LiveCutAudioProcessor::updateAllParameters()
{
    bbcutter.SetCutProc(static_cast<long> (*apvts.getRawParameterValue("cutproc")));
    bbcutter.SetSubdiv(subdivChoices[static_cast<int32_t>(*apvts.getRawParameterValue("subdiv"))]);
    bbcutter.SetFade(*apvts.getRawParameterValue("fade"));
    bbcutter.SetMinAmp(*apvts.getRawParameterValue("minamp"));
    bbcutter.SetMaxAmp(*apvts.getRawParameterValue("maxamp"));
    bbcutter.SetMinPan(*apvts.getRawParameterValue("minpan"));
    bbcutter.SetMaxPan(*apvts.getRawParameterValue("maxpan"));
    bbcutter.SetMinDetune(*apvts.getRawParameterValue("minpitch"));
    bbcutter.SetMaxDetune(*apvts.getRawParameterValue("maxpitch"));
    bbcutter.SetDutyCycle(*apvts.getRawParameterValue("duty"));
    bbcutter.SetFillDutyCycle(*apvts.getRawParameterValue("fillduty"));
    bbcutter.SetMaxPhraseLength(static_cast<long> (*apvts.getRawParameterValue("maxphrs")));
    bbcutter.SetMinPhraseLength(static_cast<long> (*apvts.getRawParameterValue("minphrs")));
    bbcutter.SetMaxRepeats(static_cast<long> (*apvts.getRawParameterValue("maxrep")));
    bbcutter.SetMinRepeats(static_cast<long> (*apvts.getRawParameterValue("minrep")));
    bbcutter.SetStutterChance(*apvts.getRawParameterValue("stutter"));
    bbcutter.SetStutterArea(*apvts.getRawParameterValue("area"));
    bbcutter.SetStraightChance(*apvts.getRawParameterValue("straight"));
    bbcutter.SetRegularChance(*apvts.getRawParameterValue("regular"));
    bbcutter.SetRitardChance(*apvts.getRawParameterValue("ritard"));
    bbcutter.SetAccel(*apvts.getRawParameterValue("speed"));
    bbcutter.SetActivity(*apvts.getRawParameterValue("activity"));
    crusher.SetOn(static_cast<bool> (*apvts.getRawParameterValue("crusher")));
    crusher.SetMinBits(*apvts.getRawParameterValue("minbits"));
    crusher.SetMaxBits(*apvts.getRawParameterValue("maxbits"));
    crusher.SetMinFreq(*apvts.getRawParameterValue("minfreq"));
    crusher.SetMaxFreq(*apvts.getRawParameterValue("maxfreq"));
    comb.SetOn(static_cast<bool> (*apvts.getRawParameterValue("comb")));
    comb.SetType(static_cast<long> (*apvts.getRawParameterValue("type")));
    comb.SetFeedBack(*apvts.getRawParameterValue("feedback"));
    comb.SetMinDelay(*apvts.getRawParameterValue("mindelay"));
    comb.SetMaxDelay(*apvts.getRawParameterValue("maxdelay"));
    Math::randomseed(static_cast<long> (*apvts.getRawParameterValue("seed")));
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LiveCutAudioProcessor();
}
