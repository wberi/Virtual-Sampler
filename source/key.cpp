#include <Key.hpp>

//Default button dimension values
const int WIDTH = 150;
const int HEIGHT = 150;

//Default values from SliderFieldHandler
const int DEFAULT_VOLUME = 8; //Real sound volume scale: 0.0 - 10.0
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
  :wxButton(parent, -1, wxT("No sound"), wxDefaultPosition, wxSize(WIDTH, HEIGHT), 0),
  
  //Initialize sound attributes
  volume(DEFAULT_VOLUME),
  attack(DEFAULT_ATTACK),
  decay(DEFAULT_DECAY),
  sustain(DEFAULT_SUSTAIN),
  release(DEFAULT_RELEASE),
  pitchShift(DEFAULT_PITCH),
  cutoff(DEFAULT_CUTOFF),
  resonance(DEFAULT_RESONANCE)
{
  sound_path = "";
}

Key::~Key()
{
  //ma_sound_uninit(&sound); 
  //TODO fix this???
}

//Set the Keys sound group
void Key::setSoundGroupPtr(ma_sound_group* groupPtr)
{
  this->soundGroupPtr = groupPtr;
}

//Get the sound pointer of the Key
ma_sound* Key::getSound()
{
  return &sound;
}

//Return the sound group that the Key belongs to
ma_sound_group* Key::getSoundGroupPtr()
{
  return soundGroupPtr;
}