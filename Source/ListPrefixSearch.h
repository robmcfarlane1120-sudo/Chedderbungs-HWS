// Modified by Cheddarbung - November 2026. Based on Hades Workshop 0.53 by Tirlititi. Distributed under GNU GPL v3.

#pragma once

#include <wx/combobox.h>
#include <wx/listctrl.h>
#include <wx/weakref.h>
#include <wx/eventfilter.h>

class ListPrefixSearch final : public wxEventFilter {
	wxWeakRef<wxWindow> target;
	int anchor = 0;
	bool chord = false;

	static wxString SearchName(wxString name) {
		name.Trim(false);
		size_t offset = 0;
		while (offset < name.length() && name[offset] >= '0' && name[offset] <= '9')
			offset++;
		if (offset != 0) {
			while (offset < name.length() && name[offset] == ' ')
				offset++;
			if (offset < name.length() && name[offset] == ':')
				return name.Mid(offset + 1).Trim(false);
		}
		return name;
	}

public:
	int FilterEvent(wxEvent& event) override {
		const auto type = event.GetEventType();
		if (type != wxEVT_CHAR_HOOK && type != wxEVT_KEY_UP && type != wxEVT_KILL_FOCUS)
			return Event_Skip;
		if (type == wxEVT_KILL_FOCUS) {
			if (event.GetEventObject() == target.get())
				anchor = 0;
			return Event_Skip;
		}

		auto& key = static_cast<wxKeyEvent&>(event);
		int code = key.GetKeyCode();
		if (type == wxEVT_KEY_UP) {
			if (code == anchor)
				anchor = 0;
			return Event_Skip;
		}

		wxWindow* focus = wxWindow::FindFocus();
		auto* list = dynamic_cast<wxListBox*>(focus);
		auto* choice = dynamic_cast<wxChoice*>(focus);
		auto* combo = dynamic_cast<wxComboBox*>(focus);
		auto* report = dynamic_cast<wxListCtrl*>(focus);
		wxItemContainer* items = nullptr;
		wxEventType selectionEvent = wxEVT_NULL;
		if (list && !list->HasMultipleSelection()) {
			items = list;
			selectionEvent = wxEVT_LISTBOX;
		} else if (choice) {
			items = choice;
			selectionEvent = wxEVT_CHOICE;
		} else if (combo && combo->HasFlag(wxCB_READONLY)) {
			items = combo;
			selectionEvent = wxEVT_COMBOBOX;
		}

		if ((!items && (!report || !report->HasFlag(wxLC_SINGLE_SEL))) ||
		    key.ControlDown() || key.AltDown() || key.MetaDown() ||
		    !((code >= 'A' && code <= 'Z') || (!key.ShiftDown() && code >= '0' && code <= '9'))) {
			anchor = 0;
			return Event_Skip;
		}
		const int count = items ? items->GetCount() : report->GetItemCount();
		if (!count)
			return Event_Skip;
		if (focus != target.get() || (anchor && !wxGetKeyState(static_cast<wxKeyCode>(anchor))))
			anchor = 0;
		if (anchor == 0) {
			target = focus;
			anchor = code;
			chord = false;
		}
		wxString prefix(static_cast<wxChar>(anchor));
		if (code != anchor) {
			prefix += static_cast<wxChar>(code);
			chord = true;
		} else if (chord) {
			return Event_Processed;
		}

		const int current = items ? items->GetSelection() :
			report->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		for (int step = 1; step <= count; step++) {
			const int index = (current + step) % count;
			wxString label = items ? items->GetString(index) : report->GetItemText(index);
			if (SearchName(label).Left(prefix.length()).CmpNoCase(prefix) != 0)
				continue;
			if (index != current) {
				if (items) {
					items->SetSelection(index);
					wxCommandEvent selected(selectionEvent, focus->GetId());
					selected.SetEventObject(focus);
					selected.SetInt(index);
					selected.SetString(label);
					if (items->HasClientObjectData())
						selected.SetClientObject(items->GetClientObject(index));
					else if (items->HasClientUntypedData())
						selected.SetClientData(items->GetClientData(index));
					focus->ProcessWindowEvent(selected);
				} else {
					report->EnsureVisible(index);
					report->SetItemState(index, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED,
						wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
				}
			}
			break;
		}
		return Event_Processed;
	}
};
