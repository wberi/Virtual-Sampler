#pragma once 

#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

///A class that provides the logic behind the key buttons.
///This class is derived from the wxButton class.
class Key: public wxButton 
{
private:
  std::string pathToSound;

public:
  //ctor
  Key(wxWindow* parent, wxWindowID event);

  //setter 
  void setPathToSound(std::string newPathToSound);

  //getter
  std::string getPathToSound();
};
