#include <MessageHandler.hpp>
#include <wx/gtk/msgdlg.h>

/////////////////////////////////////////////////
/// Shows deafult message.
/////////////////////////////////////////////////
Messages::Messages()
{
  dial = new wxMessageDialog(NULL, wxT("This is a default message."), wxT("Message")); 
}

/////////////////////////////////////////////////
/// Shows message for sound errors.
/////////////////////////////////////////////////
int Messages::ShowEngineFailureMessage()
{
  dial = new wxMessageDialog(NULL, wxT("Sound engine failure!"), wxT("Error"), wxOK_DEFAULT);
  return dial->ShowModal();
}

/////////////////////////////////////////////////
/// Shows invalid path message.
/////////////////////////////////////////////////
int Messages::ShowInvalidPathMessage()
{
  dial = new wxMessageDialog(NULL, wxT("Invalid path"), wxT("Error")); //TODO: write normal error message
  return dial->ShowModal();
}

/////////////////////////////////////////////////
/// Shows save error message.
/////////////////////////////////////////////////
int Messages::ShowSaveErrorMessage() 
{
   dial = 
    new wxMessageDialog(NULL, wxT("Could not open file for writing."), wxT("Save error"));
   return dial->ShowModal();
}

/////////////////////////////////////////////////
/// Shows messages for blocked shortcut.
/////////////////////////////////////////////////
int Messages::ShowBlockedShortcutMessage()
{
     dial = 
    new wxMessageDialog(NULL, wxT("This key is already in use. Please choose another one."), wxT("Shortcut blocked"));
   return dial->ShowModal();
}

/////////////////////////////////////////////////
/// Shows quit confirm message.
/////////////////////////////////////////////////
int Messages::ShowQuitMessage() 
{
  dial = new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT("You are about to quit..."), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  return dial->ShowModal();
}

/////////////////////////////////////////////////
/// Shows about message.
/////////////////////////////////////////////////
int Messages::ShowAboutMessage() 
{
  dial = new wxMessageDialog(NULL, wxT("A simple sampler program written in C++"), wxT("About"), wxOK_DEFAULT | wxICON_INFORMATION);
  return dial->ShowModal();
}
