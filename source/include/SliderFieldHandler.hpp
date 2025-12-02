#pragma once

#include <wx/sizer.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SliderFieldHandler
{
    //Fields parent object
    wxFrame* parent;

    //Content panel
    wxPanel* sliderPanel;
    wxFlexGridSizer* fieldGridSizer;

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

    //Helper functions
    void addSliderRow(wxString label_text, 
        wxSlider* slider_ptr, int id, int min_val, int max_val, int initial_val);
public:
    SliderFieldHandler(wxFrame* parent);

    wxPanel* getSliderPanel();
};