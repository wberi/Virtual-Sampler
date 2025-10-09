#include <base.hpp>
#include <messages.hpp>

//event table init
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(MENU_SAVE, MainFrame::saveProfile)
  EVT_MENU(MENU_LOAD, MainFrame::loadProfile)
  EVT_MENU(MENU_ABOUT, MainFrame::showAbout)
  EVT_MENU(MENU_QUIT, MainFrame::onExit)
END_EVENT_TABLE()
  
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
:wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
  //init buttons and other widgets here
  mainMenu = new wxMenuBar();
  auto profileMenu = new wxMenu(); //TODO: define these in the header file
  auto recordMenu = new wxMenu();
  auto aboutMenu = new wxMenu();

  //add menu options to the "Profile" menu
  profileMenu->Append(MENU_SAVE, wxT("Save profile\tCtrl-S"));
  profileMenu->Append(MENU_LOAD, wxT("Load profile\tCtrl-O"));
  profileMenu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

  aboutMenu->Append(MENU_ABOUT, wxT("Information"));

  //add "Profile" to the bar and activate the bar
  mainMenu->Append(profileMenu, wxT("Profile"));
  mainMenu->Append(recordMenu, wxT("Recording"));
  mainMenu->Append(aboutMenu, wxT("About"));
  SetMenuBar(mainMenu);
}

//Events
void MainFrame::saveProfile(wxCommandEvent& event)
{
 //TODO: implement
}

void MainFrame::loadProfile(wxCommandEvent& event)
{
  //TODO: implement
}

void MainFrame::showAbout(wxCommandEvent& event)
{
  ShowAboutMessage();
}

void MainFrame::onExit(wxCommandEvent& event)
{
  if(ShowQuitMessage() == wxID_YES)
  {
    Close(true);
  }
}
