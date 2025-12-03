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
  ma_sound_group* soundGroupPtr = nullptr; // Pointer to the group created by the handler
  std::string sound_path;

  // --- New Per-Key Audio Attributes ---
  // Store slider values directly as member variables
  int volume;     // 0-100
  int attack;     // 0-1000 ms
  int decay;      // 0-1000 ms
  int sustain;    // 0-100 %
  int release;    // 0-2000 ms
  int pitchShift; // -12 to 12 st
  int cutoff;     // 20 to 20000 Hz
  int resonance;  // 0 to 10

  //ctor
  Key(wxWindow* parent);

  //dtor 
  ~Key();

  //Setter for the sound group pointer
  void setSoundGroupPtr(ma_sound_group* groupPtr);

  //Getters
  ma_sound* getSound();
  ma_sound_group* getSoundGroupPtr();

  // --- New Attribute Getters/Setters ---
  void setVolume(int val) { volume = val; }
  int getVolume() const { return volume; }

  void setAttack(int val) { attack = val; }
  int getAttack() const { return attack; }

  void setDecay(int val) { decay = val; }
  int getDecay() const { return decay; }

  void setSustain(int val) { sustain = val; }
  int getSustain() const { return sustain; }

  void setRelease(int val) { release = val; }
  int getRelease() const { return release; }

  void setPitchShift(int val) { pitchShift = val; }
  int getPitchShift() const { return pitchShift; }

  void setCutoff(int val) { cutoff = val; }
  int getCutoff() const { return cutoff; }

  void setResonance(int val) { resonance = val; }
  int getResonance() const { return resonance; }
};
#endif