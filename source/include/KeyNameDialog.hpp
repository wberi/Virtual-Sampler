#ifndef KEYNAMEDIALOG_HPP
#define KEYNAMEDIALOG_HPP

#include <wx/wxprec.h>
#ifndef WC_PRECOMP   
 #include <wx/wx.h>
#endif 

/////////////////////////////////////////////////
/// A custom window for selecting a Key's name and shortcut.
/////////////////////////////////////////////////
class KeyNameDialog: public wxDialog
{
	public:
		//Constructor
		KeyNameDialog (wxWindow* parent, wxWindowID id, const wxString& title,
				  const wxPoint& pos = wxDefaultPosition,
				  const wxSize& size = wxDefaultSize,
				  long style = wxDEFAULT_DIALOG_STYLE);
	
		//Widgets
		wxComboBox* keyOptions;
		wxTextCtrl* nameField;

		//Getters
		wxString GetShortcut();
		wxString GetName();
	
	private:
		//All possible shortcut choices
		wxString keyChoices[36] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
			"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
			"O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
		
		//Handle user pressing OK
		void OnOk(wxCommandEvent& event);
	
	//Event table 
	DECLARE_EVENT_TABLE();
};
#endif