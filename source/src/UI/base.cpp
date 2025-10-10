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
  //Init widgets for menu bar
  mainMenu = new wxMenuBar();
  profileMenu = new wxMenu(); 
  recordMenu = new wxMenu();
  aboutMenu = new wxMenu();

  //add menu options to the "Profile" menu
  profileMenu->Append(MENU_SAVE, wxT("Save profile\tCtrl-S"));
  profileMenu->Append(MENU_LOAD, wxT("Load profile\tCtrl-O"));
  profileMenu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

  //add menu options to "About" menu
  aboutMenu->Append(MENU_ABOUT, wxT("Information"));

  //add "Profile" to the bar and activate the bar
  mainMenu->Append(profileMenu, wxT("Profile"));
  mainMenu->Append(recordMenu, wxT("Recording"));
  mainMenu->Append(aboutMenu, wxT("About"));
  SetMenuBar(mainMenu);

  //Init widgets for button grid
  windowSizer = new wxBoxSizer(wxVERTICAL);
  panel = new wxPanel(this, wxID_ANY);
  buttonGridSizer = new wxFlexGridSizer(4, 4, margin, margin);

  //Create button grid
  for(int i = 0; i < 4; ++i)
  {
    buttonGridSizer->AddGrowableRow(i);
    buttonGridSizer->AddGrowableCol(i);

    for(int j = 0; j < 4; ++j)
    {
      auto button = new wxButton(panel, BUTTON_PLAY, wxT("No sound"), wxDefaultPosition, wxDefaultSize, 0);
      buttonGridSizer->Add(button);
    }
  }

  buttonGridSizer->SetMinSize(wxDefaultSize.GetWidth(), wxDefaultSize.GetHeight());
  panel->SetSizer(buttonGridSizer);

  windowSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
  this->SetSizerAndFit(windowSizer);
}

//Events

void MainFrame::pressPlayButton(wxCommandEvent& event)
{

}

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
