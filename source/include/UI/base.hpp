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
private:
  const double margin = 10;
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    //declare widget
    wxMenuBar* mainMenu;
    wxPanel* panel;
    wxBoxSizer* windowSizer;
    wxFlexGridSizer* buttonGridSizer;
    wxMenu* profileMenu;
    wxMenu* recordMenu;
    wxMenu* aboutMenu;

    //declare events
    void pressPlayButton(wxCommandEvent& event);

    void saveProfile(wxCommandEvent& event);
    void loadProfile(wxCommandEvent& event);
    void showAbout(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()  
};

//button IDs
enum
{
  BUTTON_PLAY,
  MENU_SAVE,
  MENU_LOAD,
  MENU_ABOUT,
  MENU_QUIT,
};
