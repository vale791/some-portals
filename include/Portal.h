#ifndef PORTAL
#define PORTAL

#include "raylib.h"

class Portal {
public:
  Portal(Vector2 pos, Color color, Portal *counterPart);
  ~Portal() = default;

  void bind(Portal* p);
  void unBind();
  void teleportToCounterpart(Vector2 &pos, Vector2 size);
  Vector2 getPos();
  Vector2 getSize();
  void setPos(Vector2 pos);
  Color getColor();
  Rectangle getRectangle();
  bool isActivated();
  void deActivate();
  void activate();

private:
  Portal *m_counterPart;
  bool m_activated = false;

  // m_pos and m_size are only used for get functions, set functions, and the constructor
  Vector2 m_position;
  Vector2 m_size = { 30, 30 };
  Rectangle m_rect;
  Color m_color;

};

#endif // PORTAL