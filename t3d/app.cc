#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "pane.h"
#include "tilebrowser.h"

#include "aboutbox.h"
#include "about_img.h"

class App: public wxApp
{
  virtual bool OnInit();

};

IMPLEMENT_APP(App)

class MainFrame : wxFrame {
public:
  MainFrame();

  void OnNewTile(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

private:
  Pane* pane;
};

bool App::OnInit()
{
  new MainFrame();
  return true;
}

enum EventId {
  ID_NEWTILE = 1
};


MainFrame::MainFrame()
    : wxFrame((wxFrame *)NULL, -1,  wxT("T3D - Tiled 3d Editor"), wxPoint(50,50), wxSize(400,200))
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  pane = new Pane(this);
  sizer->Add(pane, 1, wxEXPAND);

  wxMenuBar* m_pMenuBar = new wxMenuBar();

  Bind(wxEVT_MENU, &MainFrame::OnNewTile, this, ID_NEWTILE);
  Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);

  // File Menu
  wxMenu* m_pFileMenu = new wxMenu();
  m_pFileMenu->Append(wxID_OPEN, _T("&Open"));
  m_pFileMenu->Append(wxID_SAVE, _T("&Save"));
  m_pFileMenu->AppendSeparator();
  m_pFileMenu->Append(ID_NEWTILE, _T("New &Tile\tCtrl-T"));
  m_pFileMenu->AppendSeparator();
  m_pFileMenu->Append(wxID_EXIT, _T("&Quit"));
  m_pMenuBar->Append(m_pFileMenu, _T("&File"));

  // About menu
  wxMenu* m_pHelpMenu = new wxMenu();
  m_pHelpMenu->Append(wxID_ABOUT, _T("&About"));
  m_pMenuBar->Append(m_pHelpMenu, _T("&Help"));

  SetMenuBar(m_pMenuBar);

  SetSizer(sizer);
  SetAutoLayout(true);

  Show();
}



void MainFrame::OnNewTile(wxCommandEvent &event) {
  TileBrowser dlg(this);
  dlg.ShowModal();
}


void MainFrame::OnAbout(wxCommandEvent &event) {
  // Create About box
  wxMozillaLikeAboutBoxDialog * dlg = new wxMozillaLikeAboutBoxDialog(this);
  // Set application name
  dlg->SetAppName(wxTheApp->GetAppName());
  // Set application version
  dlg->SetVersion(wxT("1.0.0 b1"));
  // Set copyright message
  dlg->SetCopyright(wxString::Format(wxT("%c %i %s"),
                                     (wxChar) 0x00A9, wxDateTime::Now().GetYear(),
                                     _("Volodymir (T-Rex) Tryapichko. All rights reserved. Please contact author if you have any copyright-related questions.")));
  // Set build info message. This is optional step. If you don't specify build info message then
  // default one will be used
  dlg->SetCustomBuildInfo(wxString::Format(wxT("%s. %s"),
                                           wxMozillaLikeAboutBoxDialog::GetBuildInfo(wxMozillaLikeAboutBoxDialog::wxBUILDINFO_LONG).GetData(),
                                           _("Compiled by T-Rex personally :)")));
  // Set header bitmap
  dlg->SetHeaderBitmap(wxGetBitmapFromMemory(about_jpg_start, about_jpg_size));
  // Apply changes
  dlg->ApplyInfo();
  // Show dialog
  dlg->ShowModal();
  // Destroy dialog
  dlg->Destroy();
}
