/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#define MAX_DELAY_TIME 2

//==============================================================================
/**
*/
class MultiTapDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MultiTapDelayAudioProcessor();
    ~MultiTapDelayAudioProcessor() override;

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

    float linear_interpolation(float inX, float inY, float inPhase);


private:
    float mTimeSmoothed;
    float mDryWetSmoothed;
    float mSpreadSmoothed;
    
    AudioParameterFloat* mTimeParameter;
    AudioParameterFloat* mDryWetParameter;
    AudioParameterFloat* mFeedbackParameter;
    AudioParameterFloat* mSpreadParameter;

    
    float mDryWet;
    
    float mFeedbackLeft;
    float mFeedbackRight;
    
    float mReadHead1, mReadHead2, mReadHead3, mReadHead4;
    float mDelayTimeInSamples;
    
    int mCircularBufferLength;
    int mWriteHead;
    float* mCircularBufferLeft;
    float* mCircularBufferRight;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiTapDelayAudioProcessor)
};
