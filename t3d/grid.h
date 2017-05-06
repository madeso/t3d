//
// Created by Gustav Jansson on 6/5 17.
//

#ifndef T3D_GRID_H
#define T3D_GRID_H


class Grid {
public:
  Grid();

  void SetSize(float size);
  float GetSize() const;

  void SetSpacing(float spacing);
  float GetSpacing();

  void Draw() const;

private:
  void DrawLinesAt(float s) const;
  float size_;
  float spacing_;
};


#endif // T3D_GRID_H
