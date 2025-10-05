#include <wx/wxprec.h>

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif // !WX_PRECOMP

#include <UI/base.hpp>

IMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
  MainFrame* main = new MainFrame(_("Virtual Sampler"), wxDefaultPosition, wxSize(300, 300));
  main->Show(true);
  SetTopWindow(main);
  return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size): 
  wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
  //init buttons and other widgets here
}




