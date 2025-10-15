#include "messages.hpp"
#include <base.hpp>
#include <fstream>
#include <key.hpp>
#include <miniaudio.h>

void MainFrame::initMenuBar()
{
  //add menu options to the "Profile" menu
  profileMenu->Append(MENU_SAVE, wxT("Save profile\tCtrl-S"));
  profileMenu->Append(MENU_LOAD, wxT("Load profile\tCtrl-O"));
  profileMenu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

  //add menu options to "About" menu
  aboutMenu->Append(MENU_ABOUT, wxT("Information"));

  //add options to the bar and activate the bar
  mainMenu->Append(profileMenu, wxT("Profile"));
  mainMenu->Append(recordMenu, wxT("Recording"));
  mainMenu->Append(aboutMenu, wxT("About"));
  SetMenuBar(mainMenu);
}

void MainFrame::createButtonGrid()
{
  //Create button grid
  for(int i = 0; i < 4; ++i)
  {
    buttonGridSizer->AddGrowableRow(i);
    buttonGridSizer->AddGrowableCol(i);

    for(int j = 0; j < 4; ++j)
    {
      auto button = new Key(buttonPanel, BUTTON_PLAY);
      buttonGridSizer->Add(button);
    }
  }
}


//Event table to store all events
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_BUTTON(BUTTON_PLAY, MainFrame::pressPlayButton)
  EVT_MENU(MENU_SAVE, MainFrame::saveProfile)
  EVT_MENU(MENU_LOAD, MainFrame::loadProfile)
  EVT_MENU(MENU_ABOUT, MainFrame::showAbout)
  EVT_MENU(MENU_QUIT, MainFrame::onExit)
END_EVENT_TABLE()

//declaring the constructor for MainFrame
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
:wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
  //Init messages 
  messages = new Messages(); 

  //Sound stuff 
  ma_result result;

  result = ma_engine_init(NULL, &engine);
  if(result != MA_SUCCESS)
  {
    return;
  }

  //Init widgets for menu bar
  mainMenu = new wxMenuBar();
  profileMenu = new wxMenu(); 
  recordMenu = new wxMenu();
  aboutMenu = new wxMenu();

  initMenuBar();

  //Init widgets for button grid
  windowSizer = new wxBoxSizer(wxHORIZONTAL);
  buttonPanel = new wxPanel(this, wxID_ANY);
  sliderPanel = new wxPanel(this, wxID_ANY);
  buttonGridSizer = new wxFlexGridSizer(4, 4, margin, margin);

  createButtonGrid();

  //Add the button panel to a sizer
  buttonGridSizer->SetMinSize(wxDefaultSize.GetWidth(), wxDefaultSize.GetHeight());
  buttonPanel->SetSizer(buttonGridSizer);

  //add all the panels to the main sizer and set it as default sizer
  windowSizer->Add(buttonPanel, 1, wxEXPAND | wxALL, margin);
  windowSizer->Add(sliderPanel, 1, wxEXPAND | wxALL, margin);
  this->SetSizerAndFit(windowSizer);
}

MainFrame::~MainFrame()
{
  //DESTROY THINGS HERE
  ma_engine_uninit(&engine);
}

//Events--------------------------------------------------------
//This runs when a play button is pressed
void MainFrame::pressPlayButton(wxCommandEvent& event)
{
  //checks if the button has a sound to play 
  //if not (or the path is invalid) it brings up a window to select a sound 
  //if there is a valid path it will play the sound
  
  Key* button = dynamic_cast<Key*>(event.GetEventObject());

  if(!true) //TODO: fix!!!
  {
    messages->ShowMissingFileMessage();

    wxFileDialog fileBrowser(this, wxT("Open sound file"), "", "", "*.wav|*.wav", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(fileBrowser.ShowModal() == wxID_CANCEL)
    {
      return; 
    }

    std::string filePath = fileBrowser.GetPath();

    std::ifstream testStream(filePath);
    if(!testStream)
    {
      messages->ShowInvalidPathMessage(); 
      return;
    }

    ma_result res;
    //res = ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, ???); TODO: fix!
    if(res != MA_SUCCESS)
    {
      messages->ShowEngineFailureMessage();
      return;
    }
    button->SetLabel(fileBrowser.GetFilename().c_str());
  }
  else 
  {
    //ma_sound_start(button->getSound()); TODO: fix!
  }
}

void MainFrame::saveProfile(wxCommandEvent& event)
{

}

void MainFrame::loadProfile(wxCommandEvent& event)
{

}

//Brings up a window with the about information
void MainFrame::showAbout(wxCommandEvent& event)
{
  messages->ShowAboutMessage();
}

//Shows exit message on exit
void MainFrame::onExit(wxCommandEvent& event)
{
  if(messages->ShowQuitMessage() == wxID_YES)
  {
    Close(true);
  }
}
