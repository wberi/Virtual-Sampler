#ifndef SLIDERFIELDHANDLER_HPP
#define SLIDERFIELDHANDLER_HPP

#include <miniaudio.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// Forward declaration of Key class
class Key;

// Refactoring of this file from AppBase.hpp was done with AI assistance!
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
    
    //ADSR sliders
    wxSlider* attackSlider;
    wxSlider* decaySlider;
    wxSlider* sustainSlider;
    wxSlider* releaseSlider;
    
    //Pitch slider
    wxSlider* pitchSlider;
    
    //Filter sliders
    wxSlider* cutoffSlider;
    wxSlider* resonanceSlider;

    //Reset button
    wxButton* resetButton;

    //Helper functions
    void addSliderRow(wxString label_text, wxString tooltip_text,
        wxSlider*& slider_ptr, int id, int min_val, int max_val, int initial_val);

public:
    //Constructor
    SliderFieldHandler(wxFrame* parent);

    //Methods for managing Key values
    void SetCurrentKey(Key* key);
    void UpdateControlsFromKey(); 
    void SaveControlsToKey(); 

    //Events
    void setVolume(wxCommandEvent& event);
    void setAttack(wxCommandEvent& event);
    void setDecay(wxCommandEvent& event);
    void setSustain(wxCommandEvent& event);
    void setRelease(wxCommandEvent& event);
    void setPitch(wxCommandEvent& event);
    void setCutoff(wxCommandEvent& event);
    void setResonance(wxCommandEvent& event);

    //Getters
    wxButton* getResetButton();
    Key* getCurrentKeyPtr();
};

#endif