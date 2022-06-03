/*
  ==============================================================================

    PluginParameters.cpp
    Created: 29 May 2022 7:58:00pm
    Author:  Nathan J. Hood

  ==============================================================================
*/

#include "PluginParameters.h"
#include "PluginProcessor.h"

Parameters::Parameters(AudioPluginAudioProcessor& p, APVTS& apvts) : audioProcessor(p)
{
    osPtr = static_cast                <juce::AudioParameterChoice*>       (apvts.getParameter("osID"));
    jassert(osPtr != nullptr);

    outputPtr = static_cast            <juce::AudioParameterFloat*>        (apvts.getParameter("outputID"));
    jassert(outputPtr != nullptr);

    mixPtr = static_cast              <juce::AudioParameterFloat*>        (apvts.getParameter("mixID"));
    jassert(mixPtr != nullptr);

    bypassPtr = static_cast <juce::AudioParameterBool*>(apvts.getParameter("bypassID"));
    jassert(bypassPtr != nullptr);
}

void Parameters::setParameterLayout(Params& params)
{
    const auto dBMax = juce::Decibels::gainToDecibels(16.0f);
    const auto dBMin = juce::Decibels::gainToDecibels(0.5f, -120.0f) * 20.0f;

    const auto gainRange = juce::NormalisableRange<float>(dBMin, dBMax, 0.01f, 1.00f);
    const auto mixRange = juce::NormalisableRange<float>(00.00f, 100.00f, 0.01f, 1.00f);

    auto osString = juce::StringArray ( { "--", "2x", "4x", "8x", "16x" } );

    const auto decibels =       juce::String    { ( "dB" ) };
    const auto frequency =      juce::String    { ( "Hz" ) };
    const auto percentage =     juce::String    { ( "%" ) };
    const auto milliseconds =   juce::String    { ( ".ms" ) };

    params.add(std::make_unique<juce::AudioParameterChoice>("osID", "Oversampling", osString, 0));
    params.add(std::make_unique<juce::AudioParameterFloat>("outputID", "Output", gainRange, 00.00f, decibels));
    params.add(std::make_unique<juce::AudioParameterFloat>("mixID", "Mix", mixRange, 100.00f, percentage));
    params.add(std::make_unique<juce::AudioParameterBool>("bypassID", "Bypass", false));
}