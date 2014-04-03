// t3d - Copyright (c) Gustav

#ifndef T3D_VIEW_H_
#define T3D_VIEW_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/docmdi.h>
#include <wx/docview.h>

/** The 3d view.
 */
class View : public wxView {
 public:
  /** Constructor.
   */
  View();
};

#endif  // T3D_VIEW_H_
