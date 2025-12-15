#include <App.hpp>
#include <AppBase.hpp>

const int WIDTH = 300;
const int HEIGHT = 300;

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
  //Initialize the app
  MainFrame* main = new MainFrame(wxT("Virtual Sampler"), wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  main->Show(true); //Show the app
  SetTopWindow(main);

  return true;
}
