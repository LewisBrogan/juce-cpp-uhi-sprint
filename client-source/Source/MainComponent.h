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
#include "SideBar.h"
#include "CanvasComponent.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
//==============================================================================
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton loginButton{ "login" };
    juce::Image testimage;
    juce::File localImage;
    SideBar sidebar;
    CanvasComponent canvas;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
