#include "KeyFieldHandler.hpp"
#include "MenuBarHandler.hpp"
#include "FileManager.hpp"

//ctor
MenuBarHandler::MenuBarHandler(wxFrame* parent, Messages* messages, KeyFieldHandler* kField): wxMenuBar()
{
    //Set parent frame
    this->parent = parent;

    //Set message instance
    this->messages = messages;
    
    //Set keyfield instance
    this->kField = kField;

    //init submenus
    profileMenu = new wxMenu(); 
    recordMenu = new wxMenu();
    aboutMenu = new wxMenu();

    //add menu options to the "Profile" menu
    profileMenu->Append(MENU_SAVE, wxT("Save profile\tCtrl-S"));
    profileMenu->Append(MENU_LOAD, wxT("Load profile\tCtrl-O"));
    profileMenu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

    //add menu options to "About" menu
    aboutMenu->Append(MENU_ABOUT, wxT("Information"));

    //add options to the bar and activate the bar
    this->Append(profileMenu, wxT("Profile"));
    this->Append(aboutMenu, wxT("About"));
}

//Event table
BEGIN_EVENT_TABLE(MenuBarHandler, wxMenuBar)
  EVT_MENU(MENU_SAVE, MenuBarHandler::saveProfile)
  EVT_MENU(MENU_LOAD, MenuBarHandler::loadProfile)
  EVT_MENU(MENU_ABOUT, MenuBarHandler::showAbout)
  EVT_MENU(MENU_QUIT, MenuBarHandler::onExit)
END_EVENT_TABLE()

//Save Profile to file
void MenuBarHandler::saveProfile(wxCommandEvent& event)
{
  FileManager::SaveProfile(parent, kField->getKeys());
}

//Load Profile from file
void MenuBarHandler::loadProfile(wxCommandEvent& event)
{
  FileManager::LoadProfile(parent, kField);
}

//Brings up a window with the about information
void MenuBarHandler::showAbout(wxCommandEvent& event)
{
    messages->ShowAboutMessage();
}

//Shows exit message on exit
void MenuBarHandler::onExit(wxCommandEvent& event)
{
  if(messages->ShowQuitMessage() == wxID_YES)
  {
    parent->Close(true);
  }
}