/*
  ==============================================================================

    AutoComponent.cpp
    Created: 30 May 2022 2:54:47pm
    Author:  (?) & StoneyDSP

  ==============================================================================
*/

#include "AutoComponent.h"

AutoComponentLookAndFeel::AutoComponentLookAndFeel()
{
    ///* Knob style */
    setColour(Slider::rotarySliderOutlineColourId, juce::Colours::lightgrey);
    setColour(Slider::rotarySliderFillColourId, juce::Colours::darkgrey);
    //setColour(Slider::backgroundColourId, juce::Colours::brown);
    setColour(Slider::thumbColourId, juce::Colours::purple);
    //setColour(Slider::trackColourId, juce::Colours::yellow);
    setColour(Slider::textBoxTextColourId, juce::Colours::white);
    setColour(Slider::textBoxBackgroundColourId, juce::Colours::grey);
    setColour(Slider::textBoxHighlightColourId, juce::Colours::blue);
    setColour(Slider::textBoxOutlineColourId, juce::Colours::lightgrey);

    //* Button style */
    setColour(Button::buttonDown, juce::Colours::orangered);
    setColour(Button::buttonNormal, juce::Colours::darkgrey);
    setColour(Button::buttonOver, juce::Colours::lightgrey);

    ///* Text Button style */
    //setColour(TextButton::buttonColourId, juce::Colours::grey);
    setColour(TextButton::buttonOnColourId, juce::Colours::orangered);
    setColour(TextButton::buttonNormal, juce::Colours::darkgrey);
    setColour(TextButton::buttonOver, juce::Colours::lightgrey);
    //setColour(TextButton::buttonDown, juce::Colours::green);
    //setColour(TextButton::textColourOnId, juce::Colours::white);
    //setColour(TextButton::textColourOffId, juce::Colours::transparentWhite);
}

AutoComponent::AutoComponent(juce::AudioProcessor& p, APVTS& apvts, std::function<void()> paramLambda)
{
    auto addSlider = [=, &apvts] (juce::AudioParameterFloat* param)
    {
        SliderWithAttachment* newSlide = new SliderWithAttachment;

        addAndMakeVisible (newSlide->slider);
        newSlide->attachment.reset (new SliderAttachment (apvts, param->paramID, newSlide->slider));

        auto suffix = " " + param->getLabel().fromLastOccurrenceOf ("_", false, false);
        newSlide->slider.setTextValueSuffix (suffix);

        newSlide->slider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
        newSlide->slider.setName (param->name);
        newSlide->slider.textFromValueFunction = nullptr; // @TODO: Don't override lambda from VTS
        newSlide->slider.setNumDecimalPlacesToDisplay (2);
        newSlide->slider.setTextBoxStyle (Slider::TextBoxBelow, false, 60, 16);
        newSlide->slider.onValueChange = paramLambda;

        sliders.add (newSlide);
    };

    auto addBox = [=, &apvts] (juce::AudioParameterChoice* param)
    {
        BoxWithAttachment* newBox = new BoxWithAttachment;

        addAndMakeVisible (newBox->box);
        newBox->box.setName (param->name);
        newBox->box.addItemList (param->choices, 1);
        newBox->box.setSelectedItemIndex (0);
        newBox->box.onChange = paramLambda;

        newBox->attachment.reset (new ComboBoxAttachment (apvts, param->paramID, newBox->box));

        boxes.add (newBox);
    };

    auto addButton = [=, &apvts] (juce::AudioParameterBool* param)
    {
        ButtonWithAttachment* newButton = new ButtonWithAttachment;

        addAndMakeVisible (newButton->button);
        newButton->button.setButtonText (param->name);
        newButton->button.setClickingTogglesState (true);
        newButton->button.onStateChange = paramLambda;

        newButton->attachment.reset (new ButtonAttachment (apvts, param->paramID, newButton->button));

        buttons.add (newButton);
    };

    auto params = p.getParameters();

    for (auto* param : params)
    {
        if (auto* paramFloat = dynamic_cast<juce::AudioParameterFloat*> (param))
        {
            addSlider (paramFloat);
            continue;
        }

        if (auto* paramChoice = dynamic_cast<juce::AudioParameterChoice*> (param))
        {
            addBox (paramChoice);
            continue;
        }

        if (auto* paramBool = dynamic_cast<juce::AudioParameterBool*> (param))
        {
            addButton (paramBool);
            continue;
        }
    }

    setSize (getWidth(), 100);
}

//==============================================================================
void AutoComponent::paint (juce::Graphics& g)
{
    //==========================================================================
    /** Paint Slider/Box name. */

    auto paintName = [this, &g] (juce::Component& comp, juce::String name)
    {
        const int height = 20;
        juce::Rectangle<int> nameBox (comp.getX(), 2, comp.getWidth(), height);
        g.drawFittedText (name, nameBox, juce::Justification::centredBottom, 1);
    };

    for (auto* s : sliders)
        paintName (s->slider, s->slider.getName());

    for (auto* b : boxes)
        paintName (b->box, b->box.getName());

    //==========================================================================
    /** Apply local look and feel. */

    auto applyLookAndFeel = [this, &g] (juce::Component& comp)
    {
        comp.setLookAndFeel(&lookAndfeel);
    };

    for (auto* s : sliders)
        applyLookAndFeel (s->slider);

    for (auto* b : boxes)
        applyLookAndFeel (b->box);

    for (auto* b : buttons)
        applyLookAndFeel(b->button);
}

//==============================================================================
void AutoComponent::resized()
{
    int x = 5;
    bool first = true;
    for (auto* s : sliders)
    {
        int offset = first ? 0 : 20;
        s->slider.setBounds (x - offset, 15, 85, 80);
        x = s->slider.getRight();
        first = false;
    }

    for (auto* b : boxes)
    {
        int offset = first ? 0 : 5;
        b->box.setBounds (x - offset, 40, 70, 20);
        x = b->box.getRight();
        first = false;
    }

    for (auto* b : buttons)
    {
        int offset = first ? 0 : 5;
        b->button.setBounds (x - offset, 40, 70, 20);
        x = b->button.getRight();
        first = false;
    }
}
//==============================================================================
