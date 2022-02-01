/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultiTapDelayAudioProcessorEditor::MultiTapDelayAudioProcessorEditor (MultiTapDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
    
    auto& params = processor.getParameters();
    
    AudioParameterFloat* mDryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);
    
    mDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(mDryWetParameter->range.start, mDryWetParameter->range.end);
    mDryWetSlider.setValue(*mDryWetParameter);
    addAndMakeVisible(mDryWetSlider);
    
    mDryWetSlider.onValueChange = [this, mDryWetParameter] { *mDryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [mDryWetParameter] { mDryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onDragEnd = [mDryWetParameter] { mDryWetParameter->endChangeGesture(); };

    
    AudioParameterFloat* mFeedbackParameter = (AudioParameterFloat*)params.getUnchecked(1);
    
    mFeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(mFeedbackParameter->range.start, mFeedbackParameter->range.end);
    mFeedbackSlider.setValue(*mFeedbackParameter);
    addAndMakeVisible(mFeedbackSlider);
    
    mFeedbackSlider.onValueChange = [this, mFeedbackParameter] { *mFeedbackParameter = mFeedbackSlider.getValue(); };
    mFeedbackSlider.onDragStart = [mFeedbackParameter] { mFeedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onDragEnd = [mFeedbackParameter] { mFeedbackParameter->endChangeGesture(); };
    
    
    AudioParameterFloat* mTimeParameter = (AudioParameterFloat*)params.getUnchecked(2);
    
    mDelayTimeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayTimeSlider.setRange(mTimeParameter->range.start, mTimeParameter->range.end);
    mDelayTimeSlider.setValue(*mTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);
    
    mDelayTimeSlider.onValueChange = [this, mTimeParameter] { *mTimeParameter = mDelayTimeSlider.getValue(); };
    mDelayTimeSlider.onDragStart = [mTimeParameter] { mTimeParameter->beginChangeGesture(); };
    mDelayTimeSlider.onDragEnd = [mTimeParameter] { mTimeParameter->endChangeGesture(); };
    
    
    AudioParameterFloat* mSpreadParameter = (AudioParameterFloat*)params.getUnchecked(3);
    
    mSpreadSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mSpreadSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mSpreadSlider.setRange(mSpreadParameter->range.start, mSpreadParameter->range.end);
    mSpreadSlider.setValue(*mSpreadParameter);
    mSpreadSlider.setSkewFactorFromMidPoint(250);
    addAndMakeVisible(mSpreadSlider);
    
    mSpreadSlider.onValueChange = [this, mSpreadParameter] { *mSpreadParameter = mSpreadSlider.getValue(); };
    mSpreadSlider.onDragStart = [mSpreadParameter] { mSpreadParameter->beginChangeGesture(); };
    mSpreadSlider.onDragEnd = [mSpreadParameter] { mSpreadParameter->endChangeGesture(); };
}

MultiTapDelayAudioProcessorEditor::~MultiTapDelayAudioProcessorEditor()
{
}

//==============================================================================
void MultiTapDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("MultiTap Delay", getLocalBounds(), juce::Justification::centredBottom, 1);
    
    g.drawText("Dry/Wet", ((getWidth() / 5 ) * 1) - (100 / 2), (getHeight() / 4), 100, 100, Justification::centredBottom);
    g.drawText("Feedback", ((getWidth() / 5 ) * 2) - (100 / 2), (getHeight() / 4), 100, 100, Justification::centredBottom);
    g.drawText("Delay Time", ((getWidth() / 5 ) * 3) - (100 / 2), (getHeight() / 4), 100, 100, Justification::centredBottom);
    g.drawText("Spread", ((getWidth() / 5 ) * 4) - (100 / 2), (getHeight() / 4), 100, 100, Justification::centredBottom);
}

void MultiTapDelayAudioProcessorEditor::resized()
{
    mDryWetSlider.setBounds(((getWidth() / 5 ) * 1) - (100 / 2), (getHeight() / 4), 100, 100);
    mFeedbackSlider.setBounds(((getWidth() / 5 ) * 2) - (100 / 2), (getHeight() / 4), 100, 100);
    mDelayTimeSlider.setBounds(((getWidth() / 5 ) * 3) - (100 / 2), (getHeight() / 4), 100, 100);
    mSpreadSlider.setBounds(((getWidth() / 5 ) * 4) - (100 / 2), (getHeight() / 4), 100, 100);
}
