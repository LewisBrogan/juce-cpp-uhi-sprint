/*
  ==============================================================================

    CanvasComponent.cpp
    Created: 10 Dec 2020 12:00:44pm
    Author:  calum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CanvasComponent.h"

//==============================================================================
CanvasComponent::CanvasComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    testbutton.setButtonText("test");
    addAndMakeVisible(testbutton);
    setInterceptsMouseClicks(false, true);
   

    testbutton.onClick = [this]
    {
        juce::FileChooser imgChooser("Please select the image you want to open", juce::File(), "*.png;*.jpg");

        if (imgChooser.browseForFileToOpen())
        {
            localImage = imgChooser.getResult();
            //below is soley for seeing if the filename is correct.
            juce::String imagefilename = localImage.getFileNameWithoutExtension();
            juce::String extension = localImage.getFileExtension();
            DBG("Extension is: " << extension << " Filename is: " << imagefilename);
            compimage = juce::ImageFileFormat::loadFrom(localImage);

            //imgcomp.setImage(compimage, juce::RectanglePlacement::Flags::xMid + juce::RectanglePlacement::Flags::yMid);
            canvasimages.push_back(new DraggableImage);
            DBG("Drawing new image");
            canvasimages.back()->setImage(compimage, juce::RectanglePlacement::Flags::xMid + juce::RectanglePlacement::Flags::yMid);
            repaint();
      
            
        }
        else
        {
            DBG("No file selected");
        }  
    };
    
}

CanvasComponent::~CanvasComponent()
{
}

void CanvasComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    if (canvasimages.size()) {
        for (size_t i = 0; i < canvasimages.size(); i++)
        {
            addAndMakeVisible(canvasimages[i]);
        }
    }
    DBG("Repaint from canvas");
    resized();

   
}


void CanvasComponent::resized()
{
    
    auto area = getLocalBounds();
    testbutton.setBounds(10, 10, 70, 20);
    auto imageSize = 90;
    if (canvasimages.size() > 0) {
        for (size_t i = 0; i < canvasimages.size(); i++)
        {
         DraggableImage* tempComponent = canvasimages[i];
           tempComponent->setBounds(area.removeFromBottom(imageSize));
        }
    }
        
}



