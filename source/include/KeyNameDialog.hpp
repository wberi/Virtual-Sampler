#pragma once 

#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

class KeyNameDialog: public wxDialog
{
    public:
	    KeyNameDialog (wxWindow* parent, wxWindowID id, const wxString& title,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE);

	    wxTextCtrl* dialogText;
	    wxString GetText();


    private:
	    void OnOk(wxCommandEvent& event);

	DECLARE_EVENT_TABLE();
};
