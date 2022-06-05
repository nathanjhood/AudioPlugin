/*
  ==============================================================================

    AutoButton.cpp
    Created: 5 Jun 2022 3:21:48am
    Author:  natha

  ==============================================================================
*/

#include "AutoButton.h"

/*
  ==============================================================================

    Look and Feel.

  ==============================================================================
*/

AutoButtonLookAndFeel::AutoButtonLookAndFeel()
{
    //setColourScheme(LookAndFeel_V4::getMidnightColourScheme());
    /*LookAndFeel_V4::getLightColourScheme();
    LookAndFeel_V4::getDarkColourScheme();
    LookAndFeel_V4::getGreyColourScheme();
    LookAndFeel_V4::getMidnightColourScheme();*/

    //* Button style */
    /*setColour(juce::Button::buttonDown, juce::Colours::orangered);
    setColour(juce::Button::buttonNormal, juce::Colours::darkgrey);
    setColour(juce::Button::buttonOver, juce::Colours::lightslategrey);*/

    ///* Text Button style */
    //setColour(TextButton::buttonColourId, juce::Colours::grey);
    setColour(juce::TextButton::buttonOnColourId, juce::Colours::orangered);
    setColour(juce::TextButton::buttonNormal, juce::Colours::darkgrey);
    setColour(juce::TextButton::buttonOver, juce::Colours::lightslategrey);
    //setColour(TextButton::buttonDown, juce::Colours::green);
    //setColour(TextButton::textColourOnId, juce::Colours::white);
    //setColour(TextButton::textColourOffId, juce::Colours::transparentWhite);
}

/*
  ==============================================================================

    AutoComponent.

  ==============================================================================
*/

//==============================================================================
AutoButton::AutoButton(juce::AudioProcessor& p, APVTS& apvts, std::function<void()>&& paramLambda) : lambdaSupplier(std::move(paramLambda))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    auto addButton = [=, &apvts](juce::AudioParameterBool* param)
    {
        ButtonWithAttachment* newButton = new ButtonWithAttachment;

        addAndMakeVisible(newButton->button);

        newButton->button.setButtonText(param->name);
        newButton->button.setClickingTogglesState(true);
        newButton->button.onStateChange = paramLambda;

        newButton->attachment.reset(new ButtonAttachment(apvts, param->paramID, newButton->button));

        buttons.add(newButton);
    };

    auto params = p.getParameters();

    for (auto* param : params)
    {
        //======================================================================
        /** If = ParameterBool, make new Button with Attachment */

        if (auto* paramBool = dynamic_cast<juce::AudioParameterBool*> (param))
        {
            addButton(paramBool);
            continue;
        }
    }

    setSize(getWidth(), 100);

}

AutoButton::~AutoButton()
{
}

void AutoButton::paint (juce::Graphics& g)
{
    //==========================================================================
    /** Paint Knob border. */

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 5);

    //==========================================================================
    /** Apply local Look and Feel. */

    auto applyLookAndFeel = [this, &g](juce::Component& comp)
    {
        comp.setLookAndFeel(&lookAndfeel);
    };

    for (auto* b : buttons)
        applyLookAndFeel(b->button);
}

void AutoButton::resized()
{
    //==========================================================================
    /** This is generally where you'll want to lay out the positions of any
    /** subcomponents in your editor... */

    int x = 5;
    bool first = true;

    auto width = getWidth();
    auto height = getHeight();
    auto bounds = getBounds();

    auto absCentreX = getWidth() / 3;
    auto absCentreY = getHeight() / 3;

    for (auto* b : buttons)
    {
        int offset = first ? 0 : 0;
        b->button.setBounds(width / 3, absCentreY, 70, 20);
        x = b->button.getRight();
        first = false;
    }

    /*for (auto* b : buttons)
    {
        int offset = first ? 0 : 0;
        b->button.setBounds(x - offset, 40, 70, 20);
        x = b->button.getRight();
        first = false;
    }*/
}
//==============================================================================
