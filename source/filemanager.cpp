#include "FileManager.hpp"
#include "KeyFieldHandler.hpp"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <fstream>
#include <map>
#include <string>

//This file was written using AI assistance!

//Save key field to JSON file
void FileManager::SaveProfile(wxWindow* parent, const std::vector<Key*>& keys)
{
    //Create and show file browser
    wxFileDialog saveFileDialog(parent, _("Save JSON Profile"), "", "save.json",
                                "JSON files (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if(saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    //Create JSON object
    json profileJson;

    //Iterate through the keys
    for(const auto& key : keys)
    {
        //JSON data element
        json keyData;
        
        //set properties
        keyData["sound_path"] = key->getSoundPath(); 
        keyData["shortcut"] = std::string(1, key->getShortCut());
        keyData["label"] = key->GetLabel().ToStdString();

        keyData["volume"] = key->getVolume();
        keyData["pitch"] = key->getPitchShift();
        keyData["panning"] = key->getPan();
        keyData["cutoff"] = key->getCutoff();

        //add to JSON object
        profileJson.push_back(keyData);
    }

    //Write to file
    std::ofstream file(saveFileDialog.GetPath().ToStdString());
    if(file.is_open())
    {
        file << profileJson.dump(4);
        file.close();
    }
    else
    {
        //Show error
        wxMessageBox("Could not open file for reading.", "Error", wxICON_ERROR);
    }
}

//Load profile back from JSON file
void FileManager::LoadProfile(wxWindow* parent, KeyFieldHandler* kField)
{
    //Get all the references
    std::vector<Key*>& keys = kField->getKeys();
    std::map<char, Key*>& keyMap = kField->getKeyMap();
    ma_engine* engine = kField->getEngine();


    //Create and show file browser
    wxFileDialog openFileDialog(parent, _("Open JSON Profile"), "", "",
                                "JSON files (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if(openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    //Open file
    std::ifstream file(openFileDialog.GetPath().ToStdString());
    if(!file.is_open())
    {
        //Show error
        wxMessageBox("Could not open file for reading.", "Error", wxICON_ERROR);
        return;
    }

    try
    {
        //JSON object for reading
        json profileJson;
        file >> profileJson;

        if(!profileJson.is_array())
        {
            //Show error if the file is invalid
            wxMessageBox("Invalid JSON format: Expected an array.", "Error", wxICON_ERROR);
            return;
        }

        //Clear out any binds to avoid errors
        keyMap.clear();

        //Start reading
        for(size_t i = 0; i < profileJson.size(); ++i)
        {
            if (i >= keys.size())
            {
                break; 
            }

            Key* key = keys[i];
            const auto& data = profileJson[i];

            ////Clear out any keys currently in the field to avoid errors
            key->uninitSound();
            key->setShortCut('-');
            key->SetLabel("No sound");

            //Init sound if we have a sound path
            std::string path = data.value("sound_path", "");
            if(!path.empty())
            {
                if(key->setupSound(engine, path) != MA_SUCCESS)
                {
                    //TODO handle this error
                }
            }

            //Check shortcut
            std::string sc = data.value("shortcut", "-");
            if(!sc.empty())
            {
                char shortcutChar = sc[0];
                key->setShortCut(shortcutChar);
                
                //add bind and change button event if the shortcut is not default
                if(shortcutChar != '-')
                {
                    keyMap[shortcutChar] = key;
                    kField->setKeyBind(key); //set keybind
                }
            }

            //Set the labelkey->setPitchShift(data.value("pitch", 0));
            std::string label = data.value("label", "");
            if(!label.empty()) 
            {
                key->SetLabel(label);
            }

            //Set the rest of the values
            key->setVolume(data.value("volume", 80));
            key->setPitchShift(data.value("pitch", 0));
            key->setPan(data.value("panning", 0));
            key->setCutoff(data.value("cutoff", 5000));

            if(!path.empty())
            {
                ma_sound_group_set_volume(key->getSoundGroupPtr(), key->getVolume() / 100.0);
                 
                float pitch_factor = pow(2.0f, key->getPitchShift() / 12.0f);
                ma_sound_group_set_pitch(key->getSoundGroupPtr(), pitch_factor);

                ma_sound_group_set_pan(key->getSoundGroupPtr(), key->getPan());

                key->setNewFilterFreq();
            }
        }
    }
    catch (const json::exception& e)
    {
        //Show parsing error
        wxMessageBox(wxString::Format("JSON Parsing Error: %s", e.what()), "Error", wxICON_ERROR);
    }
}