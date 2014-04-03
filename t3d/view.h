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

  /** Create callback.
  @param doc the document
  @param flags the flags
  @returns true on ok, false if not
   */
  virtual bool OnCreate(wxDocument *doc, long flags);  // NOLINT wx logic

  /** Draw callback.
  @param dc the dc.
   */
  virtual void OnDraw(wxDC *dc);

  /** Update callback.
  @param sender the sender
  @param hint the hint
   */
  virtual void OnUpdate(wxView *sender, wxObject *hint = NULL);

 private:
  DECLARE_EVENT_TABLE()
  DECLARE_DYNAMIC_CLASS(View)
};

#endif  // T3D_VIEW_H_
