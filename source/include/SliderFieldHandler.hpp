#ifndef SLIDERFIELDHANDLER_HPP
#define SLIDERFIELDHANDLER_HPP

#include <miniaudio.h>
#include "Key.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//Refactoring of this file from AppBase.hpp was done with AI assistance!

/////////////////////////////////////////////////
/// Stores and handles all operation related to sliders.
/////////////////////////////////////////////////
class SliderFieldHandler: public wxPanel
{
    //Parent object
    wxFrame* parent;

    //Content panel
    wxFlexGridSizer* fieldGridSizer;

    //Important sound references
    ma_sound_group* current_group_ptr = nullptr;
    Key* current_key_ptr = nullptr;

    //Display selected name
    wxStaticText* selectedName;

    //Volume slider
    wxSlider* volumeSlider;
    
    //Pitch slider
    wxSlider* pitchSlider;

    //Pan slider
    wxSlider* panSlider;

    //ADSR sliders
    wxSlider* attackSlider;
    wxSlider* decaySlider;
    wxSlider* sustainSlider;
    wxSlider* releaseSlider;

    //Filter slider
    wxSlider* cutoffSlider;

    //Reset button
    wxButton* resetButton;

    //Helper functions
    void addSliderRow(wxString label_text, wxString tooltip_text,
        wxSlider*& slider_ptr, int id, int min_val, int max_val, int initial_val);
    void actualizeFadeOut();

public:
    //Constructor
    SliderFieldHandler(wxFrame* parent);

    //Methods for managing Key values
    void SetCurrentKey(Key* key);
    void UpdateControlsFromKey(); 
    void SaveControlsToKey(); 

    //Events
    void setVolume(wxCommandEvent& event);
    void setPitch(wxCommandEvent& event);
    void setPan(wxCommandEvent& event);
    void setCutoff(wxCommandEvent& event);

    //Getters
    wxButton* getResetButton();
    Key* getCurrentKeyPtr();
};

#endif