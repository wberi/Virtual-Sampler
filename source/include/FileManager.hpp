#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
#include <wx/wx.h>
#include "nlohmann-json/json.hpp"
#include "Key.hpp"

using json = nlohmann::json;

class FileManager
{
public:
    static void SaveProfile(wxWindow* parent, const std::vector<Key*>& keys);
};

#endif