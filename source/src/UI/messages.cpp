#include <messages.hpp>

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
      wxT("Are you sure to quit?"), wxT("Question"), 
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  return dial->ShowModal();
}

int ShowMessage4() 
{
  wxMessageDialog *dial;
  return dial->ShowModal();
}
