//
// Created by Gustav Jansson on 7/5 17.
//

#include "tilebrowser.h"

TileBrowser::TileBrowser(wxWindow *parent)
: wxDialog(parent, wxID_ANY, "Tile browser", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
}

void TileBrowser::OnOk(wxCommandEvent &event) {
  Close();
}

BEGIN_EVENT_TABLE(TileBrowser, wxDialog)
END_EVENT_TABLE()
