#include "AppBase.hpp"
#include <Key.hpp>

const int WIDTH = 150;
const int HEIGHT = 150;

Key::Key(wxWindow* parent, wxWindowID event)
  :wxButton(parent, event, wxT("No sound"), wxDefaultPosition, wxSize(WIDTH, HEIGHT), 0)
{
  sound_path = "";
}

Key::~Key()
{
  //ma_sound_uninit(&sound); 
  //TODO fix this???
}

ma_sound* Key::getSound()
{
  return &sound;
}
