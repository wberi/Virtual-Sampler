#include "AppBase.hpp"
#include "KeyFieldHandler.hpp"
#include "Key.hpp"
#include "SliderFieldHandler.hpp"
#include <KeyNameDialog.hpp>
#include <wx/log.h>

//Refactoring of this file from base.cpp was done with AI assistance!
//Constructor for basic GUI setup
KeyFieldHandler::KeyFieldHandler(wxFrame* parent, Messages* messages, SliderFieldHandler* sliderPanel)
{
  //Set the parent frame and preloaded Message instance references
  this->parent = parent;
  this->messages = messages;

  //Store the slider panel
  this->sliderPanel = sliderPanel;

  //Create the UI panel and sizer
  keyPanel = new wxPanel(parent, wxID_ANY);
  keyGridSizer = new wxFlexGridSizer(4, 4, 10, 10);

  //Setup and activate sizer
  keyGridSizer->SetMinSize(wxDefaultSize.GetWidth(), wxDefaultSize.GetHeight());
  keyPanel->SetSizer(keyGridSizer);

  //Initialize sound engine
  ma_result result = ma_engine_init(nullptr, &engine);
  if(result != MA_SUCCESS)
  {
    //error if it fails
    messages->ShowEngineFailureMessage();
    exit(1);
  }

  //Bind key listener event to the parent frame
  parent->Bind(wxEVT_CHAR_HOOK, &KeyFieldHandler::listenToKbEvents, this);
}

//Uninitialize things
KeyFieldHandler::~KeyFieldHandler()
{   
    //TODO: sound group uninit
    ma_engine_uninit(&engine);
}

//Create a 4x4 panel if Keys
void KeyFieldHandler::createKeyField()
{
  for(int i = 0; i < 4; ++i)
  {
    keyGridSizer->AddGrowableRow(i);
    keyGridSizer->AddGrowableCol(i);

    for(int j = 0; j < 4; ++j)
    {
      auto key = new Key(keyPanel);
      
      //Bind setup method
      key->Bind(wxEVT_BUTTON, &KeyFieldHandler::setupKey, this);
      
      //Create sound group
      ma_sound_group* newGroup = new ma_sound_group();
      ma_result result =  ma_sound_group_init(&engine, MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, newGroup);
      if(result != MA_SUCCESS)
      {
        messages->ShowEngineFailureMessage();
        exit(1);
      }
      
      //Store the pointer of the sound group
      key->setSoundGroupPtr(newGroup);
      
      //Set scaling of volume 
      ma_sound_group_set_volume(newGroup, key->getVolume() / 10.0);
      
      keyGridSizer->Add(key);
    }
  }
}

//Return the panel for it to be displayed on the MainFrame
wxPanel* KeyFieldHandler::getKeyPanel()
{
    return keyPanel;
}

//Method for setting up the button when it is pressed
void KeyFieldHandler::setupKey(wxCommandEvent& event)
{
  auto button = dynamic_cast<Key*>(event.GetEventObject());
  if(button)
  {
    //Notify user of setup
    messages->ShowMissingFileMessage();
    
    //Create and show file browser window
    wxFileDialog fileBrowser(parent, wxT("Open sound file"), "", "",
     "Sound files (*.wav, *.mp3)|*.wav", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(fileBrowser.ShowModal() == wxID_CANCEL)
    {
      //return if users cancels
      return;
    }
    
    //Get the path to the file
    std::string filePath = fileBrowser.GetPath().ToStdString();
    
    //Initialize the sound, error if unsuccessful
    ma_result res;
    //Use the Key's specific sound group pointer
    res = ma_sound_init_from_file(&engine, filePath.c_str(), 
    MA_SOUND_FLAG_NO_SPATIALIZATION, button->getSoundGroupPtr(), NULL, button->getSound());
    if(res != MA_SUCCESS)
    {
      messages->ShowEngineFailureMessage();
      return;
    }
    
    //Set Key filepath property
    button->sound_path = filePath;
    
    //Create and show setup dialog
    KeyNameDialog setupDialog ( parent, -1, _("Select button shortcut"),
                            wxPoint(0, 0), wxSize(200, 100) );
    if(setupDialog.ShowModal() != wxID_OK) 
    {
      //Get the choosen character from the combo box
      wxString text = setupDialog.GetShortcut();

      //Set the name of the key accordingly
      button->SetLabel(setupDialog.GetName() + " (" + text + ")"); //the name contains the shortcut

      //Add the shortcut combination to the keyMap structure for easy lookup
      //Assuming a single character is selected
      char shortcutChar = (char)text[0];
      keyMap.insert({shortcutChar, button});

      //Unbind setupKey and bind the new updateSliderPanel function
      button->Unbind(wxEVT_BUTTON, &KeyFieldHandler::setupKey, this);
      button->Bind(wxEVT_BUTTON, &KeyFieldHandler::updateSliderPanel, this);
      
      //Manually trigger the update function to set the sliders for the newly configured key
      wxCommandEvent updateEvent(wxEVT_BUTTON, button->GetId());
      updateSliderPanel(updateEvent);
    }
  }
}

//New method to update the slider panel when a configured Key is clicked
void KeyFieldHandler::updateSliderPanel(wxCommandEvent& event)
{
    auto button = dynamic_cast<Key*>(event.GetEventObject());
    if(button && sliderPanel)
    {
        sliderPanel->SetCurrentKey(button);
        sliderPanel->UpdateControlsFromKey();
    }
}


//Play the corresponding sound after the Key is pressed
void KeyFieldHandler::playSound(Key* key)
{
  if(ma_sound_is_playing(key->getSound()))
  {
    //If the sound is still playing, we need to restart it 
    ma_sound_seek_to_pcm_frame(key->getSound(), 0);
  }
  else
  {
    //We just play the sound
    ma_sound_start(key->getSound());
  }
}

void KeyFieldHandler::listenToKbEvents(wxKeyEvent& event)
{
  //Get the code of the pressed key
  char keyCode = (char)event.GetKeyCode();

  //Get the element from the map based on the pressed buttons code
  auto key = keyMap.find(keyCode);

  if(key != keyMap.end())
  {
    //If its found, get the key from the element
    Key* targetKey = key->second;

    //Play the sound
    playSound(targetKey);
    

    //Update slider visuals
    wxCommandEvent updateEvent(wxEVT_BUTTON, targetKey->GetId());
    updateSliderPanel(updateEvent);

    //Consume the event
    event.Skip(false);
  }
  else
  {
    event.Skip();
  }
}