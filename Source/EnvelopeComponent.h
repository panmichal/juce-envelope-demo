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
    enum class Parameter
    {
        Attack,
        Decay,
        Sustain,
        Release,
        None
        
    };
    Parameter currentParameter =  Parameter::None;
    
    EnvelopePointComponent envelopePoint;
    
    Parameter cursorInParameterBoundaries(const juce::MouseEvent& e)
    {
        auto f =  std::find_if(boundaryFunctions.begin(), boundaryFunctions.end(), [&e](std::function<Parameter(const juce::MouseEvent&)> f){ return f(e) != Parameter::None; });
        return (*f)(e);
    }
    
    std::array<std::function<Parameter(const juce::MouseEvent&)>, 5> boundaryFunctions =
    {
        [this](const juce::MouseEvent& e)
        {
           juce::Point<float> attackPos = getAttackPosition();
           if (e.getMouseDownX() > attackPos.x - 10 && e.getMouseDownX() < attackPos.x + 10 &&
               e.getMouseDownY() > attackPos.y - 10 && e.getMouseDownY() < attackPos.y + 10) {
             return Parameter::Attack;
           } else {
               return Parameter::None;
           }
            
        },
        [this](const juce::MouseEvent& e)
        {
            juce::Point<float> decayPos = getDecayPosition();
            if (e.getMouseDownX() > decayPos.x - 10 && e.getMouseDownX() < decayPos.x + 10 && e.getMouseDownY() > decayPos.y - 10 && e.getMouseDownY() < decayPos.y + 10) {
                return Parameter::Decay;
            } else {
                return Parameter::None;
            }
        },
        [this](const juce::MouseEvent& e)
        {
            juce::Point<float> sustainPos = getSustainPosition();
            if (e.getMouseDownX() > sustainPos.x - 10 && e.getMouseDownX() < sustainPos.x + 10 && e.getMouseDownY() > sustainPos.y - 10 && e.getMouseDownY() < sustainPos.y + 10) {
                return Parameter::Sustain;
            } else {
                return Parameter::None;
            }
        },
        [this](const juce::MouseEvent& e)
        {
            juce::Point<float> releasePos = getReleasePosition();
            if (e.getMouseDownX() > releasePos.x - 10 && e.getMouseDownX() < releasePos.x + 10 && e.getMouseDownY() > releasePos.y - 10 && e.getMouseDownY() < releasePos.y + 10) {
                return Parameter::Release;
            } else {
               return Parameter::None;
            }
        },
        [](const juce::MouseEvent& e)
        {
            return Parameter::None;
        },
    };
};
