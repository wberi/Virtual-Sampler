#include "miniaudio.h"
#include <Key.hpp>
#include <cstddef>
#include <wx/timer.h>
#include <wx/wxcrtvararg.h>

//Default button dimension values
const int WIDTH = 150;
const int HEIGHT = 150;

//Default values from SliderFieldHandler
const int DEFAULT_VOLUME = 80; //Real sound volume scale: 0.0 - 1.0
const int DEFAULT_PITCH = 0; //Real pitch scale: 0.0 - 1.0 
                             //Based on this formula: F = 2^(N/12)
const int DEFAULT_PAN = 0;
const int DEFAULT_CUTOFF = 1;

//Constructor
Key::Key(wxWindow* parent)
  :wxButton(parent, -1, wxT("No sound"), wxDefaultPosition, wxSize(WIDTH, HEIGHT), 0)
{
    //Initialize sound attributes
    setVolume(DEFAULT_VOLUME);
    setPitchShift(DEFAULT_PITCH);
    setPan(DEFAULT_PAN);
    setCutoff(DEFAULT_CUTOFF);
    sound.sound_path = "";

    //Set default ani,ation values
    this->SetForegroundColour(DEFAULT_COLOR); //set default color
    animationTimer = new wxTimer(); //create timer
    animationTimer->Bind(wxEVT_TIMER, &Key::endAnimatekey, this);
}

//Destructor
Key::~Key()
{
  uninitSound();
  ma_sound_group_uninit(sound.soundGroupPtr);
}

//Separate function for sound init (because of reset)
void Key::uninitSound()
{
  ma_sound_uninit(sound.sound);
  ma_hpf_node_uninit(sound.hpfNode, NULL);
}

//Sound init
ma_result Key::setupSound(ma_engine* engine, std::string filePath)
{
    this->sound.sound_path = filePath;
    sound.sound = new ma_sound();

    ma_result result = ma_sound_init_from_file(engine, filePath.c_str(), 
        MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, 
        NULL, NULL, sound.sound);

    if(result != MA_SUCCESS) 
    {
      return result; 
    }

    //Filter setup
    setupHighPassFilter();
    connectHpfNode();

    return MA_SUCCESS;
}

//Sound group init
ma_result Key::setupGroup(ma_engine* engine)
{ 
  this->engine=engine;
  sound.soundGroupPtr = new ma_sound_group();

  return ma_sound_group_init(engine, MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, sound.soundGroupPtr);
}

//Function to connect the filter node to the right nodes in the graph
void Key::connectHpfNode()
{
  //Connect filter to the sound group node
  ma_node_attach_output_bus(sound.hpfNode, 0, sound.soundGroupPtr, 0);

  //Connect sound to the filter node
  ma_node_attach_output_bus(sound.sound, 0, sound.hpfNode, 0);

  //Connect group to the output node
  ma_node_attach_output_bus(sound.soundGroupPtr, 0, 
        ma_node_graph_get_endpoint(ma_engine_get_node_graph(engine)), 0);
}

//Filter init
void Key::setupHighPassFilter()
{
  //Node configuration
  hpfNodeConfig = ma_hpf_node_config_init( 
    ma_engine_get_channels(engine) ,
    ma_engine_get_sample_rate(engine),
    cutoff,
    5);

  //Configuration for value modification
  hpfConfig = ma_hpf_config_init(ma_format_f32,
    ma_engine_get_channels(engine) ,
    ma_engine_get_sample_rate(engine),
    cutoff, 
    5);

  //Initialize node
  sound.hpfNode = new ma_hpf_node;

  ma_result result =  ma_hpf_node_init(
    ma_engine_get_node_graph(engine),
    &hpfNodeConfig,
    NULL,
    sound.hpfNode);
  
    if(result != MA_SUCCESS)
    {
      delete sound.hpfNode;
      sound.hpfNode = nullptr;
    }
}

//Refresh filter with new cutoff freq
void Key::setNewFilterFreq()
{
  hpfConfig.cutoffFrequency = cutoff;
  ma_result result = ma_hpf_node_reinit(&hpfConfig, sound.hpfNode);
  if(result != MA_SUCCESS)
  {
    //TODO error
    wxPrintf("Failed to reinitialize node!!!");
  }

}

//Plays the sound on button press
void Key::playSound()
{
  if(ma_sound_is_playing(sound.sound))
  {
    //If the sound is still playing, we need to restart it 
    ma_sound_seek_to_pcm_frame(sound.sound, 0);
  }
  else
  {
    //We just play the sound
    ma_sound_start(sound.sound);
  }
}

//Start the animation
void Key::beginAnimateKey()
{
  this->SetForegroundColour(ACTIVE_COLOR);
  animationTimer->Start(100, wxTIMER_ONE_SHOT);
}

//Finish the animation
void Key::endAnimatekey(wxTimerEvent& event)
{
  this->SetForegroundColour(DEFAULT_COLOR);
  animationTimer->Stop();
  this->Refresh();
}

//Return the sound group that the Key belongs to
ma_sound_group* Key::getSoundGroupPtr()
{
  return sound.soundGroupPtr;
}

void Key::setShortCut(char shortcut)
{
  this->shortcut = shortcut;
}

char Key::getShortCut()
{
  return shortcut;
}

void Key::setSoundPath(std::string soundPath)
{
  this->sound.sound_path = soundPath;
}

std::string Key::getSoundPath()
{
  return sound.sound_path;
}