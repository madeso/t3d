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

  int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

  pane = new Pane( (wxFrame*) frame, args);
  sizer->Add(pane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}
