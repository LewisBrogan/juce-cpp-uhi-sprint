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

/*
  ==============================================================================

    SideBar.h
    Created: 7 Dec 2020 7:31:15pm
    Author:  smile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SideBar : public juce::Component
{
    public:
        SideBar();
        ~SideBar() override;
        void paint(juce::Graphics& g) override;
        void resized();
        std::vector<juce::String> getImgUrls(const juce::URL& url);
        void createImgQuery(std::vector<juce::String>&);
        void clearThumbnails();


    private:
        //creates basic search box input and search button to trigget onclick()
        juce::TextEditor searchBox;
        juce::TextButton searchButton{"Search"};
        juce::String response;
        juce::Image image;
        std::vector<juce::ImageComponent*> imageThumbnails;
        juce::ImageComponent imageComponent;
        juce::Label debugLabel; //DELETE BEFORE RELEASING
};