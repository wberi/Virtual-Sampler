#include "AppBase.hpp"
#include "KeyNameDialog.hpp"
#include <wx/gtk/combobox.h>
#include <wx/gtk/textctrl.h>
#include <wx/stringimpl.h>
#include <wx/wx.h>

//UI layout done with AI assistance!
KeyNameDialog::KeyNameDialog (wxWindow* parent, wxWindowID id, const wxString& title,
                           const wxPoint& position, const wxSize& size, long style )
: wxDialog( parent, id, title, position, size, style)
{
	const int DIALOG_WIDTH = 200;
    const int DIALOG_HEIGHT = 100;
    
    const int MARGIN = 8;
    const int SPACING = 6;

    const int COMBO_WIDTH = DIALOG_WIDTH - (2 * MARGIN) - 5;
    const int COMBO_HEIGHT = 25;
    
    wxPoint combo_pos(MARGIN, MARGIN);
    wxSize combo_size(COMBO_WIDTH, COMBO_HEIGHT);
    
    keyOptions = new wxComboBox(this, -1, wxEmptyString, combo_pos, combo_size, 
        sizeof(keyChoices) / sizeof(wxString), keyChoices, wxCB_READONLY);

    int y_start_row_2 = combo_pos.y + combo_size.GetHeight() + SPACING;
    
    wxPoint label_pos(MARGIN, y_start_row_2);
    wxStaticText* nameFieldLabel = new wxStaticText(this, wxID_ANY, "Name:", label_pos);
    
    wxSize labelSize = nameFieldLabel->GetBestSize();
    
    int label_padding = 5;
    
    wxPoint textctrl_pos(MARGIN + labelSize.GetWidth() + label_padding, y_start_row_2);
    
    const int TEXTCTRL_WIDTH = DIALOG_WIDTH - textctrl_pos.x - MARGIN;
    const int TEXTCTRL_HEIGHT = 25;
    wxSize textctrl_size(TEXTCTRL_WIDTH, TEXTCTRL_HEIGHT);
    
    nameField = new wxTextCtrl(this, wxID_ANY, wxEmptyString, textctrl_pos, textctrl_size, 0);
    nameField->SetMaxLength(13); //set character limit, so it fits inside the Key

    int y_start_row_3 = y_start_row_2 + textctrl_size.GetHeight() + SPACING;
    
    wxButton* ok_button_prototype = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize);
    wxSize buttonSize = ok_button_prototype->GetBestSize();
    delete ok_button_prototype;
    
    wxPoint button_pos(DIALOG_WIDTH - MARGIN - buttonSize.GetWidth(), y_start_row_3);

    wxButton* ok_button = new wxButton(this, wxID_OK, _("OK"), button_pos, buttonSize);

    SetClientSize(DIALOG_WIDTH, y_start_row_3 + buttonSize.GetHeight() + MARGIN);
}

//Event table
BEGIN_EVENT_TABLE(KeyNameDialog, wxDialog)
  EVT_BUTTON(wxID_OK, KeyNameDialog::OnOk)
END_EVENT_TABLE()

wxString KeyNameDialog::GetShortcut()
{
	wxString selected = keyOptions->GetStringSelection();
	return !selected.IsEmpty() ? selected : _("0");
}

wxString KeyNameDialog::GetName()
{
	wxString value = nameField->GetValue();
	return !value.IsEmpty() ? value : "Key";
}

void KeyNameDialog::OnOk(wxCommandEvent& event)
{
  //Close the dialog
	EndModal(0);
}
