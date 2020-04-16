/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginTestAudioProcessorEditor::PluginTestAudioProcessorEditor (PluginTestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100,20);
    gainSlider.setRange(-48.0f, 0.0f, 0.1);
    gainSlider.setValue(-5.0f);
    addAndMakeVisible(gainSlider);
}

PluginTestAudioProcessorEditor::~PluginTestAudioProcessorEditor()
{
    
}

//==============================================================================
void PluginTestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
       
}

void PluginTestAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

float convertFromDb(float gainInDB) {
    float res = 0.0;
    res = pow(10, gainInDB / 20);
    return res;
}

//void PluginTestAudioProcessorEditor::sliderValueChanged(Slider* slider)
//{
//   /* if (slider == &gainSlider) {
//        processor.gainValue = convertFromDb(slider->getValue());
//    }*/
//}
