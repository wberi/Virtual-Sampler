#ifndef KEY_HPP
#define KEY_HPP

#include <wx/event.h>
#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

#include <miniaudio.h>
#include <string>

typedef struct Sound 
{
  ma_sound* sound = nullptr;
  ma_hpf_node* hpfNode = nullptr;
  std::string sound_path;
  ma_sound_group* soundGroupPtr = nullptr;
} Sound;

///A class that provides the logic behind the key buttons.
///This class is derived from the wxButton class.
class Key: public wxButton
{
  //engine
  ma_engine* engine;

  //Sound
  Sound sound;

  //Filter
  ma_hpf_node_config hpfNodeConfig;
  ma_hpf_config hpfConfig;

  //Shortcut
  char shortcut = '-'; //It it unbound by default

  //Animation
  wxTimer* animationTimer;
  const wxColour DEFAULT_COLOR = *wxWHITE;
  const wxColour ACTIVE_COLOR = *wxGREEN;

  //Store slider values 
  int volume;
  int pitchShift;
  int pan;
  int cutoff;

  //Helper function
  void connectHpfNode();
public:

  //Constructor
  Key(wxWindow* parent);

  //Destructor
  ~Key();

  //Uninit sound
  void uninitSound();

  //Init engine config
  void setupEngine();

  //Setup sound from file path
  ma_result setupSound(ma_engine* engine, std::string filePath);

  //Setup sound group
  ma_result setupGroup(ma_engine* engine);

  //Play sound
  void playSound();

  //Animation methods
  void beginAnimateKey();
  void endAnimatekey(wxTimerEvent& event);

  void setupHighPassFilter();

  //Setters
  void setNewFilterFreq();
  void setShortCut(char shortcut);
  void setSoundPath(std::string soundPath);
  void setVolume(int val) {volume = val;}
  void setPitchShift(int val) {pitchShift = val;}
  void setPan(int val) {pan = val;}
  void setCutoff(int val) {cutoff = val;}

  //Getters
  ma_sound_group* getSoundGroupPtr();
  char getShortCut();
  std::string getSoundPath();
  int getVolume() const {return volume;}
  int getPitchShift() const {return pitchShift;}
  int getPan() const {return pan;}
  int getCutoff() const {return cutoff;}
};
#endif