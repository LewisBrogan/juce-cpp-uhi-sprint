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

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()

{
    addAndMakeVisible(canvas);
    canvas.setOpaque(false); 
    setSize (1024, 768);
    
    addAndMakeVisible(&loginButton);
    juce::DocumentWindow("login", juce::Colour(0xff0e345a), juce::DocumentWindow::allButtons, true);
 

    //Opens file dialog on open button click
    loginButton.onClick = [this] 
    { 
        
    };
 
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)


{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::transparentWhite);
  
    g.setFont (juce::Font (14.0f));
    g.setColour (juce::Colours::lightslategrey);
    g.drawText ("Version", getLocalBounds(), juce::Justification::bottomLeft, true);
    addAndMakeVisible(sidebar);
    addAndMakeVisible(canvas);
    

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto area = getLocalBounds();
    auto sidebarWidth = 180;
    sidebar.setBounds(area.removeFromLeft(sidebarWidth));
    loginButton.setBounds(area.removeFromBottom(30)); 
    canvas.setBounds(sidebarWidth, 0, getWidth(), getHeight());
  
}


