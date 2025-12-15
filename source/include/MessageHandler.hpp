#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <wx/wxprec.h>
#ifndef WC_PRECOMP
  #include <wx/wx.h>
#endif

class Messages
{
private:
  //Base message dialog
  wxMessageDialog* dial;

public:
  //Constructor
  Messages();

  //Messages
  int ShowEngineFailureMessage();
  int ShowInvalidPathMessage();
  int ShowSaveErrorMessage();
  int ShowBlockedShortcutMessage();
  int ShowQuitMessage();
  int ShowAboutMessage();
};
#endif