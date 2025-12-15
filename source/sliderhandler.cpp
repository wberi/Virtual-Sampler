#include "AppBase.hpp"
#include "KeyFieldHandler.hpp"
#include "SliderFieldHandler.hpp"
#include "Key.hpp"
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/string.h>

//Constructor implementation was written with AI assistance!
SliderFieldHandler::SliderFieldHandler(wxFrame* parent): wxPanel(parent, wxID_ANY)
{
    this->parent = parent;
    fieldGridSizer = new wxFlexGridSizer(2, 10, 10); 

    selectedName = new wxStaticText(this, wxID_ANY, "No key selected");
    wxFont font = selectedName->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    font.SetPointSize(font.GetPointSize() + 2);
    selectedName->SetFont(font);

    fieldGridSizer->Add(selectedName, 1, 0, 5); 
    fieldGridSizer->AddSpacer(1);

    //Volume slider
    addSliderRow("Volume", "The volume of the sound currently playing.", volumeSlider, -1, 0, 100, 80);
    volumeSlider->Bind(wxEVT_SLIDER, &SliderFieldHandler::setVolume, this);

    //Pitch slider
    addSliderRow("Pitch Shift", "The pitch of the sound currently playing." ,pitchSlider, -1, -12, 12, 0); 
    pitchSlider->Bind(wxEVT_SLIDER, &SliderFieldHandler::setPitch, this);

    //Pan slider
    addSliderRow("Panning", "The direction the sound is playing from." ,panSlider, -1, -1, 1, 0); 
    panSlider->Bind(wxEVT_SLIDER, &SliderFieldHandler::setPan, this);

    //Cutoff slider
    addSliderRow("Filter Cutoff (Hz)","The frequency level, required for the sound to get cut off.", cutoffSlider, -1, 0, 5000, 0); 
    cutoffSlider->Bind(wxEVT_SLIDER, &SliderFieldHandler::setCutoff, this);

    //Make second column flexible
    fieldGridSizer->AddGrowableCol(1); 

    //Create and bind Key reset button
    resetButton = new wxButton(this, wxID_ANY, "Rebind Key");
    resetButton->SetForegroundColour(*wxWHITE);
    resetButton->SetBackgroundColour(*wxRED);
    //bind
    fieldGridSizer->Add(resetButton, 0, wxALIGN_LEFT, 5); 
    
    //Set this sizer
    this->SetSizer(fieldGridSizer);
    this->Layout();
}

//Set the currently displayed Key
void SliderFieldHandler::SetCurrentKey(Key* key)
{
    if(key)
    {
        current_key_ptr = key;
        current_group_ptr = key->getSoundGroupPtr();
    }
}

//Update the visuals from the current key pointer
void SliderFieldHandler::UpdateControlsFromKey()
{
    if(!current_key_ptr) 
    {
        selectedName->SetLabel("Selection empty");
        return;
    }

    //Load values
    volumeSlider->SetValue(current_key_ptr->getVolume());
    pitchSlider->SetValue(current_key_ptr->getPitchShift());
    panSlider->SetValue(current_key_ptr->getPan());
    cutoffSlider->SetValue(current_key_ptr->getCutoff());

    selectedName->SetLabel("Selected " + current_key_ptr->GetLabelText());
}

//Events implementation: Now saves to Key and updates group pointer
void SliderFieldHandler::setVolume(wxCommandEvent& event)
{
    if(!current_group_ptr || !current_key_ptr)
    {
        return;
    }
    
    current_key_ptr->setVolume(volumeSlider->GetValue());
    ma_sound_group_set_volume(current_group_ptr, current_key_ptr->getVolume() / 100.0);
}


void SliderFieldHandler::setPitch(wxCommandEvent& event)
{
    if(!current_group_ptr || !current_key_ptr) 
    {
        return;
    }

    current_key_ptr->setPitchShift(pitchSlider->GetValue());
    float pitch_factor = pow(2.0, current_key_ptr->getPitchShift() / 12.0);
    ma_sound_group_set_pitch(current_group_ptr, pitch_factor);
}

void SliderFieldHandler::setPan(wxCommandEvent& event)
{
    if(!current_group_ptr || !current_key_ptr) 
    {
        return;
    }
    
    current_key_ptr->setPan(panSlider->GetValue());
    ma_sound_group_set_pan(current_group_ptr, current_key_ptr->getPan());
}

void SliderFieldHandler::setCutoff(wxCommandEvent& event)
{
    if(!current_group_ptr || !current_key_ptr) 
    {
        return;
    }
    
    current_key_ptr->setCutoff(cutoffSlider->GetValue());
    current_key_ptr->setNewFilterFreq();
}

//Add new slider to the panel
void SliderFieldHandler::addSliderRow(wxString label_text, wxString tooltip_text,
    wxSlider*& slider_ptr, int id, int min_val, int max_val, int initial_val)
{
    wxStaticText* label = new wxStaticText(this, wxID_ANY, label_text);
    label->SetToolTip(tooltip_text);
    slider_ptr = new wxSlider(this, id, initial_val, min_val, 
        max_val, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS); 
    fieldGridSizer->Add(label, 0, wxALIGN_LEFT | wxTOP, 5); 
    fieldGridSizer->Add(slider_ptr, 1, wxEXPAND | wxBOTTOM, 5); 
}

wxButton* SliderFieldHandler::getResetButton()
{
    return resetButton;
}

Key* SliderFieldHandler::getCurrentKeyPtr()
{
    return current_key_ptr;
}