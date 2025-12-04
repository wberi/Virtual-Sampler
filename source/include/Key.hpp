#ifndef KEY_HPP
#define KEY_HPP

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
public:
  ma_sound sound;
  ma_sound_group* soundGroupPtr = nullptr;
  std::string sound_path;

  //Store slider values 
  int volume;     
  int attack;
  int decay;
  int sustain;
  int release;
  int pitchShift;
  int cutoff;
  int resonance;

  //Constructor
  Key(wxWindow* parent);

  //Destructor (for destroying sounds?)
  ~Key();

  //Setters
  void setSoundGroupPtr(ma_sound_group* groupPtr);
  void setVolume(int val) {volume = val;}
  void setAttack(int val) {attack = val;}
  void setDecay(int val) {decay = val;}
  void setSustain(int val) {sustain = val;}
  void setRelease(int val) {release = val;}
  void setPitchShift(int val) {pitchShift = val;}
  void setCutoff(int val) {cutoff = val;}
  void setResonance(int val) {resonance = val;}

  //Getters
  ma_sound* getSound();
  ma_sound_group* getSoundGroupPtr();
  int getVolume() const {return volume * 10.0;} //Needs to be multiplied by 10 because of slider display
  int getAttack() const {return attack;}
  int getDecay() const {return decay;}
  int getSustain() const {return sustain;}
  int getRelease() const {return release;}
  int getPitchShift() const {return pitchShift;}
  int getCutoff() const {return cutoff;}
  int getResonance() const {return resonance;}
};
#endif