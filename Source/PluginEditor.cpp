/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LiveCutAudioProcessorEditor::LiveCutAudioProcessorEditor (LiveCutAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (2100 * scaleFactor, 1400 * scaleFactor);
    
    cutprocStepper.setTitle("CUTPROC");
    cutprocStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    cutprocStepper.setScale(scaleFactor);
    cutprocStepper.setDisplayChoiceText(true);
    cutprocStepper.setChoices(juce::StringArray {"CUTPROC11", "WARPCUT", "SQPUSHER"});
    addAndMakeVisible(&cutprocStepper);
    
    subdivStepper.setTitle("SUBDIV");
    subdivStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    subdivStepper.setScale(scaleFactor);
    subdivStepper.setDisplayChoiceText(true);
    subdivStepper.setChoices(juce::StringArray {"6", "8", "12", "16", "18", "24", "32"});
    addAndMakeVisible(&subdivStepper);
    
    fadeSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    fadeSlider.setScale(scaleFactor);
    fadeSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    fadeSlider.setTitle("FADE");
    fadeSlider.setUnitText("MS");
    addAndMakeVisible(&fadeSlider); // LOGARITHMIC
    
    minampSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    minampSlider.setScale(scaleFactor);
    minampSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minampSlider.setTitle("MINAMP");
    addAndMakeVisible(&minampSlider);
    
    maxampSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxampSlider.setScale(scaleFactor);
    maxampSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxampSlider.setTitle("MAXAMP");
    addAndMakeVisible(&maxampSlider);
    
    minpanSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    minpanSlider.setScale(scaleFactor);
    minpanSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minpanSlider.setTitle("MINPAN");
    addAndMakeVisible(&minpanSlider);
    
    maxpanSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxpanSlider.setScale(scaleFactor);
    maxpanSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxpanSlider.setTitle("MAXPAN");
    addAndMakeVisible(&maxpanSlider);
    
    minpitchSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    minpitchSlider.setScale(scaleFactor);
    minpitchSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minpitchSlider.setTitle("MINPITCH");
    minpitchSlider.setUnitText("CEN");
    addAndMakeVisible(&minpitchSlider);
    
    maxpitchSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxpitchSlider.setScale(scaleFactor);
    maxpitchSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxpitchSlider.setTitle("MAXPITCH");
    maxpitchSlider.setUnitText("CEN");
    addAndMakeVisible(&maxpitchSlider);
    
    dutySlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    dutySlider.setScale(scaleFactor);
    dutySlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    dutySlider.setTitle("DUTY");
    addAndMakeVisible(&dutySlider);
    
    filldutySlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    filldutySlider.setScale(scaleFactor);
    filldutySlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    filldutySlider.setTitle("FILLDUTY");
    addAndMakeVisible(&filldutySlider);
    
    maxphrsStepper.setScale(scaleFactor);
    maxphrsStepper.setTitle("MAXPHRS");
    maxphrsStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxphrsStepper.setUnitText("BAR");
    maxphrsStepper.setDisplayChoiceText(false);
    addAndMakeVisible(&maxphrsStepper);
    
    minphrsStepper.setTitle("MINPHRS");
    minphrsStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minphrsStepper.setScale(scaleFactor);
    minphrsStepper.setUnitText("BAR");
    minphrsStepper.setDisplayChoiceText(false);
    addAndMakeVisible(&minphrsStepper);
    
    maxrepStepper.setTitle("MAXREP");
    maxrepStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxrepStepper.setScale(scaleFactor);
    maxrepStepper.setUnitText("REP");
    maxrepStepper.setDisplayChoiceText(false);
    addAndMakeVisible(&maxrepStepper);
    
    minrepStepper.setTitle("MINREP");
    minrepStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minrepStepper.setUnitText("REP");
    minrepStepper.setDisplayChoiceText(false);
    minrepStepper.setScale(scaleFactor);
    addAndMakeVisible(&minrepStepper);
    
    stutterSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    stutterSlider.setScale(scaleFactor);
    stutterSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    stutterSlider.setTitle("STUTTER");
    addAndMakeVisible(&stutterSlider);
    
    areaSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    areaSlider.setScale(scaleFactor);
    areaSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    areaSlider.setTitle("AREA");
    addAndMakeVisible(&areaSlider);
    
    straightSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    straightSlider.setScale(scaleFactor);
    straightSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    straightSlider.setTitle("STRAIGHT");
    addAndMakeVisible(&straightSlider);
    
    regularSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    regularSlider.setScale(scaleFactor);
    regularSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    regularSlider.setTitle("REGULAR");
    addAndMakeVisible(&regularSlider);
    
    ritardSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    ritardSlider.setScale(scaleFactor);
    ritardSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    ritardSlider.setTitle("RITARD");
    addAndMakeVisible(&ritardSlider);
    
    speedSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    speedSlider.setScale(scaleFactor);
    speedSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    speedSlider.setTitle("SPEED");
    addAndMakeVisible(&speedSlider);
    
    activitySlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    activitySlider.setScale(scaleFactor);
    activitySlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    activitySlider.setTitle("ACTIVITY");
    addAndMakeVisible(&activitySlider);
    
    crusherSwitch.setTitle("CRUSHER");
    crusherSwitch.setScale(scaleFactor);
    crusherSwitch.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    addAndMakeVisible(&crusherSwitch);
    
    minbitsSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    minbitsSlider.setScale(scaleFactor);
    minbitsSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minbitsSlider.setTitle("MINBITS");
    minbitsSlider.setUnitText("BIT");
    addAndMakeVisible(&minbitsSlider);
    
    maxbitsSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxbitsSlider.setScale(scaleFactor);
    maxbitsSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxbitsSlider.setTitle("MAXBITS");
    maxbitsSlider.setUnitText("BIT");
    addAndMakeVisible(&maxbitsSlider);
    
    minfreqSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    minfreqSlider.setScale(scaleFactor);
    minfreqSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    minfreqSlider.setTitle("MINFREQ");
    minfreqSlider.setUnitText("HZ");
    addAndMakeVisible(&minfreqSlider); // LOGARITHMIC
    
    maxfreqSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxfreqSlider.setScale(scaleFactor);
    maxfreqSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxfreqSlider.setTitle("MAXFREQ");
    maxfreqSlider.setUnitText("HZ");
    addAndMakeVisible(&maxfreqSlider); // LOGARITHMIC
    
    combSwitch.setTitle("COMB");
    combSwitch.setScale(scaleFactor);
    combSwitch.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    addAndMakeVisible(&combSwitch);
    
    typeStepper.setTitle("TYPE");
    typeStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    typeStepper.setScale(scaleFactor);
    typeStepper.setDisplayChoiceText(true);
    typeStepper.setChoices(juce::StringArray {"FEEDFWD", "FEEDBACK"});
    addAndMakeVisible(&typeStepper);
    
    feedbackSlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    feedbackSlider.setScale(scaleFactor);
    feedbackSlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    feedbackSlider.setTitle("FEEDBACK");
    addAndMakeVisible(&feedbackSlider);
    
    mindelaySlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    mindelaySlider.setScale(scaleFactor);
    mindelaySlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    mindelaySlider.setTitle("MINDELAY");
    mindelaySlider.setUnitText("MS");
    addAndMakeVisible(&mindelaySlider);
    
    maxdelaySlider.xSlider.setLookAndFeel(&sliderLookAndFeel);
    maxdelaySlider.setScale(scaleFactor);
    maxdelaySlider.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    maxdelaySlider.setTitle("MAXDELAY");
    maxdelaySlider.setUnitText("MS");
    addAndMakeVisible(&maxdelaySlider);
    
    seedStepper.setTitle("SEED");
    seedStepper.setFont(juce::Font ( withDefaultMetrics (juce::FontOptions { varelaTypeface }) ));
    seedStepper.setScale(scaleFactor);
    seedStepper.setDisplayChoiceText(false);
    addAndMakeVisible(&seedStepper);
    
    
    // Widget parameter attachments
    cutprocStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "cutproc", cutprocStepper.xSlider);
    subdivStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "subdiv", subdivStepper.xSlider);
    fadeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "fade", fadeSlider.xSlider);
    minampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minamp", minampSlider.xSlider);
    maxampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxamp", maxampSlider.xSlider);
    minpanSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minpan", minpanSlider.xSlider);
    maxpanSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxpan", maxpanSlider.xSlider);
    minpitchSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minpitch", minpitchSlider.xSlider);
    maxpitchSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxpitch", maxpitchSlider.xSlider);
    dutySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "duty", dutySlider.xSlider);
    filldutySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "fillduty", filldutySlider.xSlider);
    maxphrsStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxphrs", maxphrsStepper.xSlider);
    minphrsStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minphrs", minphrsStepper.xSlider);
    maxrepStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxrep", maxrepStepper.xSlider);
    minrepStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minrep", minrepStepper.xSlider);
    stutterSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "stutter", stutterSlider.xSlider);
    areaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "area", areaSlider.xSlider);
    straightSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "straight", straightSlider.xSlider);
    regularSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "regular", regularSlider.xSlider);
    ritardSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "ritard", ritardSlider.xSlider);
    speedSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "speed", speedSlider.xSlider);
    activitySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "activity", activitySlider.xSlider);
    crusherSwitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getApvts(), "crusher", crusherSwitch.button);
    minbitsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minbits", minbitsSlider.xSlider);
    maxbitsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxbits", maxbitsSlider.xSlider);
    minfreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "minfreq", minfreqSlider.xSlider);
    maxfreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxfreq", maxfreqSlider.xSlider);
    combSwitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getApvts(), "comb", combSwitch.button);
    typeStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "type", typeStepper.xSlider);
    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "feedback", feedbackSlider.xSlider);
    mindelaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "mindelay", mindelaySlider.xSlider);
    maxdelaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "maxdelay", maxdelaySlider.xSlider);
    seedStepperAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getApvts(), "seed", seedStepper.xSlider);
        
    int titleFontHeight = 100 * scaleFactor;
    int headingFontHeight = 50 * scaleFactor;
    juce::Colour headingColour = juce::Colours::darkgrey;
    
    juce::Font titleFont = FontOptions(audiowide).withHeight(titleFontHeight);
    juce::Font headingFont = FontOptions(audiowide).withHeight(headingFontHeight);
    
    titleSectionLabel.setText("LIVECUT", juce::dontSendNotification);
    titleSectionLabel.setFont(titleFont);
    titleSectionLabel.setColour (juce::Label::textColourId, headingColour);
    titleSectionLabel.setJustificationType(juce::Justification::centred);
    titleSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&titleSectionLabel);
    
    globalSectionLabel.setText("GLOBAL", juce::dontSendNotification);
    globalSectionLabel.setFont(headingFont);
    globalSectionLabel.setColour (juce::Label::textColourId, headingColour);
    globalSectionLabel.setJustificationType(juce::Justification::centred);
    globalSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&globalSectionLabel);

    cutprocSectionLabel.setText("CUTPROC11", juce::dontSendNotification);
    cutprocSectionLabel.setFont(headingFont);
    cutprocSectionLabel.setColour (juce::Label::textColourId, headingColour);
    cutprocSectionLabel.setJustificationType(juce::Justification::centred);
    cutprocSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&cutprocSectionLabel);
    
    warpcutSectionLabel.setText("WARPCUT", juce::dontSendNotification);
    warpcutSectionLabel.setFont(headingFont);
    warpcutSectionLabel.setColour (juce::Label::textColourId, headingColour);
    warpcutSectionLabel.setJustificationType(juce::Justification::centred);
    warpcutSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&warpcutSectionLabel);
    
    sqpusherSectionLabel.setText("SQPUSHER", juce::dontSendNotification);
    sqpusherSectionLabel.setFont(headingFont);
    sqpusherSectionLabel.setColour (juce::Label::textColourId, headingColour);
    sqpusherSectionLabel.setJustificationType(juce::Justification::centred);
    sqpusherSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&sqpusherSectionLabel);
    
    bitcrusherSectionLabel.setText("BITCRUSHER", juce::dontSendNotification);
    bitcrusherSectionLabel.setFont(headingFont);
    bitcrusherSectionLabel.setColour (juce::Label::textColourId, headingColour);
    bitcrusherSectionLabel.setJustificationType(juce::Justification::centred);
    bitcrusherSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&bitcrusherSectionLabel);
    
    combSectionLabel.setText("COMB", juce::dontSendNotification);
    combSectionLabel.setFont(headingFont);
    combSectionLabel.setColour (juce::Label::textColourId, headingColour);
    combSectionLabel.setJustificationType(juce::Justification::centred);
    combSectionLabel.setMinimumHorizontalScale(1.0f);
    addAndMakeVisible(&combSectionLabel);
}

LiveCutAudioProcessorEditor::~LiveCutAudioProcessorEditor()
{
}

//==============================================================================
void LiveCutAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour::fromRGB(0x00, 0x00, 0x00));
    g.setColour(juce::Colour::fromRGB(0xFA, 0xFA, 0xFA));
    float margin = 10.0f;
    g.fillRoundedRectangle(juce::Rectangle<float>(margin, margin, getWidth() - (2.0f * margin), getHeight() - (2.0f * margin)), 25.0f);
    
    // Draw the lines that are centred on the heading labels
    g.setColour(juce::Colours::darkgrey);
    g.drawLine( 80 * scaleFactor, 167 * scaleFactor, 245 * scaleFactor, 167 * scaleFactor);
    g.drawLine( 445 * scaleFactor, 167 * scaleFactor, 600 * scaleFactor, 167 * scaleFactor);
    
    g.drawLine( 780 * scaleFactor, 372 * scaleFactor, 915 * scaleFactor, 372 * scaleFactor);
    g.drawLine( 1180 * scaleFactor, 372 * scaleFactor, 1300 * scaleFactor, 372 * scaleFactor);
    
    g.drawLine( 780 * scaleFactor, 805 * scaleFactor, 925 * scaleFactor, 805 * scaleFactor);
    g.drawLine( 1170 * scaleFactor, 805 * scaleFactor, 1300 * scaleFactor, 805 * scaleFactor);
    
    g.drawLine( 780 * scaleFactor, 1208 * scaleFactor, 910 * scaleFactor, 1208 * scaleFactor);
    g.drawLine( 1185 * scaleFactor, 1208 * scaleFactor, 1300 * scaleFactor, 1208 * scaleFactor);
    
    g.drawLine( 1475 * scaleFactor, 167 * scaleFactor, 1595 * scaleFactor, 167 * scaleFactor);
    g.drawLine( 1900 * scaleFactor, 167 * scaleFactor, 2000 * scaleFactor, 167 * scaleFactor);
    
    g.drawLine( 1475 * scaleFactor, 717 * scaleFactor, 1673 * scaleFactor, 717 * scaleFactor);
    g.drawLine( 1823 * scaleFactor, 717 * scaleFactor, 2000 * scaleFactor, 717 * scaleFactor);
}

void LiveCutAudioProcessorEditor::resized()
{   
    int topMargin = 50 * scaleFactor;
    
    titleSectionLabel.setBounds( (getWidth() / 2) - (200 * scaleFactor), topMargin, 400 * scaleFactor, 60 * scaleFactor);
    
    int smallStep = 80 * scaleFactor;
    int largeStep = 115 * scaleFactor;
    int stepperMargin = 110 * scaleFactor;
    int sliderMargin = 80 * scaleFactor;
    int switchMargin = 140 * scaleFactor;
    int labelTopStep = 100 * scaleFactor;
    int labelBottomStep = 65 * scaleFactor;
    
    int yPos = (100 * scaleFactor) + topMargin;
    //
    globalSectionLabel.setBounds( (getWidth() / 6) - (130 * scaleFactor), yPos, 260 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    cutprocStepper.setBounds(stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += smallStep;
    subdivStepper.setBounds(stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += smallStep;
    seedStepper.setBounds(stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += largeStep;
    fadeSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    minampSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxampSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    minpanSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxpanSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    minpitchSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxpitchSlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    dutySlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    filldutySlider.setBounds(sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    
    yPos = (125 * scaleFactor) + topMargin;
    
    minphrsStepper.setBounds(getWidth() / 3 + stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += smallStep;
    maxphrsStepper.setBounds(getWidth() / 3 + stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    //
    yPos += labelTopStep;
    cutprocSectionLabel.setBounds( (getWidth() / 2) - (172 * scaleFactor), yPos, 344 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    maxrepStepper.setBounds(getWidth() / 3 + stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += smallStep;
    minrepStepper.setBounds(getWidth() / 3 + stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += largeStep;
    stutterSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    areaSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    //
    yPos += labelTopStep;
    warpcutSectionLabel.setBounds( (getWidth() / 2) - (158 * scaleFactor), yPos, 316 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    straightSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    regularSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    ritardSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    speedSlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    //
    yPos += labelTopStep;
    sqpusherSectionLabel.setBounds( (getWidth() / 2) - (178 * scaleFactor), yPos, 356 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    activitySlider.setBounds(getWidth() / 3 + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    
    yPos = (100 * scaleFactor) + topMargin;
    //
    bitcrusherSectionLabel.setBounds( (getWidth() - (getWidth() / 6)) - (195 * scaleFactor), yPos, 390 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    crusherSwitch.setBounds((getWidth() / 3 * 2) + switchMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    minbitsSlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxbitsSlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    minfreqSlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxfreqSlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    //
    yPos += labelTopStep;
    combSectionLabel.setBounds( (getWidth() - (getWidth() / 6)) - (90 * scaleFactor), yPos, 180 * scaleFactor, 40 * scaleFactor);
    yPos += labelBottomStep;
    //
    combSwitch.setBounds((getWidth() / 3 * 2) + switchMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    typeStepper.setBounds((getWidth() / 3 * 2) + stepperMargin, yPos, getWidth() / 4.3f, 65 * scaleFactor);
    yPos += largeStep;
    feedbackSlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += largeStep;
    mindelaySlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
    yPos += smallStep;
    maxdelaySlider.setBounds((getWidth() / 3 * 2) + sliderMargin, yPos, getWidth() / 3, 65 * scaleFactor);
}
