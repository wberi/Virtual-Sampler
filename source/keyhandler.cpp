#include "AppBase.hpp"
#include "KeyFieldHandler.hpp"
#include "Key.hpp"
#include "SliderFieldHandler.hpp"
#include <KeyNameDialog.hpp>
#include <wx/event.h>
#include <wx/gtk/colour.h>
#include <wx/log.h>
#include <wx/timer.h>
#include <wx/utils.h>

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

  //Bind key reset button from SliderFieldHandler
  sliderPanel->getResetButton()->Bind(wxEVT_BUTTON, &KeyFieldHandler::resetKey, this);
}

//Uninitialize things
KeyFieldHandler::~KeyFieldHandler()
{   
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
      keyList.push_back(key);
      
      //Bind setup method
      key->Bind(wxEVT_BUTTON, &KeyFieldHandler::setupKeyEvent, this);
      
      //Create sound group
      if(key->setupGroup(&engine) != MA_SUCCESS)
      {
        messages->ShowEngineFailureMessage();
        exit(1);
      }
      
      //Set scaling of volume 
      ma_sound_group_set_volume(key->getSoundGroupPtr(), key->getVolume() / 100.0);
      
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
void KeyFieldHandler::setupKeyEvent(wxCommandEvent& event)
{
  auto button = dynamic_cast<Key*>(event.GetEventObject());
  if(button)
  {
    setupKey(button);
  }
}

void KeyFieldHandler::setupKey(Key* button)
{      
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

  if(button->setupSound(&engine, filePath) != MA_SUCCESS)
  {
    messages->ShowEngineFailureMessage();
    return;
  }
  
  //Create and show setup dialog
  KeyNameDialog setupDialog ( parent, -1, _("Select button shortcut"),
                          wxPoint(0, 0), wxSize(200, 100) );
  if(setupDialog.ShowModal() != wxID_CANCEL) 
  {
    //Get the choosen character from the combo box
    wxString text = setupDialog.GetShortcut();
    char shortcutChar = (char)text[0];
    
    if(keyMap.count(shortcutChar))
    {
      //If key had a shortcut, restore it
      messages->ShowBlockedShortcutMessage();
      char keyShortcut = button->getShortCut();
      if(keyShortcut != '-')
      {
        keyMap.insert({keyShortcut, button});
      }
      return;
    }
    
    //Set the name of the key accordingly
    button->SetLabel(setupDialog.GetName() + " (" + text + ")"); //the name contains the shortcut

    //Add the shortcut combination to the keyMap structure for easy lookup
    //Assuming a single character is selected
    keyMap.insert({shortcutChar, button});
    button->setShortCut(shortcutChar); //Store shortczt in Key

    //Unbind setupKey and bind the new updateSliderPanel function
    setKeyBind(button);
    
    //Manually trigger the update function to set the sliders for the newly configured key
    refreshControls(button);
  }
}

void KeyFieldHandler::setKeyBind(Key* button)
{
  button->Unbind(wxEVT_BUTTON, &KeyFieldHandler::setupKeyEvent, this);
  button->Bind(wxEVT_BUTTON, &KeyFieldHandler::updateSliderPanel, this);
}

void KeyFieldHandler::resetKey(wxCommandEvent& event)
{
  Key* currentKey = sliderPanel->getCurrentKeyPtr();
  if(currentKey == nullptr)
  {
    //error msg
    return;
  }

  //Uninit sound 
  currentKey->uninitSound();

  //Delete bind (if it exists)
  char k;
  for(auto& key : keyMap)
  {
    if(key.second == currentKey)
    {
      k = key.first;
    }
  }
  keyMap.erase(k);
  
  //redo setup
  setupKey(sliderPanel->getCurrentKeyPtr());
}

//Helper function, so both events can refresh
void KeyFieldHandler::refreshControls(Key* button)
{
  sliderPanel->SetCurrentKey(button);
  sliderPanel->UpdateControlsFromKey();
}

//Update the slider panel when a configured Key is clicked
void KeyFieldHandler::updateSliderPanel(wxCommandEvent& event)
{
    auto button = dynamic_cast<Key*>(event.GetEventObject());
    if(button && sliderPanel)
    {
      refreshControls(button);
    }
}

//Play the corresponding sound after the Key is pressed
void KeyFieldHandler::playSound(Key* key)
{
  //Start animation
  key->beginAnimateKey(); 

  //Play sound
  key->playSound();
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

    //Consume the event
    event.Skip(false);
  }
  else
  {
    event.Skip();
  }
}

std::vector<Key*>& KeyFieldHandler::getKeys()
{
  return keyList;
}

ma_engine* KeyFieldHandler::getEngine()
{
  return &engine;
}

std::map<char, Key*>& KeyFieldHandler::getKeyMap()
{
  return keyMap;
}