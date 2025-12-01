#include "KeyNameDialog.hpp"
#include <wx/wx.h>

KeyNameDialog::KeyNameDialog (wxWindow* parent, wxWindowID id, const wxString& title,
                           const wxPoint& position, const wxSize& size, long style )
: wxDialog( parent, id, title, position, size, style)
{
	wxPoint position_helper;
	wxSize window_size;

	window_size.SetWidth(size.GetWidth() - 20);
	window_size.SetHeight(size.GetHeight() - 70);

	position_helper.x = 6; position_helper.y = 2;

	dialogText = new wxTextCtrl (this, -1, "button name", position_helper, window_size);

	position_helper.y += window_size.GetHeight() + 10;
	wxButton* ok_button = new wxButton(this, wxID_OK, _("OK"), position_helper, wxDefaultSize);
}

//Event table

BEGIN_EVENT_TABLE(KeyNameDialog, wxDialog)
  EVT_BUTTON(wxID_OK, KeyNameDialog::OnOk)
END_EVENT_TABLE()

wxString KeyNameDialog::GetText()
{
	return dialogText->GetLineText(0);
}

void KeyNameDialog::OnOk(wxCommandEvent& event)
{
	EndModal(0);
}
