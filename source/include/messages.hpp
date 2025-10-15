#pragma once

#include <wx/wxprec.h>
#ifndef WC_PRECOMP
  #include <wx/wx.h>
#endif

class Messages
{
private:
  wxMessageDialog* dial;

public:
  Messages();

  int ShowEngineFailureMessage();
  int ShowInvalidPathMessage();
  int ShowMissingFileMessage();
  int ShowQuitMessage();
  int ShowAboutMessage();
};


