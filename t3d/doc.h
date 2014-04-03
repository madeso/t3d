// t3d - Copyright (c) Gustav

#ifndef T3D_DOC_H_
#define T3D_DOC_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/docmdi.h>
#include <wx/docview.h>

/** The document.
 */
class Doc : public wxDocument {
 public:
  /** Constructor.
   */
  Doc();

  /** Wx widgets code.
   */
  wxDECLARE_NO_COPY_CLASS(Doc);
  DECLARE_DYNAMIC_CLASS(Doc)
};

#endif  // T3D_DOC_H_
