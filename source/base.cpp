#include "KeyFieldHandler.hpp"
#include "MenuBarHandler.hpp"
#include "SliderFieldHandler.hpp"
#include <MessageHandler.hpp>
#include <KeyNameDialog.hpp>
#include <AppBase.hpp>
#include <cstdio>
#include <fstream>
#include <Key.hpp>
#include <miniaudio.h>

//Event table to store all events
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_BUTTON(BUTTON_PLAY, MainFrame::pressPlayButton)
END_EVENT_TABLE()

//declaring the constructor for MainFrame
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
:wxFrame((wxFrame*) nullptr, -1, title, pos, size)
{
  //Init messages 
  messages = new Messages(); 

  //Sound stuff 
  ma_result result;

  result = ma_engine_init(nullptr, &engine);
  if(result != MA_SUCCESS)
  {
    return;
  }

  //Init widgets for menu bar
  menubar = new MenuBarHandler(this, messages);
  SetMenuBar(menubar);

  //Init widgets
  windowSizer = new wxBoxSizer(wxHORIZONTAL);

  //Setup keyfield
  keyfield = new KeyFieldHandler(this);
  keyfield->createKeyField();

  //Setup sliderfield
  sliderfield = new SliderFieldHandler(this);

  //add all the panels to the main sizer and set it as default sizer
  windowSizer->Add(keyfield->getKeyPanel(), 1, wxEXPAND | wxALL, margin);
  windowSizer->Add(sliderfield->getSliderPanel(), 1, wxEXPAND | wxALL, margin);
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
  
  auto button = dynamic_cast<Key*>(event.GetEventObject());

  if(button->sound_path.empty())
  {
    messages->ShowMissingFileMessage();

    wxFileDialog fileBrowser(this, wxT("Open sound file"), "", "", "Sound files (*.wav, *.mp3)|*.wav", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(fileBrowser.ShowModal() == wxID_CANCEL)
    {
      return; 
    }

    std::string filePath = fileBrowser.GetPath();

    std::ifstream testFilePath(filePath);
    if(!testFilePath)
    {
      messages->ShowInvalidPathMessage(); 
      return;
    }
    testFilePath.close();

    ma_result res;
    res = ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, button->getSound());
    if(res != MA_SUCCESS)
    {
      messages->ShowEngineFailureMessage();
      return;
    }

    button->sound_path = filePath;
    
    KeyNameDialog nameDialog ( this, -1, _("Choose button name"),
	                          wxPoint(100, 100), wxSize(200, 200) );
	  if (nameDialog.ShowModal() != wxID_OK)
      button->SetLabel(nameDialog.GetText());
  }
  else 
  {
    if(ma_sound_is_playing(button->getSound()))
    {
     ma_sound_seek_to_pcm_frame(button->getSound(), 0);
    }
    else 
    {
     ma_sound_start(button->getSound());
    }
  }
}