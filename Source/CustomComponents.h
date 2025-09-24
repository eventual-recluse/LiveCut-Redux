#ifndef CUSTOMCOMPONENTS_H
#define CUSTOMCOMPONENTS_H

#include <JuceHeader.h>
#include "CustomComponentImages.h"

template <class T>
T limitValue (const T x, const T min, const T max)
{
    return (x < min ? min : (x > max ? max : x));
}

class CustomLookAndFeel_V3 : public juce::LookAndFeel_V3
{
public:
    CustomLookAndFeel_V3()
    {
    }
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                 float /*sliderPos*/,
                                                 float /*minSliderPos*/,
                                                 float /*maxSliderPos*/,
                                                 const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        // Don't draw anything! This method is overridden so that the slider background is not drawn here.
        // NOTE! For the sliders, we retain and display only the thumb and the text box from the JUCE slider
    }
};

struct CustomSlider : public juce::Component
{
    CustomSlider();
    ~CustomSlider();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void setScale(const float newScaleFactor);
    void setTitle(const juce::String &newTitle);
    void setFont(const juce::Font &newFont);
    void setUnitText(const juce::String &newUnitText);
    
    float scaleFactor{1.0f};

    juce::Slider xSlider;
    juce::String sliderTitle;
    juce::String unitText;
    juce::Font font { withDefaultMetrics (juce::FontOptions() ) };
    
    std::unique_ptr<juce::Drawable> sliderBackgroundAndTrack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSlider)
};

struct CustomStepper : public juce::Component
                    , public juce::Slider::Listener
                    , public juce::Timer
{
    CustomStepper();
    ~CustomStepper();
    
    enum StepperStatus
    {
        NORMAL = 0,
        DOWN_ON = 1,
        UP_ON = 2
    };
        
    void mouseDown(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
    void resized() override;
    void paint(Graphics& g) override;
    void setScale(const float newScale);
    void sliderValueChanged(Slider* slider) override;
    
    void setTitle(const juce::String &title);
    void setUnitText(const juce::String &title);
    void setChoices(const juce::StringArray &newChoices);
    void setFont(const juce::Font &newFont);
    void setDisplayChoiceText(const bool ch);
    void increment(const int inc);
    void timerCallback() override;
        
    uint32_t status;
    double valueOnMouseDown;
    bool dragging;
    
    juce::Slider xSlider;
    std::unique_ptr<juce::Drawable> stepperImg;
    std::unique_ptr<juce::Drawable> downOnImg;
    std::unique_ptr<juce::Drawable> upOnImg;
    
    juce::StringArray choices;
    float scaleFactor;
    juce::String sliderTitle;
    juce::String unitText;
    
    bool displayChoiceText;
    
    juce::Font font { withDefaultMetrics (juce::FontOptions() ) };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomStepper)
};

struct CustomButton : public juce::Component
                    , public juce::Button::Listener
{
    CustomButton();
    ~CustomButton();
    
    void mouseDown(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
    void resized() override;
    void paint(Graphics& g) override;
    void setScale(const float newScale);
    void buttonStateChanged(Button* btn) override;
    void buttonClicked(Button* btn) override;
    
    void setTitle(const juce::String &title);
    void setFont(const juce::Font &newFont);
    void toggle();
        
    std::unique_ptr<juce::Drawable> offImg;
    std::unique_ptr<juce::Drawable> onImg;
    
    bool switchWasPressed;
    
    float scaleFactor;
    juce::StringArray choices;
    juce::TextButton button;
    juce::String switchTitle;
    
    juce::Font font { withDefaultMetrics (juce::FontOptions() ) };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomButton)
};

#endif // CUSTOMCOMPONENTS_H
