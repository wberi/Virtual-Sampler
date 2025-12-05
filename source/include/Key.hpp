#ifndef KEY_HPP
#define KEY_HPP

#include <wx/event.h>
#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

#include <miniaudio.h>
#include <string>

///A class that provides the logic behind the key buttons.
///This class is derived from the wxButton class.
class Key: public wxButton
{
  //Sound
  ma_sound* sound = nullptr;
  ma_sound_group* soundGroupPtr = nullptr;
  std::string sound_path;

  //Shortcut
  char shortcut = '-'; //It it unbound by default

  //Animation
  wxTimer* animationTimer;
  const wxColour DEFAULT_COLOR = *wxWHITE;
  const wxColour ACTIVE_COLOR = *wxGREEN;

  //Store slider values 
  int volume;     
  int attack;
  int decay;
  int sustain;
  int release;
  int pitchShift;
  int cutoff;
  int resonance;
public:

  //Constructor
  Key(wxWindow* parent);

  //Destructor
  ~Key();

  //Uninit sound
  void uninitSound();

  //Setup sound from file path
  ma_result setupSound(ma_engine* engine, std::string filePath);

  //Setup sound group
  ma_result setupGroup(ma_engine* engine);

  //Play sound
  void playSound();

  //Animation methods
  void beginAnimateKey();
  void endAnimatekey(wxTimerEvent& event);

  //Setters
  void setShortCut(char shortcut);
  void setVolume(int val) {volume = val;}
  void setAttack(int val) {attack = val;}
  void setDecay(int val) {decay = val;}
  void setSustain(int val) {sustain = val;}
  void setRelease(int val) {release = val;}
  void setPitchShift(int val) {pitchShift = val;}
  void setCutoff(int val) {cutoff = val;}
  void setResonance(int val) {resonance = val;}

  //Getters
  ma_sound_group* getSoundGroupPtr();
  char getShortCut();
  int getVolume() const {return volume;}
  int getAttack() const {return attack;}
  int getDecay() const {return decay;}
  int getSustain() const {return sustain;}
  int getRelease() const {return release;}
  int getPitchShift() const {return pitchShift;}
  int getCutoff() const {return cutoff;}
  int getResonance() const {return resonance;}
};
#endif