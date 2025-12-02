#include "AppBase.hpp"
#include "KeyFieldHandler.hpp"
#include "Key.hpp"


KeyFieldHandler::KeyFieldHandler(wxFrame* parent)
{
    this->parent = parent;    
    keyPanel = new wxPanel(parent, wxID_ANY);
    keyGridSizer = new wxFlexGridSizer(4, 4, 10, 10); //TODO: use universal value from base
  
    //Add the key panel to a sizer
    keyGridSizer->SetMinSize(wxDefaultSize.GetWidth(), wxDefaultSize.GetHeight());
    keyPanel->SetSizer(keyGridSizer);
}

//Create key grid
void KeyFieldHandler::createKeyField()
{
  for(int i = 0; i < 4; ++i)
  {
    keyGridSizer->AddGrowableRow(i);
    keyGridSizer->AddGrowableCol(i);

    for(int j = 0; j < 4; ++j)
    {
      auto key = new Key(keyPanel, BUTTON_PLAY);
      keyGridSizer->Add(key);
    }
  }
}

wxPanel* KeyFieldHandler::getKeyPanel()
{
    return keyPanel;
}