#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
#include <wx/wx.h>
#include "KeyFieldHandler.hpp"
#include "nlohmann-json/json.hpp"
#include "Key.hpp"
//This file was written using AI assistance!

using json = nlohmann::json;

class FileManager
{
public:
    static void SaveProfile(wxWindow* parent, const std::vector<Key*>& keys);
    static void LoadProfile(wxWindow* parent, KeyFieldHandler* kField);
};

#endif