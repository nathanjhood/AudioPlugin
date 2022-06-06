/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p, APVTS& apvts, juce::UndoManager& um)
    : juce::AudioProcessorEditor(&p), audioProcessor(p), state(apvts), undoManager(um), knobComponents(p, apvts), buttonComponents(p, apvts), comboBoxComponents(p, apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (500, 600);
    addAndMakeVisible(buttonComponents);
    addAndMakeVisible(knobComponents);
    addAndMakeVisible(comboBoxComponents);
    addAndMakeVisible(undoButton);
    addAndMakeVisible(redoButton);
    undoButton.onClick = [this] { undoManager.undo(); };
    redoButton.onClick = [this] { undoManager.redo(); };
    setResizable(true, false);

    startTimerHz(24);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::timerCallback()
{
    knobComponents.resized();
    buttonComponents.resized();
    comboBoxComponents.resized();
    undoManager.beginNewTransaction();
}

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::darkslategrey);

    //// draw an outline around the component
    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 5);

    // Add project info text to background here
    g.setColour (juce::Colours::antiquewhite);
    g.setFont (15.0f);
    g.drawFittedText(ProjectInfo::companyName, getLocalBounds(), juce::Justification::topLeft, 1);
    g.drawFittedText(ProjectInfo::projectName, getLocalBounds(), juce::Justification::topRight, 1);
    g.drawFittedText(ProjectInfo::versionString, getLocalBounds(), juce::Justification::bottomRight, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto width = getWidth();
    auto height = getHeight();
    auto bounds = getBounds();
    auto left = 0;
    auto right = getRight();
    auto bottom = getBottom();

    // Positions...

    auto absCentreX = getWidth() / 3;
    auto absCentreY = getHeight() / 3;

    auto absLeftX = 0;
    auto absRightX = getRight();

    auto absTopY = 0;
    auto absBottomY = getBottom();

    // Sizes...

    auto wholeW = getWidth();
    auto wholeY = getHeight();

    auto halfW = getWidth() / 2;
    auto halfH = getHeight() / 2;

    auto thirdW = getWidth() / 3;
    auto thirdH = getHeight() / 3;

    knobComponents.setBounds(left, absCentreY, wholeW, thirdH);
    buttonComponents.setBounds(halfW, 1 / bottom, halfW, height / 4);
    comboBoxComponents.setBounds(halfW, bottom - (halfH /2) , halfW, height / 4);


    auto r = getLocalBounds();

    auto buttons = r.removeFromBottom(20);
    undoButton.setBounds(buttons.removeFromLeft(100));
    redoButton.setBounds(buttons.removeFromLeft(100));
}
