#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include <miniaudio.h>
#include <MessageHandler.hpp>
#include <MenuBarHandler.hpp>

///This class is responsible for showing and handling the GUI.
///
///This class is derived from the wxFrame class.
class MainFrame: public wxFrame 
{
private:
  const double margin = 10;
public:
    //ctor
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    //dtor
    ~MainFrame();

    //Sound stuff
    ma_engine engine;

    //Messages
    Messages* messages; 

    //Menubar
    wxMenuBar menubar;
  
    //Declare widgets------------------------
    //Buttons and sliders are on a different panel
    wxPanel* buttonPanel;
    wxPanel* sliderPanel;
    wxBoxSizer* windowSizer;
    wxFlexGridSizer* buttonGridSizer;

    //Functions for clearer ctor declaration
    void createButtonGrid();

    //Declare events
    void pressPlayButton(wxCommandEvent& event);

    DECLARE_EVENT_TABLE();
};

//button IDs
enum
{
  BUTTON_PLAY
};