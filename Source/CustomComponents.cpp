#include "CustomComponents.h"

CustomSlider::CustomSlider()
{
    // We'll display only the thumb and text box of the JUCE slider.
    // LookAndFeel_V3 was chosen because it's a similar style to the old Livecut GUI.
    // CustomLookAndFeel_V3 prevents drawing of the JUCE slider background.
    // The slider background will be replaced by our own graphic.
    xSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    xSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentWhite);
    xSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::orange);
    xSlider.setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(0xE9, 0xE6, 0xE6));
    addAndMakeVisible(&xSlider);
    
    sliderBackgroundAndTrack = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(SliderSvg));
}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::resized()
{
    xSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 160 * scaleFactor, 43 * scaleFactor);
    xSlider.setBounds(160 * scaleFactor, 1 * scaleFactor, 372 * scaleFactor, 70 * scaleFactor);
    // Note: the specified width & height of the slider SVG image is 531 x 61
    sliderBackgroundAndTrack->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 531.0f * scaleFactor, 61.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
}

void CustomSlider::paint(Graphics& g)
{
    g.setFont(font.withHeight(32 * scaleFactor));
    
    sliderBackgroundAndTrack->drawAt(g, 0.0f, 0.0f, 1.0f);
    
    g.setColour(juce::Colours::black);
    g.drawText(sliderTitle, 2 * scaleFactor, 0 * scaleFactor, 165 * scaleFactor, 60 * scaleFactor, juce::Justification::centred, false);
    
    g.setColour(juce::Colours::black);
    g.drawText(unitText, 360 * scaleFactor, 35 * scaleFactor, 165 * scaleFactor, 30 * scaleFactor, juce::Justification::centred, false);

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
    scaleFactor = 1.0f;
    
    stepperImg = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(StepperSvg));
    downOnImg = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(StepperDownOnSvg));
    upOnImg = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(StepperUpOnSvg));
    
    displayChoiceText = false;
    
    // Don't display the JUCE slider, as we will replace it with our own graphic.
    // However, we'll use the JUCE slider object so we can send and listen for parameter changes.
    addAndMakeVisible(&xSlider);
    xSlider.setSliderStyle(juce::Slider::IncDecButtons);
    xSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsNotDraggable);
    xSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    xSlider.addListener(this);
    xSlider.setEnabled(false);
    xSlider.setVisible(false);
    
    status = NORMAL;
    dragging = false;

}

CustomStepper::~CustomStepper() {}

void CustomStepper::mouseDown(const MouseEvent& event)
{
    // Buttons are about 25 * scaleFactor radius
    juce::Point downButtonCenter (203 * scaleFactor, 30 * scaleFactor);
    juce::Point upButtonCenter (260 * scaleFactor, 30 * scaleFactor);
    
    if ( downButtonCenter.getDistanceFrom(juce::Point<float>(event.position.getX(), event.position.getY())) < (25 * scaleFactor) )
    {
        increment(-1);
        status = DOWN_ON;
        dragging = true;
        valueOnMouseDown = xSlider.getValue();
        startTimerHz(1);
        repaint();
    }
    else if ( upButtonCenter.getDistanceFrom(juce::Point<float>(event.position.getX(), event.position.getY())) < (25 * scaleFactor) )
    {
        increment(1);
        status = UP_ON;
        dragging = true;
        valueOnMouseDown = xSlider.getValue();
        startTimerHz(1);
        repaint();
    }
}

void CustomStepper::mouseUp(const MouseEvent& event)
{
    if (dragging)
    {
        dragging = false;
        repaint();
    }
}

void CustomStepper::mouseDrag(const MouseEvent& event)
{
    if (dragging)
    {
        double newVal = limitValue( valueOnMouseDown + ( (event.getDistanceFromDragStartY() * -1.0) * 0.01), xSlider.getMinimum(), xSlider.getMaximum());
        xSlider.setValue(newVal);
        repaint();
    }
}

void CustomStepper::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel)
{
    juce::Rectangle<float> mouseScrollArea (0 * scaleFactor, 0 * scaleFactor, 462 * scaleFactor, 59 * scaleFactor);
    
    if ( (event.position.getX() > mouseScrollArea.getX()) && (event.position.getY() > mouseScrollArea.getY()) && (event.position.getX() < mouseScrollArea.getRight()) && (event.position.getY() < mouseScrollArea.getBottom()) )
    {
        if (! juce::approximatelyEqual (wheel.deltaY, 0.0f))
        {
            increment( 1 * (wheel.isReversed ? -1 : 1) * (wheel.deltaY < 0.0f ? -1 : 1) );
        }
    }
}

void CustomStepper::resized()
{
    stepperImg->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 466.0f * scaleFactor, 59.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
    downOnImg->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 466.0f * scaleFactor, 59.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
    upOnImg->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 466.0f * scaleFactor, 59.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
    // Note: the specified width & height of the slider SVG image is 466 x 59
}

void CustomStepper::paint(Graphics& g)
{
    switch(status)
    {
        case NORMAL:
            stepperImg->drawAt(g, 0.0f, 0.0f, 1.0f);
            break;
        case DOWN_ON:
            downOnImg->drawAt(g, 0.0f, 0.0f, 1.0f);
            break;
        case UP_ON:
            upOnImg->drawAt(g, 0.0f, 0.0f, 1.0f);
            break;
        default:
            stepperImg->drawAt(g, 0.0f, 0.0f, 1.0f);
            break;
    }
    
    g.setFont(font.withHeight(32 * scaleFactor));
    g.setColour(juce::Colours::black);
    g.drawText(sliderTitle, 0 * scaleFactor, 0 * scaleFactor, 175 * scaleFactor, 59 * scaleFactor, juce::Justification::centred, false);
    
    //g.setFont(font.withHeight(30 * scaleFactor));
    if (displayChoiceText && !choices.isEmpty())
        g.drawText(choices[xSlider.getValue()], 285 * scaleFactor, 0 * scaleFactor, 175 * scaleFactor, 59 * scaleFactor, juce::Justification::centred, false);
    else
        g.drawText(juce::String(xSlider.getValue()) + unitText, 285 * scaleFactor, 0 * scaleFactor, 175 * scaleFactor, 59 * scaleFactor, juce::Justification::centred, false);
    
    // Show title text area (for calibration)
    //g.drawRect(juce::Rectangle<float>(0 * scaleFactor, 0 * scaleFactor, 175 * scaleFactor, 59 * scaleFactor));
    
    // Show unit text area (for calibration)
    //g.drawRect(juce::Rectangle<float>(285 * scaleFactor, 0 * scaleFactor, 175 * scaleFactor, 59 * scaleFactor));
    
    // Show button ellipses (for calibrating the widget)
    //g.fillEllipse(203 * scaleFactor - 25* scaleFactor, 30 * scaleFactor - 25* scaleFactor, 50.0f* scaleFactor, 50.0f* scaleFactor);
    //g.fillEllipse(260 * scaleFactor - 25* scaleFactor, 30 * scaleFactor - 25* scaleFactor, 50.0f* scaleFactor, 50.0f* scaleFactor);
    
    // Show mouse scroll bounding box (for calibration)
    //g.drawRect(juce::Rectangle<float>(0 * scaleFactor, 0 * scaleFactor, 462 * scaleFactor, 59 * scaleFactor));
}

void CustomStepper::setScale(const float newScale)
{
    scaleFactor = newScale;
    resized();
}

void CustomStepper::sliderValueChanged(Slider* slider)
{
    if (slider == &xSlider)
    {
        repaint();
    }
}

void CustomStepper::setTitle(const juce::String &title)
{
    sliderTitle = title;
}

void CustomStepper::setUnitText(const juce::String &newUnitText)
{
    unitText = " " + newUnitText;
}

void CustomStepper::setChoices(const juce::StringArray &newChoices)
{
    choices = newChoices;
}

void CustomStepper::setFont(const juce::Font &newFont)
{
    font = newFont;
}

void CustomStepper::setDisplayChoiceText(const bool ch)
{
    displayChoiceText = ch;
}

void CustomStepper::increment(const int inc)
{
    if ( ( (inc > 0) && ( (xSlider.getValue() + inc) <= xSlider.getMaximum()) ) 
        || ( (inc < 0) && ( (xSlider.getValue() + inc) >= xSlider.getMinimum())) )
        xSlider.setValue(xSlider.getValue() + inc);
    repaint();
}

void CustomStepper::timerCallback()
{
    stopTimer();
    status = NORMAL;
    repaint();
}




CustomButton::CustomButton()
{
    scaleFactor = 1.0f;
    choices = juce::StringArray{"OFF", "ON"};
    
    offImg = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(SwitchSvg));
    onImg = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(SwitchOnSvg));
    
    // Don't display the JUCE button, as we will replace it with our own graphic.
    // However, we'll still use a JUCE button object so we can send and listen for parameter changes.
    button.setToggleable(true);
    button.setClickingTogglesState(true);
    button.addListener(this);
    button.setEnabled(false);
    button.setVisible(false);
    addAndMakeVisible(&button);
    
    switchWasPressed = false;
}

CustomButton::~CustomButton() {}

void CustomButton::mouseDown(const MouseEvent& event)
{
    // This rectangle covers the area of the on / off label.
    juce::Rectangle<float> onOffArea (230 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 59 * scaleFactor);
    
    juce::Point switchButtonCenter (206 * scaleFactor, 30 * scaleFactor);
    // Button is about 25 * scaleFactor radius
    
    if  ( ( switchButtonCenter.getDistanceFrom(juce::Point<float>(event.position.getX(), event.position.getY())) < (25 * scaleFactor) )
            || ( (event.position.getX() > onOffArea.getX()) && (event.position.getY() > onOffArea.getY()) && (event.position.getX() < onOffArea.getRight()) && (event.position.getY() < onOffArea.getBottom()) )
        )
    {
        switchWasPressed = true;
        toggle();
    }
}

void CustomButton::mouseUp(const MouseEvent& event)
{
    if (switchWasPressed)
    {
        switchWasPressed = false;
    }
}

void CustomButton::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel)
{
    juce::Rectangle<float> mouseScrollArea (0 * scaleFactor, 0 * scaleFactor, 413 * scaleFactor, 59 * scaleFactor);
    
    if ( (event.position.getX() > mouseScrollArea.getX()) && (event.position.getY() > mouseScrollArea.getY()) && (event.position.getX() < mouseScrollArea.getRight()) && (event.position.getY() < mouseScrollArea.getBottom()) )
    {
        if (! juce::approximatelyEqual (wheel.deltaY, 0.0f))
        {
            if ( (button.getToggleState() == false && (wheel.deltaY * (wheel.isReversed ? -1.0 : 1.0) > 0.0f))
                || (button.getToggleState() == true && (wheel.deltaY * (wheel.isReversed ? -1.0 : 1.0) < 0.0f)) )
            {
                toggle();
            }
        }
    }
}

void CustomButton::resized()
{
    // Note: the specified width & height of the slider SVG image is 416 x 59
    onImg->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 416.0f * scaleFactor, 59.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
    offImg->setTransformToFit(juce::Rectangle<float>(0.0f, 0.0f, 416.0f * scaleFactor, 59.0f * scaleFactor), juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yTop);
}

void CustomButton::paint(Graphics& g)
{
    if (button.getToggleState() == false)
    {
        offImg->drawAt(g, 0.0f, 0.0f, 1.0f);
    }
    else if (button.getToggleState() == true)
    {
        onImg->drawAt(g, 0.0f, 0.0f, 1.0f);
    }
    
    g.setFont(font.withHeight(32 * scaleFactor));
    g.setColour(juce::Colours::black);
    g.drawText(switchTitle, 0 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 59 * scaleFactor, juce::Justification::centred, false);
    
    //g.setFont(font.withHeight(30 * scaleFactor));
    g.drawText(choices[button.getToggleState()], 227 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 59 * scaleFactor, juce::Justification::centred, false);
    
    // Show title text box (for calibration)
    //g.drawRect(juce::Rectangle<float>(0 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 59 * scaleFactor));
    // Show On/Off text box (for calibration)
    //g.drawRect(juce::Rectangle<float>(227 * scaleFactor, 0 * scaleFactor, 180 * scaleFactor, 59 * scaleFactor));
    // Show button ellipse (for calibration)
    //g.fillEllipse(206 * scaleFactor - 25* scaleFactor, 30 * scaleFactor - 25* scaleFactor, 50.0f* scaleFactor, 50.0f* scaleFactor);
    
    // Show mouse scroll bounding box (for calibration)
    //g.drawRect(juce::Rectangle<float>(0 * scaleFactor, 0 * scaleFactor, 413 * scaleFactor, 59 * scaleFactor));
}

void CustomButton::setScale(const float newScale)
{
    scaleFactor = newScale;
    resized();
}

void CustomButton::buttonStateChanged(Button* btn)
{
    if (btn == &button)
    {
        repaint();
    }
}

void CustomButton::buttonClicked(Button* btn)
{
    if (btn == &button)
    {
        repaint();
    }
}

void CustomButton::setTitle(const juce::String &title)
{
    switchTitle = title;
}

void CustomButton::setFont(const juce::Font &newFont)
{
    font = newFont;
}

void CustomButton::toggle()
{
    if (button.getToggleState() == true)
        button.setToggleState(false, juce::sendNotificationSync);
    else if (button.getToggleState() == false)
        button.setToggleState(true, juce::sendNotificationSync);
        
    repaint();
}
