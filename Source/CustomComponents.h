#ifndef CUSTOMCOMPONENTS_H
#define CUSTOMCOMPONENTS_H

#include <JuceHeader.h>

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
        const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

        const Colour trackColour (slider.findColour (Slider::trackColourId));
        const Colour gradCol1 (trackColour.overlaidWith (Colour (slider.isEnabled() ? 0x13000000 : 0x09000000)));
        const Colour gradCol2 (trackColour.overlaidWith (Colour (0x06000000)));
        Path indent;

        if (slider.isHorizontal())
        {
            auto iy = (float) y + (float) height * 0.5f - sliderRadius;

            g.setGradientFill (ColourGradient::vertical (gradCol1, iy, gradCol2, iy + sliderRadius * 2.0f));

            indent.addRoundedRectangle ((float) x - sliderRadius, iy, (float) width + sliderRadius * 2.0f, sliderRadius * 2.0f, 8.0f);
        }
        else
        {
            auto ix = (float) x + (float) width * 0.5f - sliderRadius * 0.5f;

            g.setGradientFill (ColourGradient::horizontal (gradCol1, ix, gradCol2, ix + sliderRadius));

            indent.addRoundedRectangle (ix, (float) y - sliderRadius * 0.5f, sliderRadius, (float) height + sliderRadius, 5.0f);
        }

        g.fillPath (indent);

        g.setColour (trackColour.contrasting (1.0f));
        g.strokePath (indent, PathStrokeType (0.5f));
    }
};

class CustomLookAndFeel_V4 : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel_V4()
    {
    }
    void drawButtonText (Graphics& g, TextButton& button,
                                     bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/) override
    {
        //Font font (getTextButtonFont (button, button.getHeight()));
        Font font (withDefaultMetrics (FontOptions { jmin (16.0f, (float) button.getHeight() * 0.8f) }));
        g.setFont (font);
        g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                                : TextButton::textColourOffId)
                           .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

        const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
        const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

        const int fontHeight = roundToInt (font.getHeight() * 0.6f);
        const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        const int textWidth = button.getWidth() - leftIndent - rightIndent;

        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                              Justification::centred, 2);
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSlider)
};

struct CustomStepper : public juce::Component
{
    CustomStepper();
    ~CustomStepper();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void setScale(const float newScaleFactor);
    void setTitle(const juce::String &newTitle);
    void setFont(const juce::Font &newFont);
    
    float scaleFactor{1.0f};

    juce::Slider xSlider;
    juce::String sliderTitle;
    juce::Font font { withDefaultMetrics (juce::FontOptions() ) };
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomStepper)
};

struct CustomButton : public juce::Component
{
    CustomButton();
    ~CustomButton();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void setScale(const float newScaleFactor);
    void setTitle(const juce::String &newTitle);
    void setFont(const juce::Font &newFont);
    
    void buttonClicked();
    
    float scaleFactor{1.0f};

    juce::TextButton button;
    juce::String buttonTitle;
    juce::Font font { withDefaultMetrics (juce::FontOptions() ) };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomButton)
};

#endif // CUSTOMCOMPONENTS_H
