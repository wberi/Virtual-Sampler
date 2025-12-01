#pragma once 

#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

#include <miniaudio.h>

///A class that provides the logic behind the key buttons.
///This class is derived from the wxButton class.
class Key: public wxButton 
{
public:
  ma_sound sound;
  std::string sound_path;

  //ctor
  Key(wxWindow* parent, wxWindowID event);

  //dtor 
  ~Key();

  //getter
  ma_sound* getSound();
};
