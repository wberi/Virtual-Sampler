#ifndef KEYFIELDHANDLER_HPP
#define KEYFIELDHANDLER_HPP

#include <wx/event.h>
#include <wx/gdicmn.h>
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
  SliderFieldHandler* sliderPanel;

  //Sound engine
  ma_engine engine;
  ma_engine_config engineConfig;

  //Map for keeping track of button shortcuts
  std::map<char, Key*> keyMap;
  std::vector<Key*> keyList;

public:
    //Constructor
    KeyFieldHandler(wxFrame* parent, Messages* messages, SliderFieldHandler* sliderPanel);

    //Destructor
    ~KeyFieldHandler();

    ma_result createEngine();

    //Create keyfield
    void createKeyField();

    //Setup the Key's sound file and shortcut
    void setupKeyEvent(wxCommandEvent& event);
    void setupKey(Key* button);
    void setKeyBind(Key* button); //binds Key with sound playing
    void resetKey(wxCommandEvent& event);

    //Refresh the slider panel
    void refreshControls(Key* button);
    
    //Update the slider panel to match the clicked button's attributes
    void updateSliderPanel(wxCommandEvent& event);

    //Play sound
    void playSound(Key* key);

    //Listen to keyboard events
    void listenToKbEvents(wxKeyEvent& event);

    //Getters
    wxPanel* getKeyPanel();
    std::vector<Key*>& getKeys();
    ma_engine* getEngine();
    std::map<char, Key*>& getKeyMap();
};

#endif