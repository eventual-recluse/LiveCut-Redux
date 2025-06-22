/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BBCutter.h"
#include "BitCrusher.h"
#include "Comb.h"

//==============================================================================
/**
*/
class LiveCutAudioProcessor  : public juce::AudioProcessor
                             , public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LiveCutAudioProcessor();
    ~LiveCutAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState& getApvts();
    
    const int64_t subdivChoices[7]{6, 8, 12, 16, 18, 24, 32};

private:
    //==============================================================================
    
    void registerParameterListeners();
    void parameterChanged (const juce::String &parameterID, float newValue) override;
    void updateAllParameters();
    
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout addParameters();
    
    // Livecut components
    LivePlayer player;
    BitCrusher crusher;
    Comb comb;
    BBCutter bbcutter;
    
    int64_t oldpositionInMeasure;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveCutAudioProcessor)
};
