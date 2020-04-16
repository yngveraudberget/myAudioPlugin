/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginTestAudioProcessorEditor : public AudioProcessorEditor
{
public:
	PluginTestAudioProcessorEditor(PluginTestAudioProcessor&);
	~PluginTestAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	//void sliderValueChanged(Slider* slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	PluginTestAudioProcessor& processor;
	Slider gainSlider;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginTestAudioProcessorEditor)
public:
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
};
