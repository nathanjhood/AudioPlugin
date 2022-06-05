/*
  ==============================================================================

    AutoKnob.h
    Created: 30 May 2022 2:54:47pm
    Author:  StoneyDSP

  ==============================================================================
*/

#ifndef AUTOKNOB_H_INCLUDED
#define AUTOKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

/*
  ==============================================================================

    Look and Feel.

  ==============================================================================
*/

class AutoKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    using APVTS = juce::AudioProcessorValueTreeState;

    //==========================================================================
    /** Constructor. */
    AutoKnobLookAndFeel();
};

/*
  ==============================================================================

    Define parameter objects.

  ==============================================================================
*/

using KnobAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

struct KnobWithAttachment
{
    juce::Slider knob;
    std::unique_ptr<KnobAttachment> attachment;
};

/*
  ==============================================================================

    AutoKnob.

  ==============================================================================
*/

class AutoKnob : public juce::Component
{
public:
    using APVTS = juce::AudioProcessorValueTreeState;
    //==========================================================================
    /** Constructor. */    
    AutoKnob(juce::AudioProcessor& p, APVTS& apvts, std::function<void()> paramLambda = {}, std::function<juce::String(double)>&& apvtsLambda = {});
    ~AutoKnob() override;

    //==========================================================================
    /** Component methods. */
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    //==========================================================================
    /** Instantiate members. */
    AutoKnobLookAndFeel lookAndfeel;
    juce::OwnedArray<KnobWithAttachment> knobs;

    std::function<void()> lambdaSupplier;
    const std::function<juce::String(double)> valueSupplier;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoKnob)
};

#endif //AUTOKNOB_H_INCLUDED