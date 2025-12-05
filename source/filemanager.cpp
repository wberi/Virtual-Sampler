#include "FileManager.hpp"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <fstream>

void FileManager::SaveProfile(wxWindow* parent, const std::vector<Key*>& keys)
{
    wxFileDialog saveFileDialog(parent, _("Save JSON Profile"), "", "",
                                "JSON files (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    json profileJson;

    for (const auto& key : keys)
    {
        json keyData;
        
        keyData["sound_path"] = key->getSoundPath(); 
        keyData["shortcut"] = std::string(1, key->getShortCut());
        keyData["label"] = key->GetLabel().ToStdString();

        keyData["volume"] = key->getVolume();
        keyData["attack"] = key->getAttack();
        keyData["decay"] = key->getDecay();
        keyData["sustain"] = key->getSustain();
        keyData["release"] = key->getRelease();
        keyData["pitch"] = key->getPitchShift();
        keyData["cutoff"] = key->getCutoff();
        keyData["resonance"] = key->getResonance();

        profileJson.push_back(keyData);
    }

    std::ofstream file(saveFileDialog.GetPath().ToStdString());
    if (file.is_open())
    {
        file << profileJson.dump(4);
        file.close();
    }
    else
    {
        wxMessageBox("Could not open file for reading.", "Error", wxICON_ERROR);
    }
}