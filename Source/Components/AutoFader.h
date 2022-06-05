/*
  ==============================================================================

    AutoFader.h
    Created: 5 Jun 2022 5:48:30pm
    Author:  natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AutoFader  : public juce::Component
{
public:
    AutoFader();
    ~AutoFader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoFader)
};
