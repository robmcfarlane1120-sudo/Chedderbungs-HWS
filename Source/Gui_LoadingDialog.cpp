// Modified by Cheddarbung - November 2026. Based on Hades Workshop 0.53 by Tirlititi. Distributed under GNU GPL v3.

#include "Gui_LoadingDialog.h"

#include "main.h"

LoadingDialog::LoadingDialog(wxWindow* parent, const wxString& title) :
	wxGenericProgressDialog(title,wxEmptyString,100,parent,wxPD_AUTO_HIDE),
	object_amount(1),
	is_active(false) {
	Show(false);
}

LoadingDialog::~LoadingDialog() {
}

static LoadingDialog* TheLoadingDialog = NULL;
wxWindow* TheLoadingDialogParent = NULL;

// Doesn't really create the dialog (it would be briefly shown otherwise)...
void LoadingDialogCreate(wxWindow* parent) {
	TheLoadingDialogParent = parent;
}

void LoadingDialogInit(unsigned int objamount, const wxString& title) {
	if (TheLoadingDialog==NULL)
		TheLoadingDialog = new LoadingDialog(TheLoadingDialogParent);
	if (TheLoadingDialog->is_active)
		return;
	TheLoadingDialog->wxTopLevelWindow::SetTitle(title);
	TheLoadingDialog->object_amount = objamount;
	TheLoadingDialog->is_active = true;
	TheLoadingDialog->wxDialog::Show(true);
	TheLoadingDialog->wxGenericProgressDialog::Update(0,wxString::Format(wxT("0 / %u"),objamount));
	TheLoadingDialogParent->Freeze();
	return;
}

void LoadingDialogUpdate(unsigned int objdone, wxString message) {
	if (!TheLoadingDialog->is_active || TheLoadingDialog->object_amount==0)
		return;
	const unsigned int percent = 100 * objdone / TheLoadingDialog->object_amount;
	const int value = percent < 100 ? percent : 99;
	if (value == TheLoadingDialog->GetValue())
		return;
	if (message.empty())
		message = wxString::Format(wxT("%u / %u"),objdone,TheLoadingDialog->object_amount);
	TheLoadingDialog->Update(value, message);
	wxYield();
	GetTopWindow()->SetDoubleBuffered(false);
}

void LoadingDialogEnd() {
	if (!TheLoadingDialog->is_active)
		return;
	TheLoadingDialog->wxGenericProgressDialog::Update(100,_(L"Done"));
	TheLoadingDialog->is_active = false;
	TheLoadingDialog->wxDialog::Show(false);
	TheLoadingDialogParent->Thaw();
}
