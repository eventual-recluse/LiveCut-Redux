#include "CustomComponents.h"

CustomSlider::CustomSlider()
{
    xSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    xSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::orange);
    xSlider.setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(0xF6, 0xB6, 0x48));
    addAndMakeVisible(&xSlider);
}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::resized()
{
    xSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 160 * scaleFactor, 43 * scaleFactor);
    xSlider.setBounds(160 * scaleFactor, 0, 370 * scaleFactor, 65 * scaleFactor);
}

void CustomSlider::paint(Graphics& g)
{
    g.setFont(font.withHeight(32 * scaleFactor));
    

    g.setColour(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7));
    g.setGradientFill(juce::ColourGradient(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7), 150.0f  * scaleFactor, 30.0f * scaleFactor, juce::Colour::fromRGB(0xF6, 0xB6, 0x48), 280.0f  * scaleFactor, 30.0f * scaleFactor, false));
    g.fillRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 260.0f * scaleFactor, 61.0f * scaleFactor, 16.0f);
    
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 260.0f * scaleFactor, 61.0f * scaleFactor, 16.0f, 0.5f);
    
    g.setColour(juce::Colours::black);
    g.drawText(sliderTitle, 2 * scaleFactor, 0 * scaleFactor, 165 * scaleFactor, 63 * scaleFactor, juce::Justification::centred, false);
    
    g.setColour(juce::Colours::black);
    g.drawText(unitText, 360 * scaleFactor, 32 * scaleFactor, 165 * scaleFactor, 30 * scaleFactor, juce::Justification::centred, false);

    // Obscure the rounded rectangle behind the track.
    g.setColour(juce::Colour::fromRGB(0xFA, 0xFA, 0xFA));
    g.fillRoundedRectangle(165.0f * scaleFactor, 0.0f, 360.0f * scaleFactor, 29.0f * scaleFactor, 8.0f);
}

void CustomSlider::setScale(const float newScaleFactor)
{
    scaleFactor = newScaleFactor;
    resized();
}

void CustomSlider::setTitle(const juce::String &newTitle)
{
    sliderTitle = newTitle;
    repaint();
}

void CustomSlider::setFont(const juce::Font &newFont)
{
    font = newFont;
}

void CustomSlider::setUnitText(const juce::String &newUnitText)
{
    unitText = newUnitText;
}






CustomStepper::CustomStepper()
{
    xSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    xSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    xSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::orange);
    addAndMakeVisible(&xSlider);
}

CustomStepper::~CustomStepper()
{
}

void CustomStepper::resized()
{
    xSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, true, 165 * scaleFactor, 43 * scaleFactor);
    xSlider.setBounds(180 * scaleFactor, 6, 280 * scaleFactor, 40 * scaleFactor);
}

void CustomStepper::paint(Graphics& g)
{
    g.setFont(font.withHeight(32 * scaleFactor));
    

    g.setColour(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7));
    g.setGradientFill(juce::ColourGradient(juce::Colour::fromRGB(0xF6, 0xB6, 0x48), 150.0f  * scaleFactor, 30.0f * scaleFactor, juce::Colour::fromRGB(0xF6, 0xD9, 0xA7), 280.0f  * scaleFactor, 30.0f * scaleFactor, false));
    g.fillRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 189.0f * scaleFactor, 60.0f * scaleFactor, 16.0f);
    
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 189.0f * scaleFactor, 60.0f * scaleFactor, 16.0f, 0.5f);
    
    
    
    g.setColour(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7));
    g.setGradientFill(juce::ColourGradient(juce::Colour::fromRGB(0xF6, 0xB6, 0x48), 150.0f  * scaleFactor, 30.0f * scaleFactor, juce::Colour::fromRGB(0xF6, 0xD9, 0xA7), 280.0f  * scaleFactor, 30.0f * scaleFactor, false));
    g.fillRoundedRectangle(285.0f * scaleFactor, 1.0f * scaleFactor, 187.0f * scaleFactor, 60.0f * scaleFactor, 16.0f);
    
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(285.0f * scaleFactor, 1.0f * scaleFactor, 187.0f * scaleFactor, 60.0f * scaleFactor, 16.0f, 0.5f);

    g.setColour(juce::Colours::black);
    g.drawText(sliderTitle, 2 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 63 * scaleFactor, juce::Justification::centred, false);

}

void CustomStepper::setScale(const float newScaleFactor)
{
    scaleFactor = newScaleFactor;
    resized();
}

void CustomStepper::setTitle(const juce::String &newTitle)
{
    sliderTitle = newTitle;
    repaint();
}

void CustomStepper::setFont(const juce::Font &newFont)
{
    font = newFont;
}




CustomButton::CustomButton()
{
    button.setButtonText("OFF");
    button.setToggleable(true);
    button.setClickingTogglesState(true);
    button.onClick = [this] { buttonClicked(); };
    button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::orange);
    addAndMakeVisible(&button);
}

CustomButton::~CustomButton()
{
}

void CustomButton::resized()
{
    button.setBounds(170 * scaleFactor, 0 * scaleFactor, 80 * scaleFactor, 60 * scaleFactor);
}

void CustomButton::paint(Graphics& g)
{
    g.setFont(font.withHeight(32 * scaleFactor));
    

    g.setColour(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7));
    g.setGradientFill(juce::ColourGradient(juce::Colour::fromRGB(0xF6, 0xD9, 0xA7), 150.0f  * scaleFactor, 30.0f * scaleFactor, juce::Colour::fromRGB(0xF6, 0xB6, 0x48), 280.0f  * scaleFactor, 30.0f * scaleFactor, false));
    g.fillRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 170.0f * scaleFactor, 60.0f * scaleFactor, 16.0f);
    
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(1.0f * scaleFactor, 1.0f * scaleFactor, 170.0f * scaleFactor, 60.0f * scaleFactor, 16.0f, 0.5f);

    g.setColour(juce::Colours::black);
    g.drawText(buttonTitle, 2 * scaleFactor, 0 * scaleFactor, 165 * scaleFactor, 63 * scaleFactor, juce::Justification::centred, false);
}


void CustomButton::setScale(const float newScaleFactor)
{
    scaleFactor = newScaleFactor;
    resized();
}

void CustomButton::setTitle(const juce::String &newTitle)
{
    buttonTitle = newTitle;
    repaint();
}

void CustomButton::setFont(const juce::Font &newFont)
{
    font = newFont;
}

void CustomButton::buttonClicked()
{
    if (button.getToggleState())
    {
        button.setButtonText("ON");
    }
    else
    {
        button.setButtonText("OFF");
    }
}
