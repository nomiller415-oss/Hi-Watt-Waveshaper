#pragma once

#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>
#if JUCE_DEBUG
    #include "melatonin_inspector/melatonin_inspector.h"
#endif


//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void resized() override;
    void parameterValueChanged (int parameterIndex, float newValue);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processorRef;

    juce::WebSliderRelay gainSliderRelay { "GainKnob" };
    juce::WebSliderRelay trebleSliderRelay { "TrebleKnob" };
    juce::WebSliderRelay bassSliderRelay { "BassKnob" };
    juce::WebBrowserComponent webView;
        

    

    std::unique_ptr<juce::WebSliderParameterAttachment> gainAttachment;
    std::unique_ptr<juce::WebSliderParameterAttachment> trebleAttachment;
    std::unique_ptr<juce::WebSliderParameterAttachment> bassAttachment;


    

    // Melatonin Inspector for debugging and UI Design
    #if JUCE_DEBUG
        std::unique_ptr<melatonin::Inspector> inspector;
        juce::TextButton inspectButton { "Inspect the UI" };
    #endif
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
