#include <base.hpp>
#include <messages.hpp>

const int WIDTH = 300;
const int HEIGHT = 300;

IMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
  MainFrame* main = new MainFrame(wxT("Virtual Sampler"), wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  main->Show(true);
  SetTopWindow(main);

  //Message window setup
  MessageFrame *msgs = new MessageFrame(wxT("Messages"));
  msgs->Show(true);

  return true;
}

//event table init
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(MENU_SAVE, MainFrame::saveProfile)
  EVT_MENU(MENU_LOAD, MainFrame::loadProfile)
  EVT_MENU(MENU_QUIT, MainFrame::onExit)
END_EVENT_TABLE()
  

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
:wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
  //init buttons and other widgets here
  mainMenu = new wxMenuBar();
  wxMenu* profileMenu = new wxMenu();
  wxMenu* recordMenu = new wxMenu();
  wxMenu* aboutMenu = new wxMenu();

  //add menu options to the "Profile" menu
  profileMenu->Append(MENU_SAVE, wxT("Save profile\tCtrl-S"));
  profileMenu->Append(MENU_LOAD, wxT("Load profile\tCtrl-O"));
  profileMenu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

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

void MainFrame::onExit(wxCommandEvent& event)
{
  Close(true);
}
