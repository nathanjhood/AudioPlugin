/*
  ==============================================================================

    AutoLambdas.cpp
    Created: 12 Jun 2022 1:41:38am
    Author:  StoneyDSP

  ==============================================================================
*/

#include "AutoLambdas.h"

Lambdas::Lambdas()
{
}

juce::String Lambdas::freqValToString(float freqVal)
{
    if (freqVal <= 1000.0f)
        return juce::String(freqVal, 2, false) + " Hz";

    return juce::String(freqVal / 1000.0f, 2, false) + " kHz";
}

float Lambdas::stringToFreqVal(const juce::String& s)
{
    auto freqVal = s.getFloatValue();

    if (s.getLastCharacter() == 'k')
        freqVal *= 1000.0f;

    return freqVal;
}

juce::String Lambdas::percentValToString(float percentVal)
{
    juce::String percentStr = juce::String(int(percentVal * 100.0f));
    return percentStr + "%";
}

float Lambdas::stringToPercentVal(const juce::String& s)
{ 
    return s.getFloatValue() / 100.0f;
}

juce::String Lambdas::gainValToString(float gainVal)
{
    juce::String gainStr = juce::String(gainVal, 2, false);
    return gainStr + " dB";
}

float Lambdas::stringToGainVal(const juce::String& s) 
{ 
    return s.getFloatValue(); 
}

juce::String Lambdas::ratioValToString(float ratioVal)
{
    juce::String ratioStr = juce::String(ratioVal, 2, false);
    return ratioStr + " : 1";
}

float Lambdas::stringToRatioVal(const juce::String& s) 
{ 
    return s.getFloatValue(); 
}

juce::String Lambdas::timeMsValToString(float timeMsVal)
{
    if (timeMsVal < 1000.0f)
        return juce::String(timeMsVal, 2, false) + " ms";

    juce::String timeSecStr = juce::String(timeMsVal / 1000.0f, 2, false);
    return timeSecStr + " s";
}

float Lambdas::stringToTimeMsVal(const juce::String& s) { return s.getFloatValue(); }

juce::String Lambdas::floatValToString(float floatVal)
{
    return floatValToStringDecimal(floatVal, 2);
}

juce::String Lambdas::floatValToStringDecimal(float floatVal, int numDecimalPlaces)
{
    return { floatVal, numDecimalPlaces, false };
}

float Lambdas::stringToFloatVal(const juce::String& s) 
{ 
    return s.getFloatValue(); 
}