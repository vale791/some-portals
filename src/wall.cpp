#include "Wall.h"
#include "raylib.h"

Wall::Wall(Vector2 pos, Vector2 size, Color color) : m_position(pos), m_size(size), m_color(color) {
  m_rect = { m_position.x, m_position.y, m_size.x, m_size.y };
}

void Wall::draw() {
  DrawRectangleRec(m_rect, m_color);
}
