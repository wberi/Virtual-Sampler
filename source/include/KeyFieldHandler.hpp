#ifndef KEYFIELDHANDLER_HPP
#define KEYFIELDHANDLER_HPP

#include <wx/event.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include <miniaudio.h>
#include <map>
#include "MessageHandler.hpp" 
#include "Key.hpp"
#include "SliderFieldHandler.hpp" 

class KeyFieldHandler
{
  //GUI
  wxFrame* parent;
  wxPanel* keyPanel;
  wxFlexGridSizer* keyGridSizer;
  Messages* messages;
  SliderFieldHandler* sliderPanel; // Reference to the main slider panel

  //Sound stuff
  ma_engine engine;
  // ma_sound_group soundGroup; // REMOVED

  //Map for keeping track of button shortcuts
  std::map<char, Key*> keyMap;

public:
    //Constructor and destructor (Updated: Added SliderFieldHandler* argument)
    KeyFieldHandler(wxFrame* parent, Messages* messages, SliderFieldHandler* sliderPanel);
    ~KeyFieldHandler();

    //Create keyfield
    void createKeyField();

    //Setup the button's sound file and shortcut
    void setupKey(wxCommandEvent& event);
    
    //Update the slider panel to match the clicked button's attributes
    void updateSliderPanel(wxCommandEvent& event);

    //Play sound
    void playSound(Key* key);

    //Listen to keyboard events
    void listenToKbEvents(wxKeyEvent& event);
    
    //Getters
    wxPanel* getKeyPanel();
    //ma_sound_group* getSoundGroup(); // REMOVED
};

#endif // KEYFIELDHANDLER_HPP