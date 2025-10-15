#include <messages.hpp>
#include <wx/gtk/msgdlg.h>


Messages::Messages()
{
  dial = new wxMessageDialog(NULL, wxT("This is a default message."), wxT("Message")); 
}

int Messages::ShowEngineFailureMessage()
{
  dial = new wxMessageDialog(NULL, wxT("Sound engine failure!"), wxT("Error"), wxOK_DEFAULT);
  return dial->ShowModal();
}

int Messages::ShowInvalidPathMessage()
{
  dial = new wxMessageDialog(NULL, wxT("Invalid path"), wxT("Error")); //TODO: write normal error message
  return dial->ShowModal();
}

int Messages::ShowMissingFileMessage() 
{
   dial = 
    new wxMessageDialog(NULL, wxT("There is no sound file attached to this key.\nA new file will be assigned now."), wxT("Missing sound file"));
   return dial->ShowModal();
}

int Messages::ShowQuitMessage() 
{
  dial = new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT("You are about to quit..."), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  return dial->ShowModal();
}

int Messages::ShowAboutMessage() 
{
  dial = new wxMessageDialog(NULL, wxT("Virtual Sampler\nBéri Márk\n2025"), wxT("About"), wxOK_DEFAULT | wxICON_INFORMATION);
  return dial->ShowModal();
}
