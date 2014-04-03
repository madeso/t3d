// t3d - Copyright (c) Gustav

#ifndef T3D_MAINFRAME_H_
#define T3D_MAINFRAME_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/docmdi.h>
#include <wx/docview.h>

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

#endif  // T3D_MAINFRAME_H_
