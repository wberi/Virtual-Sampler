#pragma once

#include <wx/wxprec.h>
#ifndef WC_PRECOMP
  #include <wx/wx.h>
#endif

const int MSGW = 150;
const int MSGH = 150;

///A MessageFrame osztály
///
///Ez az osztály felelős az üzenetablakhoz kapcsolódó műveletek végrehajtásáért.
class MessageFrame: public wxFrame 
{
  public:
public:
    MessageFrame(const wxString& title);
    
    void ShowMessage1(wxCommandEvent & event);
    void ShowMessage2(wxCommandEvent & event);
    void ShowMessage3(wxCommandEvent & event);
    void ShowMessage4(wxCommandEvent & event);
};

enum
{
  ID_INFO = 1,
  ID_ERROR = 2,
  ID_QUESTION = 3,
  ID_ALERT = 4,
};
