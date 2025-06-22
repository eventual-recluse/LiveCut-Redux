/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomComponents.h"

//==============================================================================
/**
*/
class LiveCutAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LiveCutAudioProcessorEditor (LiveCutAudioProcessor&);
    ~LiveCutAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LiveCutAudioProcessor& audioProcessor;
    
    const float scaleFactor{0.52f};
    
    juce::Label titleSectionLabel;
    juce::Label globalSectionLabel;
    juce::Label cutprocSectionLabel;
    juce::Label warpcutSectionLabel;
    juce::Label sqpusherSectionLabel;
    juce::Label bitcrusherSectionLabel;
    juce::Label combSectionLabel;
    
    const juce::Typeface::Ptr audiowide = juce::Typeface::createSystemTypefaceFor(BinaryData::AudiowideRegular_ttf, BinaryData::AudiowideRegular_ttfSize);
    const juce::Typeface::Ptr varelaTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::VarelaRegular_ttf, BinaryData::VarelaRegular_ttfSize);

    CustomLookAndFeel_V3 sliderLookAndFeel;
    CustomLookAndFeel_V4 stepperLookAndFeel;
    juce::LookAndFeel_V3 switchLookAndFeel;
    
    LookAndFeel_V4::ColourScheme stepperColourScheme{ 0xffefefef, 0xfffaebd3, 0xffffffff,
             0xff696969, 0xff000000, 0xffa9a9a9,
             0xffffffff, 0xff42a2c8, 0xff000000 };

    CustomStepper cutprocStepper;
    CustomStepper subdivStepper;
    CustomSlider fadeSlider; // LOGARITHMIC
    CustomSlider minampSlider;
    CustomSlider maxampSlider;
    CustomSlider minpanSlider;
    CustomSlider maxpanSlider;
    CustomSlider minpitchSlider;
    CustomSlider maxpitchSlider;
    CustomSlider dutySlider;
    CustomSlider filldutySlider;
    CustomStepper maxphrsStepper;
    CustomStepper minphrsStepper;
    CustomStepper maxrepStepper;
    CustomStepper minrepStepper;
    CustomSlider stutterSlider;
    CustomSlider areaSlider;
    CustomSlider straightSlider;
    CustomSlider regularSlider;
    CustomSlider ritardSlider;
    CustomSlider speedSlider;
    CustomSlider activitySlider;
    CustomButton crusherSwitch;
    CustomSlider minbitsSlider;
    CustomSlider maxbitsSlider;
    CustomSlider minfreqSlider; // LOGARITHMIC
    CustomSlider maxfreqSlider; // LOGARITHMIC
    CustomButton combSwitch;
    CustomStepper typeStepper;
    CustomSlider feedbackSlider;
    CustomSlider mindelaySlider;
    CustomSlider maxdelaySlider;
    CustomStepper seedStepper;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutprocStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> subdivStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fadeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minampSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxampSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minpanSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxpanSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minpitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxpitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dutySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filldutySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxphrsStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minphrsStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxrepStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minrepStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> stutterSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> areaSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> straightSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> regularSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ritardSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> activitySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crusherSwitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minbitsSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxbitsSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minfreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxfreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> combSwitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> typeStepperAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mindelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxdelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> seedStepperAttachment;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveCutAudioProcessorEditor)
};
