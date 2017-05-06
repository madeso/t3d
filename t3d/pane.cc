#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/glcanvas.h"

#include "pane.h"

#include "wxgl.h"

#include <sstream>

BEGIN_EVENT_TABLE(Pane, wxGLCanvas)
EVT_MOTION(Pane::OnMouseMoved)
EVT_LEFT_DOWN(Pane::OnMouseDown)
EVT_LEFT_UP(Pane::OnMouseReleased)
EVT_RIGHT_DOWN(Pane::OnRightClick)
EVT_LEAVE_WINDOW(Pane::OnMouseLeftWindow)
EVT_SIZE(Pane::OnSize)
EVT_KEY_DOWN(Pane::OnKeyPressed)
EVT_KEY_UP(Pane::OnKeyReleased)
EVT_MOUSEWHEEL(Pane::OnMouseWheelMoved)
EVT_PAINT(Pane::Render)
END_EVENT_TABLE()


// some useful events to use
void Pane::OnMouseMoved(wxMouseEvent &event) {}
void Pane::OnMouseDown(wxMouseEvent &event) {}
void Pane::OnMouseWheelMoved(wxMouseEvent &event) {}
void Pane::OnMouseReleased(wxMouseEvent &event) {}
void Pane::OnRightClick(wxMouseEvent &event) {}
void Pane::OnMouseLeftWindow(wxMouseEvent &event) {}
void Pane::OnKeyPressed(wxKeyEvent &event) {}
void Pane::OnKeyReleased(wxKeyEvent &event) {}


wxGLAttributes GetOpenglAttributes() {
  wxGLAttributes attributes;
  attributes.PlatformDefaults().RGBA().DoubleBuffer().Depth(16).EndList();

  bool supported = wxGLCanvas::IsDisplaySupported(attributes);

  if ( !supported )
  {
    wxMessageBox("Visual attributes for OpenGL are not accepted.\nThe app will exit now.",
                 "Error with OpenGL", wxOK | wxICON_ERROR);
  }

  return attributes;
}


Pane::Pane(wxFrame* parent) :
    wxGLCanvas(parent, GetOpenglAttributes())
{
  wxGLContextAttrs attributes;
  attributes.PlatformDefaults().OGLVersion(1, 0).EndList();

  context = new wxGLContext(this, nullptr, &attributes);

  // MeshLoadResult load = LoadMesh("testmesh.obj");
  try {
    mesh = CreateBox(1.0f, 1.0f, 1.0f);
  }
  catch(...) {
    wxMessageBox("fail");
  }

  // To avoid flashing on MSW
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

Pane::~Pane()
{
  delete context;
}

void Pane::OnSize(wxSizeEvent &evt)
{
//	wxGLCanvas::OnSize(evt);

  Refresh();
}

void Pane::Prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x,
                             int bottomrigth_y)
{

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
  glClearDepth(1.0f);	// Depth Buffer Setup
  glEnable(GL_DEPTH_TEST); // Enables Depth Testing
  glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_COLOR_MATERIAL);

  glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
  gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

void Pane::Prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x,
                             int bottomrigth_y)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
  glEnable(GL_TEXTURE_2D);   // textures
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int Pane::GetWidth()
{
  return GetSize().x;
}

int Pane::GetHeight()
{
  return GetSize().y;
}

void RenderMesh(const Mesh& mesh) {
  for(const MeshPart& part : mesh.parts) {
    const Material mat = mesh.materials[part.material];
    glColor4f(mat.diffuse.GetRed(), mat.diffuse.GetGreen(), mat.diffuse.GetBlue(), mat.alpha);
    for(int i=0; i<part.facecount; ++i) {
      int b = i * 3;
      const int pointsize = 5;
      glBegin(GL_LINE_LOOP);
      glVertex3fv(&part.points[part.faces[b + 0]*pointsize]);
      glVertex3fv(&part.points[part.faces[b + 1]*pointsize]);
      glVertex3fv(&part.points[part.faces[b + 2]*pointsize]);
      glEnd();
    }
  }
}

void Pane::Render(wxPaintEvent &evt)
{
  if(!IsShown()) return;

  wxGLCanvas::SetCurrent(*context);
  wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Prepare3DViewport(0, 0, GetWidth(), GetHeight());
  glLoadIdentity();

  glColor4f(0,0,1,1);
  glTranslatef(0,0,-5);
  glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

  RenderMesh(mesh);
  grid.Draw();

  glFlush();
  SwapBuffers();
}
