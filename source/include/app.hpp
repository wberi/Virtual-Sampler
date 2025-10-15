#pragma once

#include <wx/app.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include<wx/wx.h>
#endif

///This class is responsible for handling events inside the app.
///
///It class is derived from the wxApp class.
class MainApp: public wxApp
{
  public:
    virtual bool OnInit();
};

DECLARE_APP(MainApp)
