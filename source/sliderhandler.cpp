#include "SliderFieldHandler.hpp"

void SliderFieldHandler::addSliderRow(wxString label_text, 
    wxSlider* slider_ptr, int id, int min_val, int max_val, int initial_val)
{
    wxStaticText* label = new wxStaticText(sliderPanel, wxID_ANY, label_text); 
    slider_ptr = new wxSlider(sliderPanel, id, initial_val, min_val, 
        max_val, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS); 
    fieldGridSizer->Add(label, 0, wxALIGN_LEFT | wxTOP, 5); 
    fieldGridSizer->Add(slider_ptr, 1, wxEXPAND | wxBOTTOM, 5); 
}

SliderFieldHandler::SliderFieldHandler(wxFrame* parent)
{
    this->parent = parent;
    sliderPanel = new wxPanel(parent, wxID_ANY); 
    fieldGridSizer = new wxFlexGridSizer(2, 10, 10); 

    //Volume
    addSliderRow("Volume", volumeSlider, -1, 0, 100, 80); 

    //ADSR
    addSliderRow("Attack (ms)", attackSlider, -1, 0, 1000, 10); 
    addSliderRow("Decay (ms)", decaySlider, -1, 0, 1000, 50); 
    addSliderRow("Sustain (%)", sustainSlider, -1, 0, 100, 75); 
    addSliderRow("Release (ms)", releaseSlider, -1, 0, 2000, 500); 

    //Pitch
    addSliderRow("Pitch Shift (st)", pitchSlider, -1, -12, 12, 0); 

    //Cutoff, Resonance
    addSliderRow("Filter Cutoff (Hz)", cutoffSlider, -1, 20, 20000, 5000); 
    addSliderRow("Filter Resonance", resonanceSlider, -1, 0, 10, 1); 

    fieldGridSizer->AddGrowableCol(1); 
    
    sliderPanel->SetSizer(fieldGridSizer);
    sliderPanel->Layout(); 
}

wxPanel* SliderFieldHandler::getSliderPanel()
{
    return sliderPanel;
}