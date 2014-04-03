// t3d - Copyright (c) Gustav

#ifndef T3D_APP_H_
#define T3D_APP_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/** The t3d application.
 */
class T3dApp : public wxApp {
 public:
  /** Create the main window.
   */
  virtual bool OnInit();
};

#endif  // T3D_APP_H_
