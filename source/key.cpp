#include "miniaudio.h"
#include <Key.hpp>
#include <wx/timer.h>

//Default button dimension values
const int WIDTH = 150;
const int HEIGHT = 150;

//Default values from SliderFieldHandler
const int DEFAULT_VOLUME = 80; //Real sound volume scale: 0.0 - 1.0
const int DEFAULT_ATTACK = 10;
const int DEFAULT_DECAY = 50;
const int DEFAULT_SUSTAIN = 75;
const int DEFAULT_RELEASE = 500;
const int DEFAULT_PITCH = 0; //Real pitch scale: 0.0 - 1.0 
                             //Based on this formula: F = 2^(N/12)
const int DEFAULT_CUTOFF = 5000;
const int DEFAULT_RESONANCE = 1;

//Constructor
Key::Key(wxWindow* parent)
  :wxButton(parent, -1, wxT("No sound"), wxDefaultPosition, wxSize(WIDTH, HEIGHT), 0)
{
    //Initialize sound attributes
    setVolume(DEFAULT_VOLUME);
    setAttack(DEFAULT_ATTACK);
    setDecay(DEFAULT_DECAY);
    setSustain(DEFAULT_SUSTAIN);
    setRelease(DEFAULT_RELEASE);
    setPitchShift(DEFAULT_PITCH);
    setCutoff(DEFAULT_CUTOFF);
    setResonance(DEFAULT_RESONANCE);
    sound_path = "";

    this->SetForegroundColour(DEFAULT_COLOR); //set default color
    animationTimer = new wxTimer(); //create timer
    animationTimer->Bind(wxEVT_TIMER, &Key::endAnimatekey, this);
}

Key::~Key()
{
  //Free sound and sound group
  uninitSound();
  ma_sound_group_uninit(soundGroupPtr);
}

void Key::uninitSound()
{
  ma_sound_uninit(sound);
}

ma_result Key::setupSound(ma_engine* engine, std::string filePath)
{
  this->sound_path = filePath; //store filepath
  sound = new ma_sound(); //initialize sound
  
  return ma_sound_init_from_file(engine, filePath.c_str(), 
    MA_SOUND_FLAG_NO_SPATIALIZATION, soundGroupPtr, NULL, sound);
}

ma_result Key::setupGroup(ma_engine* engine)
{    
  soundGroupPtr = new ma_sound_group();
  return ma_sound_group_init(engine, MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, soundGroupPtr);
}

void Key::playSound()
{
  if(ma_sound_is_playing(sound))
  {
    //If the sound is still playing, we need to restart it 
    ma_sound_seek_to_pcm_frame(sound, 0);
  }
  else
  {
    //We just play the sound
    ma_sound_start(sound);
  }
}

void Key::beginAnimateKey()
{
  this->SetForegroundColour(ACTIVE_COLOR);
  animationTimer->Start(100, wxTIMER_ONE_SHOT);
}

void Key::endAnimatekey(wxTimerEvent& event)
{
  this->SetForegroundColour(DEFAULT_COLOR);
  animationTimer->Stop();
  this->Refresh();
}

//Return the sound group that the Key belongs to
ma_sound_group* Key::getSoundGroupPtr()
{
  return soundGroupPtr;
}

void Key::setShortCut(char shortcut)
{
  this->shortcut = shortcut;
}

char Key::getShortCut()
{
  return shortcut;
}