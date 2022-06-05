/*
  ==============================================================================

    AutoKnob.cpp
    Created: 30 May 2022 2:54:47pm
    Author: StoneyDSP

  ==============================================================================
*/

#include "AutoKnob.h"

/*
  ==============================================================================

    Look and Feel.

  ==============================================================================
*/

AutoKnobLookAndFeel::AutoKnobLookAndFeel()
{
    ///* Knob style */
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::purple);
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightgrey);
    setColour(juce::Slider::backgroundColourId, juce::Colours::brown);
    setColour(juce::Slider::thumbColourId, juce::Colours::pink);
    setColour(juce::Slider::trackColourId, juce::Colours::black);
    setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::grey);
    setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::blue);
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::lightgrey);
}

/*
  ==============================================================================

    AutoKnob.

  ==============================================================================
*/

AutoKnob::AutoKnob(juce::AudioProcessor& p, APVTS& apvts, std::function<void()> paramLambda, std::function<juce::String(double)>&& apvtsLambda) : valueSupplier(std::move(apvtsLambda))
{
    auto addSlider = [=, &apvts](juce::AudioParameterFloat* param)
    {
        SliderWithAttachment* newSlide = new SliderWithAttachment;
        
        addAndMakeVisible(newSlide->slider);
        newSlide->attachment.reset(new SliderAttachment(apvts, param->paramID, newSlide->slider));

        auto suffix = " " + param->getLabel().fromLastOccurrenceOf("_", false, false);
        newSlide->slider.setTextValueSuffix(suffix);

        newSlide->slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        newSlide->slider.setName(param->name);
        newSlide->slider.textFromValueFunction = valueSupplier;
        //newSlide->slider.textFromValueFunction = nullptr; // @TODO: Don't override lambda from VTS
        newSlide->slider.setNumDecimalPlacesToDisplay(2);
        newSlide->slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
        newSlide->slider.onValueChange = paramLambda;

        sliders.add(newSlide);
    };

    auto params = p.getParameters();

    for (auto* param : params)
    {
        //======================================================================
        /** If = ParameterFloat, make new Rotary Slider with Attachment */

        if (auto* paramFloat = dynamic_cast<juce::AudioParameterFloat*> (param))
        {
            addSlider(paramFloat);
            continue;
        }
    }

    setSize(getWidth(), 100);
}

//==============================================================================

void AutoKnob::paint(juce::Graphics& g)
{
    //==========================================================================
    /** Paint Slider/Box name. */

    auto paintName = [this, &g](juce::Component& comp, juce::String name)
    {
        const int height = 20;
        const int initialY = 2;
        juce::Rectangle<int> nameBox(comp.getX(), initialY, comp.getWidth(), height);
        g.setColour(juce::Colours::antiquewhite);
        g.setFont(15.0f);
        g.drawFittedText(name, nameBox, juce::Justification::centred, 1);
    };

    for (auto* s : sliders)
        paintName(s->slider, s->slider.getName());

    //==========================================================================
    /** Apply local Look and Feel. */

    auto applyLookAndFeel = [this, &g](juce::Component& comp)
    {
        comp.setLookAndFeel(&lookAndfeel);
    };

    for (auto* s : sliders)
        applyLookAndFeel(s->slider);
}

//==============================================================================

void AutoKnob::resized()
{
    //==========================================================================
    /** This is generally where you'll want to lay out the positions of any
    /** subcomponents in your editor... */

    int x = 5;
    bool first = true;

    for (auto* s : sliders)
    {
        int offset = first ? 0 : 20;
        s->slider.setBounds(x - offset, 15, 85, 80);
        x = s->slider.getRight();
        first = false;
    }
}
//==============================================================================
