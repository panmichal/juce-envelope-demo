/*
  ==============================================================================

    EnvelopePointComponent.h
    Created: 11 Dec 2020 11:17:25pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvelopePointComponent  : public juce::Component
{
public:
    EnvelopePointComponent();
    ~EnvelopePointComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent & e) override;
    void mouseUp(const juce::MouseEvent & e) override;
    bool getIsDragged() const { return isDragged; };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopePointComponent)
    
    bool isDragged = false;
};
