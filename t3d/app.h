// t3d - Copyright (c) Gustav

#ifndef T3D_APP_H_
#define T3D_APP_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class wxView;

/** The t3d application.
 */
class T3dApp : public wxApp {
 public:
  /** Create the main window.
   */
  virtual bool OnInit();

  /** Create a child frame.
  @param view the view to create it from
  @returns the new frame
   */
  wxFrame* CreateChildFrame(wxView* view);
};

wxDECLARE_APP(T3dApp);

#endif  // T3D_APP_H_
