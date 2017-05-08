//
// Created by Gustav Jansson on 7/5 17.
//

#ifndef T3D_TILEBROWSER_H
#define T3D_TILEBROWSER_H

#include "wx/wx.h"

class TileBrowser: public wxDialog
{
public:
  TileBrowser(wxWindow* parent);

private:
  void OnOk( wxCommandEvent & event );
};


#endif //T3D_TILEBROWSER_H
