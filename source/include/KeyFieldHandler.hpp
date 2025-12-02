#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class KeyFieldHandler
{
    wxFrame* parent;
    wxPanel* keyPanel;
    wxFlexGridSizer* keyGridSizer;

public:
    KeyFieldHandler(wxFrame* parent);

    void createKeyField();

    wxPanel* getKeyPanel();
};