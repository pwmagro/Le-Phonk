/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Common/Constants.h"
#include "DSP/OTT.h"
#include "DSP/Fonz.h"
#include "DSP/Zekete.h"
#include "Common/RingBuffer.h"

//==============================================================================
/**
*/
class LePhonkAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    LePhonkAudioProcessor();
    ~LePhonkAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    inline float zeketeDistort(float sample, int idx) { return zekete.distArray[idx]->distort(sample); }

    juce::StringArray distTypes{ "Dist 1", "Dist 2", "Dist 3" };

    juce::AudioProcessorValueTreeState treeState;
    xynth::RingBuffer ringBuffer;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    xynth::OTT ott;
    xynth::Fonz fonz;
    xynth::Zekete zekete;

    std::atomic<float>* enableAtomic{ nullptr };
    std::atomic<float>* gainAtomic  { nullptr };
    float prevGain{ 0.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LePhonkAudioProcessor)
};
