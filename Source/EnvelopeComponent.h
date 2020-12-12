/*
  ==============================================================================

    EnvelopeComponent.h
    Created: 11 Dec 2020 10:25:00pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EnvelopePointComponent.h"

#define SUSTAIN_WIDTH 100
#define ENVELOPE_HEIGHT 200

//==============================================================================
/*
*/
class EnvelopeComponent  : public juce::Component
{
public:
    EnvelopeComponent();
    ~EnvelopeComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseMove(const juce::MouseEvent & e) override;
    void mouseDown(const juce::MouseEvent & e) override;
    void mouseUp(const juce::MouseEvent & e) override;
    void mouseDrag(const juce::MouseEvent & e) override;
    juce::Point<float> getAttackPosition();
    juce::Point<float> getDecayPosition();
    juce::Point<float> getSustainPosition();
    juce::Point<float> getReleasePosition();
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeComponent)
    
    float attack = 100;
    float decay = 50;
    float sustain = 100;
    float release = 120;
    
    bool isChangingAttack = false;
    enum ParameterToChange { ATTACK, DECAY, SUSTAIN, RELEASE, NONE };
    ParameterToChange currentParameter = NONE;
    
    EnvelopePointComponent envelopePoint;
};
