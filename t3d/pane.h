#ifndef T3D_PANE
#define T3D_PANE

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "core/mesh.h"

#include "grid.h"

class Pane : public wxGLCanvas
{
  public:
  explicit Pane(wxFrame* parent);
  virtual ~Pane();

  int GetWidth();
  int GetHeight();

  void Render(wxPaintEvent &evt);
  void Prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x,
                         int bottomrigth_y);
  void Prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x,
                         int bottomrigth_y);

  // events
  void OnSize(wxSizeEvent &evt);
  void OnMouseMoved(wxMouseEvent &event);
  void OnMouseDown(wxMouseEvent &event);
  void OnMouseWheelMoved(wxMouseEvent &event);
  void OnMouseReleased(wxMouseEvent &event);
  void OnRightClick(wxMouseEvent &event);
  void OnMouseLeftWindow(wxMouseEvent &event);
  void OnKeyPressed(wxKeyEvent &event);
  void OnKeyReleased(wxKeyEvent &event);

 DECLARE_EVENT_TABLE()

 private:
  wxGLContext* context;
  Mesh mesh;
  Grid grid;
};

#endif // T3D_PANE
