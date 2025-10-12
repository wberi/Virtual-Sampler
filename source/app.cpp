#include <app.hpp>
#include <base.hpp>

const int WIDTH = 300;
const int HEIGHT = 300;

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
  MainFrame* main = new MainFrame(wxT("Virtual Sampler"), wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  main->Show(true);
  SetTopWindow(main);

  return true;
}
