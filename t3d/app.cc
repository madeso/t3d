// t3d - Copyright (c) Gustav

#include "t3d/app.h"
#include "t3d/mainframe.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  MainFrame* frame = new MainFrame("Hello World");
  frame->Show(true);
  return true;
}
