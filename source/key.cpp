#include <key.hpp>

const int WIDTH = 150;
const int HEIGHT = 150;

Key::Key(wxWindow* parent, wxWindowID event)
  :wxButton(parent, event, wxT("No sound"), wxDefaultPosition, wxSize(WIDTH, HEIGHT), 0)
{
  pathToSound = "no_path";
}

void Key::setPathToSound(std::string newPathToSound)
{
  pathToSound = newPathToSound;
}

std::string Key::getPathToSound()
{
  return pathToSound;
}
