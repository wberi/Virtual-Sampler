#include <messages.hpp>
#include <wx/chartype.h>
#include <wx/gtk/msgdlg.h>

int ShowMessage1() 
{
  wxMessageDialog *dial;
  return dial->ShowModal();
}

int ShowMessage2() 
{
   wxMessageDialog *dial;
   return dial->ShowModal();
}

int ShowQuitMessage() 
{
  wxMessageDialog *dial = new wxMessageDialog(NULL, 
      wxT("Are you sure to quit?"), wxT("You are about to quit..."), 
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  return dial->ShowModal();
}

int ShowAboutMessage() 
{
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Welcome to Virtual Sampler!"), wxT("About"), wxOK_DEFAULT | wxICON_INFORMATION);
  return dial->ShowModal();
}
