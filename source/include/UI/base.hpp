#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

///A MainApp osztály
///
///Ez kezel minden eseményt, ami az alkalmazásban történik.
class MainApp: public wxApp
{
  public:
    virtual bool OnInit();
};

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
    void onExit(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()  
};

//button IDs
enum
{
  MENU_SAVE,
  MENU_LOAD,
  MENU_QUIT,
};

DECLARE_APP(MainApp);
