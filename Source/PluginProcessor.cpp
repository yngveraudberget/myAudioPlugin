/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginTestAudioProcessor::PluginTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    treeState(*this, nullptr, "PARAMETER", { createParamterLayout()})
   
    //treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 0.0f, -15.0f)})
#endif
{
    treeState.state = ValueTree("savedparams");
}

PluginTestAudioProcessor::~PluginTestAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout PluginTestAudioProcessor::createParamterLayout() {
    std::vector <std::unique_ptr<RangedAudioParameter>> params;
    auto gainParam = std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 0.0f, -15.0f);
    params.push_back(std::move(gainParam));
    return { params.begin(), params.end() };
}

//==============================================================================
const String PluginTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginTestAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginTestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PluginTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginTestAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto channelData = buffer.getWritePointer (channel);
        std::atomic<float>* slider = treeState.getRawParameterValue(GAIN_ID);
      
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = buffer.getSample(channel, sample) * Decibels::decibelsToGain<float>(*slider);
        }
    }
}

//==============================================================================
bool PluginTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginTestAudioProcessor::createEditor()
{
    return new PluginTestAudioProcessorEditor (*this);
}

//==============================================================================
void PluginTestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    std::unique_ptr<XmlElement> xml(treeState.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> theParams = getXmlFromBinary(data, sizeInBytes);
    if (theParams != nullptr) {
        if (theParams->hasTagName(treeState.state.getType())) {
            treeState.state = ValueTree::fromXml(*theParams);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginTestAudioProcessor();
}
