#pragma once

#include "MessageHandler.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class MenuBarHandler: public wxMenuBar
{
    //Submenus
    wxMenu* profileMenu;
    wxMenu* recordMenu;
    wxMenu* aboutMenu;

    //Parent frame
    wxFrame* parent;

    //MessageHandler instance
    Messages* messages;

public:
    //ctor
    MenuBarHandler(wxFrame* parent, Messages* messages);

    //Event handling
    void saveProfile(wxCommandEvent& event);
    void loadProfile(wxCommandEvent& event);
    void showAbout(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

//Event IDs
enum
{
  MENU_SAVE,
  MENU_LOAD,
  MENU_ABOUT,
  MENU_QUIT,
};