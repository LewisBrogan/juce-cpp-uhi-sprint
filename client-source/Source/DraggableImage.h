/*
  ==============================================================================

    DraggableImage.h
    Created: 15 Dec 2020 1:06:58am
    Author:  Vittorio Rivabella

  ==============================================================================
*/

//   Modern Reference Assistant - Shoot, search, create beautiful moodboards
//   Copyright (c) 2020, Calum MacIntosh, Alexander Wedekind, Damir Elsik,
//   Lewis Brogan and Vittorio Rivabella. Licensed Under GNU GPL.

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as published
//     by the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.

//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DraggableImage  : public juce::Component
{
public:
    DraggableImage()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addMouseListener(this, true);

    }

    ~DraggableImage() override
    {
    }

    void setImage(juce::Image& image, juce::RectanglePlacement placementToUse) {
        imageComponent.setImage(image, placementToUse );
        repaint();
    }
    void paint (juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::red);
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        addAndMakeVisible(imageComponent);
    }

    void resized() override
    {
        imageComponent.setBounds(getLocalBounds());
        constrainer.setMinimumOnscreenAmounts(20, 20, 20, 100);
        DBG("Resized called from draggable");
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

    


    
    void mouseDown(const juce::MouseEvent& e) override {
        dragger.startDraggingComponent(&imageComponent, e);
        DBG("starting drag operations");
    }
    void mouseDrag(const juce::MouseEvent& e) override {
        dragger.dragComponent(&imageComponent, e, &constrainer);
        DBG("dragging component");
    }
    
private:
    juce::ComponentBoundsConstrainer constrainer;
    juce::ComponentDragger dragger;
    juce::ImageComponent imageComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DraggableImage)
};
