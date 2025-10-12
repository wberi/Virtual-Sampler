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

    //Declare widgets------------------------
  
    //Buttons and sliders are on a different panel
    wxPanel* buttonPanel;
    wxPanel* sliderPanel;
    wxBoxSizer* windowSizer;
    wxFlexGridSizer* buttonGridSizer;

    //Menu bar elements
    wxMenuBar* mainMenu;
    wxMenu* profileMenu;
    wxMenu* recordMenu;
    wxMenu* aboutMenu;

    //Declare events
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
