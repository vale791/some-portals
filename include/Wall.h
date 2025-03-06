#include "raylib.h"
#ifndef WALL
#define WALL

class Wall {
public:
  Wall(Vector2 pos, Vector2 size, Color color);
  void draw();
  ~Wall() = default;
private:
  Vector2 m_position;
  Vector2 m_size;
  Rectangle m_rect;
  Color m_color;
};

#endif // WALL