#include "KeyFieldHandler.hpp"
#include "MenuBarHandler.hpp"
#include <MessageHandler.hpp>
#include <KeyNameDialog.hpp>
#include <AppBase.hpp>
#include <Key.hpp>
#include <miniaudio.h>

//declaring the constructor for MainFrame
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame*) nullptr, -1, title, pos, size)
{
  //Init messages
  messages = new Messages();

  //Init widgets for menu bar
  menubar = new MenuBarHandler(this, messages);
  SetMenuBar(menubar);

  //Init widgets
  windowSizer = new wxBoxSizer(wxHORIZONTAL);

  // --- REFACTOR START ---
  
  // 1. Initialize SliderFieldHandler first (no longer needs a sound group pointer)
  sliderfield = new SliderFieldHandler(this);

  // 2. Initialize KeyFieldHandler and pass the slider panel pointer
  keyfield = new KeyFieldHandler(this, messages, sliderfield);
  keyfield->createKeyField();

  // --- REFACTOR END ---

  windowSizer->Add(keyfield->getKeyPanel(), 1, wxEXPAND | wxALL, margin);
  windowSizer->Add(sliderfield, 1, wxEXPAND | wxALL, margin);
  this->SetSizerAndFit(windowSizer);
}