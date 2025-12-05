#ifndef APPBASE_HPP
#define APPBASE_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MessageHandler.hpp"
#include "MenuBarHandler.hpp"
#include "KeyFieldHandler.hpp"
#include "SliderFieldHandler.hpp"

///This class is responsible for showing and handling the GUI.
///
///This class is derived from the wxFrame class.
class MainFrame: public wxFrame
{
    //Messages
    Messages* messages;
    
    //Menubar
    MenuBarHandler* menubar;
    
    //Declare widgets------------------------
    //Buttons and sliders are on a different panel
    wxBoxSizer* windowSizer;
    KeyFieldHandler* keyfield;
    SliderFieldHandler* sliderfield;

public:
    const double margin = 10;

    //Constructor
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};
#endif