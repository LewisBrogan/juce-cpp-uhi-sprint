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

    SideBar.cpp
    Created: 7 Dec 2020 7:31:15pm
    Author:  smile

  ==============================================================================
*/

#include "SideBar.h"
#include <JuceHeader.h>
#include "external-includes/json.hpp"

SideBar::SideBar() {
    searchBox.setText("http://localhost:8081/");
    
    searchButton.onClick = [this]() {
        clearThumbnails();
        juce::URL url = "http://localhost:8081/get-image";
        
        url = url.withParameter("tag", searchBox.getText());
        DBG("SearchButton : OnClick(): " + url.toString(false));    
        createImgQuery(getImgUrls(url));
       
        
    };   

}
SideBar::~SideBar()
{
}   

void SideBar::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkslategrey);
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
    g.drawText("SideBar", getLocalBounds(), juce::Justification::centred, true);
    addAndMakeVisible(searchBox);
    addAndMakeVisible(searchButton);
    addAndMakeVisible(debugLabel);
    
}


void SideBar::resized() {
    auto area = getLocalBounds();
    auto margins = 5;
    auto inputHeights = 30;
    auto buttonHeights = 30;
    searchBox.setBounds(area.removeFromTop(inputHeights).reduced(margins));
    searchButton.setBounds(area.removeFromTop(buttonHeights).reduced(margins));
    debugLabel.setBounds(area.removeFromTop(200).reduced(margins));
    if (imageThumbnails.size()) {
        for (size_t i = 0; i < imageThumbnails.size(); i++)
        {
            imageThumbnails[i]->setBounds(area.removeFromTop(100).reduced(margins));
        }
    }
    
}


std::vector<juce::String> SideBar::getImgUrls(const juce::URL& url) {
    DBG("Search called with url " + url.toString(false));
    juce::StringPairArray responseHeaders;
    int statusCode = 0;
    std::vector<juce::String> imgUrls;
    auto stream = std::unique_ptr<juce::InputStream>(url.createInputStream(false, nullptr, nullptr, {}, 10000, &responseHeaders, &statusCode));

    if (stream && statusCode == 200) {
        response = juce::String(stream->readEntireStreamAsString());
        nlohmann::json json_response = nlohmann::json::parse(response.toStdString());
        juce::String debugString;
        for (int i = 0; i < json_response["docs"].size(); i++) {
            response = json_response["docs"][i]["imageUrl"].dump();
            response = "http://" + response.replace("\"", "");
            DBG(response);
            imgUrls.insert(imgUrls.end(),response);
            debugString += "\n" + imgUrls[i];
        }        
        debugLabel.setText(debugString, juce::sendNotification);
        repaint();
        return imgUrls;
    }
    else
        DBG("Error performing get request to server");
    return imgUrls;
}


void SideBar::createImgQuery(std::vector <juce::String>& imgUrls) {
    if (imgUrls.size()) {
        DBG("createImgQuery(): getting urls");
        
        
        resized();
        for (size_t i = 0; i < imgUrls.size(); i++)
        {
            DBG(i + "Url cycle");
            juce::URL url(imgUrls[i].toStdString());
            juce::MemoryBlock memoryBlock;
            if (url.readEntireBinaryStream(memoryBlock)) {
                DBG("reading stream");
                juce::ImageComponent tempComponent;
                imageThumbnails.push_back(new juce::ImageComponent());
                imageThumbnails.back()->setImage(juce::ImageFileFormat::loadFrom(memoryBlock.getData(), memoryBlock.getSize()));
                addAndMakeVisible(imageThumbnails.back());
            }
        }
        resized();
    }
}

void SideBar::clearThumbnails() {
    DBG("clearThumbnails() called");
    for (size_t i = 0; i < imageThumbnails.size(); i++) {
        DBG(imageThumbnails.size());
        removeChildComponent(imageThumbnails[i]);
    }
    resized();
    
    imageThumbnails.clear();
  
}