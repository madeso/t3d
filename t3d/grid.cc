#include "grid.h"
#include "wxgl.h"

Grid::Grid() : size_(10.0f), spacing_(1.0f) {}

void Grid::SetSize(float size) {size_ = size;}
float Grid::GetSize() const {return size_;}

void Grid::SetSpacing(float spacing) {spacing_ = spacing;}
float Grid::GetSpacing() {return spacing_;}

void Grid::Draw() const {
  glBegin(GL_LINES);
  DrawLinesAt(0);
  for(float s = spacing_; s<size_; s += spacing_) {
    DrawLinesAt(s);
    DrawLinesAt(-s);
  }
  glEnd();
}

void Grid::DrawLinesAt(float s) const {
  const float y = 0.0f;
  glVertex3f(-size_, y, s);
  glVertex3f(size_, y, s);
  glVertex3f(s, y, -size_);
  glVertex3f(s, y, -size_);
}
