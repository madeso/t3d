#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/glcanvas.h"

#include "pane.h"

#include "wxgl.h"

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

// Vertices and faces of a simple cube to demonstrate 3D Render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };



Pane::Pane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
  context = new wxGLContext(this);
  // prepare a simple cube to demonstrate 3D Render
  // source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

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


void Pane::Render(wxPaintEvent &evt)
{
  if(!IsShown()) return;

  wxGLCanvas::SetCurrent(*context);
  wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ------------- draw some 2D ----------------
  Prepare2DViewport(0, 0, GetWidth() / 2, GetHeight());
  glLoadIdentity();

  // white background
  glColor4f(1, 1, 1, 1);
  glBegin(GL_QUADS);
  glVertex3f(0,0,0);
  glVertex3f(GetWidth(),0,0);
  glVertex3f(GetWidth(), GetHeight(),0);
  glVertex3f(0, GetHeight(),0);
  glEnd();

  // red square
  glColor4f(1, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex3f(GetWidth()/8, GetHeight()/3, 0);
  glVertex3f(GetWidth()*3/8, GetHeight()/3, 0);
  glVertex3f(GetWidth()*3/8, GetHeight()*2/3, 0);
  glVertex3f(GetWidth()/8, GetHeight()*2/3, 0);
  glEnd();

  // ------------- draw some 3D ----------------
  Prepare3DViewport(0, 0, GetWidth(), GetHeight());
  glLoadIdentity();

  glColor4f(0,0,1,1);
  glTranslatef(0,0,-5);
  glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

  glColor4f(1, 0, 0, 1);
  for (int i = 0; i < 6; i++)
  {
    glBegin(GL_LINE_STRIP);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glEnd();
  }

  glFlush();
  SwapBuffers();
}
