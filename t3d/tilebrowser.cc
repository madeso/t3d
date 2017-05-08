//
// Created by Gustav Jansson on 7/5 17.
//

#include "tilebrowser.h"

TileBrowser::TileBrowser(wxWindow *parent)
: wxDialog(parent, wxID_ANY, "Tile browser", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
  wxBoxSizer* topsizer = new wxBoxSizer( wxVERTICAL );
  topsizer->Add(CreateButtonSizer(wxOK | wxCANCEL));
  SetSizerAndFit(topsizer);
}

void TileBrowser::OnOk(wxCommandEvent &event) {
  Close();
}
