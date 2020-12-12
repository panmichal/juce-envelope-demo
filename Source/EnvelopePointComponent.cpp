/*
  ==============================================================================

    EnvelopePointComponent.cpp
    Created: 11 Dec 2020 11:17:25pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopePointComponent.h"

//==============================================================================
EnvelopePointComponent::EnvelopePointComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setInterceptsMouseClicks(false, false);

}

EnvelopePointComponent::~EnvelopePointComponent()
{
}

void EnvelopePointComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::red);
    g.drawEllipse(0, 0, 20, 20, 2);
}

void EnvelopePointComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void EnvelopePointComponent::mouseDown(const juce::MouseEvent &e)
{
    DBG("POINT DOWN");
}

void EnvelopePointComponent::mouseUp(const juce::MouseEvent &e)
{
    DBG("POINT UP");
}
