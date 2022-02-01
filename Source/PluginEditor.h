/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultiTapDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MultiTapDelayAudioProcessorEditor (MultiTapDelayAudioProcessor&);
    ~MultiTapDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Slider mDryWetSlider;
    Slider mFeedbackSlider;
    Slider mDelayTimeSlider;
    Slider mSpreadSlider;
    
    MultiTapDelayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiTapDelayAudioProcessorEditor)
};
