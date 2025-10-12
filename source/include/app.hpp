#pragma once

#include <wx/app.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include<wx/wx.h>
#endif

///A MainApp osztály
///
///Ez kezel minden eseményt, ami az alkalmazásban történik.
class MainApp: public wxApp
{
  public:
    virtual bool OnInit();
};

DECLARE_APP(MainApp)
