#pragma once

///A MainApp osztály
///
///Ez kezel minden eseményt, ami az alkalmazásban történik.
class MainApp: public wxApp
{
  public:
    virtual bool OnInit();
};

///A MainFrame osztály
///
///Az vizuális elemek megjelenítéséért felelős osztály.
class MainFrame: public wxFrame 
{
  public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size); 
};

DECLARE_APP(MainApp);
