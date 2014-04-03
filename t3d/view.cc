// t3d - Copyright (c) Gustav

#include "t3d/view.h"
#include "t3d/app.h"

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

IMPLEMENT_DYNAMIC_CLASS(View, wxView)

BEGIN_EVENT_TABLE(View, wxView)
END_EVENT_TABLE()

View::View() {}

bool View::OnCreate(wxDocument* doc, long flags) {  // NOLINT wx logic
  if (!wxView::OnCreate(doc, flags)) return false;

  T3dApp& app = wxGetApp();
  // create a new window and canvas inside it
  wxFrame* frame = app.CreateChildFrame(this);
  wxASSERT(frame == GetFrame());
  // m_canvas = new MyCanvas(this);
  frame->Show();

  return true;
}

void View::OnDraw(wxDC* dc) {}

void View::OnUpdate(wxView* sender, wxObject* hint) {
  wxView::OnUpdate(sender, hint);
  // if (m_canvas)
  //    m_canvas->Refresh();
}
