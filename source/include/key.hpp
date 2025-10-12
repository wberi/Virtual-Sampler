#pragma once 

#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

///A Key osztaly
///
///A wxButton kibovitett valtozata. El tudja tarolni az utvonalat egy hangoz.
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
