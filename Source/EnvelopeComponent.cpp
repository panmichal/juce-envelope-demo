/*
  ==============================================================================

    EnvelopeComponent.cpp
    Created: 11 Dec 2020 10:25:00pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeComponent.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

EnvelopeComponent::~EnvelopeComponent()
{
}

void EnvelopeComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightblue);
    juce::Path path;
    path.startNewSubPath (juce::Point<float> (0, getHeight()));
    path.lineTo(attack, getHeight() - ENVELOPE_HEIGHT);
    path.lineTo(attack + decay, getHeight() - sustain);
    path.lineTo(attack + decay + SUSTAIN_WIDTH, getHeight() - sustain);
    path.lineTo(attack + decay + SUSTAIN_WIDTH + release, getHeight());
    
    g.strokePath(path, juce::PathStrokeType(4));
    addChildComponent(envelopePoint);
}

void EnvelopeComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    

}

void EnvelopeComponent::mouseMove(const juce::MouseEvent & e)
{
    juce::Point<float> attackPos = getAttackPosition();
    juce::Point<float> decayPos = getDecayPosition();
    juce::Point<float> sustainPos = getSustainPosition();
    juce::Point<float> releasePos = getReleasePosition();

    if (e.getPosition().x > attackPos.x - 10 && e.getPosition().x < attackPos.x + 10 &&
        e.getPosition().y > attackPos.y - 10 && e.getPosition().y < attackPos.y + 10) {
        envelopePoint.setBounds(attackPos.x - 10,attackPos.y - 10, 20, 20);
        envelopePoint.setVisible(true);
    } else if (e.getPosition().x > sustainPos.x - 10 && e.getPosition().x < sustainPos.x + 10 && e.getPosition().y > sustainPos.y - 10 && e.getPosition().y < sustainPos.y + 10) {
        envelopePoint.setBounds(sustainPos.x - 10, sustainPos.y - 10, 20, 20);
        envelopePoint.setVisible(true);
    } else if (e.getPosition().x > decayPos.x - 10 && e.getPosition().x < decayPos.x + 10 && e.getPosition().y > decayPos.y - 10 && e.getPosition().y < decayPos.y + 10) {
        envelopePoint.setBounds(decayPos.x - 10, decayPos.y - 10, 20, 20);
        envelopePoint.setVisible(true);
    } else if (e.getPosition().x > releasePos.x - 10 && e.getPosition().x < releasePos.x + 10 && e.getPosition().y > releasePos.y - 10 && e.getPosition().y < releasePos.y + 10) {
        envelopePoint.setBounds(releasePos.x - 10, releasePos.y - 10, 20, 20);
        envelopePoint.setVisible(true);
    } else {
        envelopePoint.setVisible(false);
    }
}

void EnvelopeComponent::mouseDrag(const juce::MouseEvent & e)
{
    if (currentParameter == Parameter::Attack) {
        attack = std::max(e.getPosition().x, 0);
        envelopePoint.setBounds(attack - 10, getHeight() - 200 - 10, 20, 20);
        repaint();
    } else if (currentParameter == Parameter::Decay) {
        decay = std::max(attack, (float)e.getPosition().x) - attack;
        envelopePoint.setBounds(attack + decay - 10, getHeight() - sustain - 10, 20, 20);
        repaint();
    } else if (currentParameter == Parameter::Sustain) {
        sustain = std::min(getHeight() - e.getPosition().y, ENVELOPE_HEIGHT);
        envelopePoint.setBounds(attack + decay + SUSTAIN_WIDTH - 10, getHeight() - sustain - 10, 20, 20);
        repaint();
    } else if (currentParameter == Parameter::Release) {
        release = e.getPosition().x - SUSTAIN_WIDTH - decay - attack;
        envelopePoint.setBounds(attack + decay + SUSTAIN_WIDTH + release - 10, getHeight() - 10, 20, 20);
        repaint();
    }
}

void EnvelopeComponent::mouseDown(const juce::MouseEvent &e)
{
    juce::Point<float> attackPos = getAttackPosition();
    juce::Point<float> decayPos = getDecayPosition();
    juce::Point<float> sustainPos = getSustainPosition();
    juce::Point<float> releasePos = getReleasePosition();
    
    if (e.getMouseDownX() > attackPos.x - 10 && e.getMouseDownX() < attackPos.x + 10 &&
        e.getMouseDownY() > attackPos.y - 10 && e.getMouseDownY() < attackPos.y + 10) {
        currentParameter = Parameter::Attack;
    } else if (e.getMouseDownX() > sustainPos.x - 10 && e.getMouseDownX() < sustainPos.x + 10 && e.getMouseDownY() > sustainPos.y - 10 && e.getMouseDownY() < sustainPos.y + 10) {
        currentParameter = Parameter::Sustain;
    } else if (e.getMouseDownX() > decayPos.x - 10 && e.getMouseDownX() < decayPos.x + 10 && e.getMouseDownY() > decayPos.y - 10 && e.getMouseDownY() < decayPos.y + 10) {
        currentParameter = Parameter::Decay;
    } else if (e.getMouseDownX() > releasePos.x - 10 && e.getMouseDownX() < releasePos.x + 10 && e.getMouseDownY() > releasePos.y - 10 && e.getMouseDownY() < releasePos.y + 10) {
        currentParameter = Parameter::Release;
    } else {
        currentParameter = Parameter::None;
    }
}

void EnvelopeComponent::mouseUp(const juce::MouseEvent &e)
{
    currentParameter = Parameter::None;
}

juce::Point<float> EnvelopeComponent::getAttackPosition()
{
    return juce::Point<float>(attack, getHeight() - 200);
}

juce::Point<float> EnvelopeComponent::getDecayPosition()
{
    return juce::Point<float>(attack + decay, getHeight() - sustain);
}

juce::Point<float> EnvelopeComponent::getSustainPosition()
{
    return juce::Point<float>(attack + decay + SUSTAIN_WIDTH, getHeight() - sustain);
}

juce::Point<float> EnvelopeComponent::getReleasePosition()
{
    return juce::Point<float>(attack + decay + SUSTAIN_WIDTH + release, getHeight());
}
