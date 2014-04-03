// t3d - Copyright (c) Gustav

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/docmdi.h>
#include <wx/docview.h>

class MyApp : public wxApp {
 public:
  virtual bool OnInit();
};

class MainFrame : public wxDocMDIParentFrame {
 public:
  explicit MainFrame(const wxString& title);

 private:
  void OnHello(wxCommandEvent& event);  // NOLINT - wx callbacks
  void OnExit(wxCommandEvent& event);   // NOLINT - wx callbacks
  void OnAbout(wxCommandEvent& event);  // NOLINT - wx callbacks
  wxDECLARE_EVENT_TABLE();

 private:
  wxDocManager docManager_;
};

enum {
  ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_Hello, MainFrame::OnHello)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  MainFrame* frame = new MainFrame("Hello World");
  frame->Show(true);
  return true;
}

MainFrame::MainFrame(const wxString& title) : wxDocMDIParentFrame() {
  wxDocMDIParentFrame::Create(&docManager_, NULL, wxID_ANY, title,
                              wxPoint(50, 50), wxSize(450, 340));

  wxMenu* menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                   "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");
}

void MainFrame::OnExit(wxCommandEvent& event) {  // NOLINT - wx callback
  Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {  // NOLINT - wx callback
  wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World",
               wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent& event) {  // NOLINT - wx callback
  wxLogMessage("Hello world from wxWidgets!");
}
