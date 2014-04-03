// t3d - Copyright (c) Gustav

#include "t3d/app.h"
#include "t3d/mainframe.h"

wxIMPLEMENT_APP(T3dApp);

bool T3dApp::OnInit() {
  MainFrame* frame = new MainFrame();
  frame->Show(true);
  return true;
}
