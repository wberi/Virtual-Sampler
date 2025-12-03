#ifndef KEYNAMEDIALOG_HPP
#define KEYNAMEDIALOG_HPP

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

	    wxComboBox* keyOptions;
	    wxString GetText();


    private:
		wxString keyChoices[36] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
			"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
			"O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	    void OnOk(wxCommandEvent& event);

	DECLARE_EVENT_TABLE();
};
#endif