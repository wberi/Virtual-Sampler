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
    // Fields parent object
    wxFrame* parent;

    // Content panel
    wxFlexGridSizer* fieldGridSizer;

    // Sound Group Reference
    ma_sound_group* current_group_ptr = nullptr;
    Key* current_key_ptr = nullptr;

    // Volume slider
    wxSlider* volumeSlider;
    
    // ADSR sliders
    wxSlider* attackSlider;
    wxSlider* decaySlider;
    wxSlider* sustainSlider;
    wxSlider* releaseSlider;
    
    // Pitch slider
    wxSlider* pitchSlider;
    
    // Filter sliders
    wxSlider* cutoffSlider;
    wxSlider* resonanceSlider;

    // Helper functions
    void addSliderRow(wxString label_text, wxString tooltip_text,
        wxSlider*& slider_ptr, int id, int min_val, int max_val, int initial_val);

public:
    // ctor (Updated: Removed ma_sound_group* argument)
    SliderFieldHandler(wxFrame* parent);

    // New Key/Group management methods
    void SetCurrentKey(Key* key);
    void UpdateControlsFromKey(); 
    void SaveControlsToKey(); 

    // events
    void setVolume(wxCommandEvent& event);
    void setAttack(wxCommandEvent& event);
    void setDelay(wxCommandEvent& event); // Note: Should probably be setDecay
    void setSustain(wxCommandEvent& event);
    void setRelease(wxCommandEvent& event);
    void setPitch(wxCommandEvent& event);
    void setCutoff(wxCommandEvent& event);
    void setResonance(wxCommandEvent& event);
};

#endif // SLIDERFIELDHANDLER_HPP