// Modified by Cheddarbung - November 2026. Based on Hades Workshop 0.53 by Tirlititi. Distributed under GNU GPL v3.

#pragma once
#include <wx/translation.h>

#ifdef _
#undef _
#define _(value) wxGetTranslation(wxString(value))
#endif
