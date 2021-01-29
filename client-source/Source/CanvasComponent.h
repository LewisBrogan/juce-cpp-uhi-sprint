/*
  ==============================================================================

    CanvasComponent.h
    Created: 10 Dec 2020 12:00:44pm
    Author:  calum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DraggableImage.h"
//==============================================================================
/*
*/
class CanvasComponent  : public juce::Component
{
public:
    CanvasComponent();
    ~CanvasComponent() override;

   

    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    juce::TextButton testbutton;
    std::vector<DraggableImage*> canvasimages;
    juce::File localImage;
    juce::Image compimage;
    
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CanvasComponent)
};
