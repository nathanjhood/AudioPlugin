/*
  ==============================================================================

    AutoLambdas.h
    Created: 12 Jun 2022 1:41:38am
    Author:  StoneyDSP

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#ifndef AUTOLAMBDAS_H_INCLUDED
#define AUTOLAMBDAS_H_INCLUDED

class Lambdas
{
public:

    Lambdas();

    juce::String freqValToString(float freqVal);
    float stringToFreqVal(const juce::String& s);

    juce::String percentValToString(float percentVal);
    float stringToPercentVal(const juce::String& s);

    juce::String gainValToString(float gainVal);
    float stringToGainVal(const juce::String& s);

    juce::String ratioValToString(float ratioVal);
    float stringToRatioVal(const juce::String& s);

    juce::String timeMsValToString(float timeMsVal);
    float stringToTimeMsVal(const juce::String& s);

    juce::String floatValToString(float floatVal);
    juce::String floatValToStringDecimal(float floatVal, int numDecimalPlaces);
    float stringToFloatVal(const juce::String& s);
};

#endif // AUTOLAMBDAS_H_INCLUDED
