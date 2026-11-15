#pragma once
#include <wx/translation.h>

#ifdef _
#undef _
#define _(value) wxGetTranslation(wxString(value))
#endif
