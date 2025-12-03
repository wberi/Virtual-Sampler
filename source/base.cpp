#include "KeyFieldHandler.hpp"
#include "MenuBarHandler.hpp"
#include <MessageHandler.hpp>
#include <KeyNameDialog.hpp>
#include <AppBase.hpp>
#include <Key.hpp>
#include <miniaudio.h>

//Constructor
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame*) nullptr, -1, title, pos, size)
{
  //Initialize messages
  messages = new Messages();

  //Initialize widgets for menu bar
  menubar = new MenuBarHandler(this, messages);
  SetMenuBar(menubar);

  //Initialize widgets
  windowSizer = new wxBoxSizer(wxHORIZONTAL);
  
  //Initialize SliderFieldHandler
  sliderfield = new SliderFieldHandler(this);

  //Initialize KeyFieldHandler
  keyfield = new KeyFieldHandler(this, messages, sliderfield);
  keyfield->createKeyField();

  //Add both fields to the main window
  windowSizer->Add(keyfield->getKeyPanel(), 1, wxEXPAND | wxALL, margin);
  windowSizer->Add(sliderfield, 1, wxEXPAND | wxALL, margin);
  this->SetSizerAndFit(windowSizer);
}