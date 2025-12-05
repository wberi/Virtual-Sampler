#ifndef MENUBARHANDLER_HPP
#define MENUBARHANDLER_HPP

#include "MessageHandler.hpp"
#include "KeyFieldHandler.hpp"
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

    //KeyFieldHandler instance
    KeyFieldHandler* kField;

public:
    //ctor
    MenuBarHandler(wxFrame* parent, Messages* messages, KeyFieldHandler* kField);

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
#endif