#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

///A MainFrame osztály
///
///Az vizuális elemek megjelenítéséért felelős osztály.
class MainFrame: public wxFrame 
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    //declare widget
    wxMenuBar* mainMenu;  

    //declare events
    void saveProfile(wxCommandEvent& event);
    void loadProfile(wxCommandEvent& event);
    void showAbout(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()  
};

//button IDs
enum
{
  MENU_SAVE,
  MENU_LOAD,
  MENU_ABOUT,
  MENU_QUIT,
};
