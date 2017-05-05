#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "pane.h"

class App: public wxApp
{
  virtual bool OnInit();

  wxFrame* frame;
  Pane* pane;
};

IMPLEMENT_APP(App)

bool App::OnInit()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame *)NULL, -1,  wxT("T3D - Tiled 3d Editor"), wxPoint(50,50), wxSize(400,200));

  pane = new Pane( (wxFrame*) frame);
  sizer->Add(pane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}
