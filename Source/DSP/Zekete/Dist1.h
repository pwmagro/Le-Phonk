/*
  ==============================================================================

    Dist1.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"

namespace xynth
{
class Dist1 : public DistTemplate
{
public:
    Dist1();
    ~Dist1() = default;

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::ProcessContextReplacing<float>& context) override;
    inline float distort(float sample) override { return std::tanh(sample); }

    void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

private:
    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    std::atomic<float>* paramAtomic{ nullptr };

    enum FiltersEnum { before, after };
};
} // namespace xynth