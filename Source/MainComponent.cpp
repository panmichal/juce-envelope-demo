#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(envelopeController);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colours::salmon);
}

void MainComponent::resized()
{
    envelopeController.setBounds(getWidth() / 2 - 300, getHeight() / 2 - 200, 600, 400);
}
