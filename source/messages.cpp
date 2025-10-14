#include <cstddef>
#include <messages.hpp>
#include <wx/chartype.h>
#include <wx/gtk/msgdlg.h>

int ShowInvalidPathMessage()
{
  wxMessageDialog *dial = 
    new wxMessageDialog(NULL, wxT("szar path"), wxT("Invalid path")); //TODO: write normal error message
  return dial->ShowModal();
}

int ShowMissingFileMessage() 
{
   wxMessageDialog *dial = 
    new wxMessageDialog(NULL, wxT("There is no sound file attached to this key.\nA new file will be assigned now."), wxT("Missing sound file"));
   return dial->ShowModal();
}

int ShowQuitMessage() 
{
  wxMessageDialog *dial 
    = new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT("You are about to quit..."), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  return dial->ShowModal();
}

int ShowAboutMessage() 
{
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Virtual Sampler\nBéri Márk\n2025"), wxT("About"), wxOK_DEFAULT | wxICON_INFORMATION);
  return dial->ShowModal();
}
