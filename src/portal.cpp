#include "Portal.h"
#include "raylib.h"
#include <iostream>
#include <thread>
#include <chrono>

void deActivateActivatePortal(Portal* p) {
  p->deActivate();
  std::this_thread::sleep_for(std::chrono::milliseconds(750));
  p->activate();
}

Portal::Portal(Vector2 pos, Color portalColor, Portal *counterPart): m_position(pos), m_color(portalColor), m_counterPart(nullptr) {
  m_rect.x = pos.x;
  m_rect.y = pos.y;
  m_rect.width = m_size.x;
  m_rect.height = m_size.y;
  if (counterPart != nullptr) {
    bind(counterPart);
  }

  std::thread *t = new std::thread(deActivateActivatePortal, this);
}

void Portal::bind(Portal* p) {
  m_counterPart = p;
  m_counterPart->m_counterPart = this;
}

void Portal::unBind() {
  if (m_counterPart != nullptr) {
    m_counterPart->m_counterPart = nullptr;
    m_counterPart = nullptr;
  }
}

void Portal::teleportToCounterpart(Vector2& pos, Vector2 size) {
  if (m_counterPart != nullptr && m_activated && m_counterPart->m_activated) {
    pos.x = m_counterPart->m_position.x + m_counterPart->m_size.x / 2 - size.x / 2;
    pos.y = m_counterPart->m_position.y + m_counterPart->m_size.y / 2 - size.y / 2;
    std::thread* t = new std::thread(deActivateActivatePortal, m_counterPart);
  }
}

bool Portal::isActivated() {
  return m_activated;
}

void Portal::deActivate() {
  m_activated = false;
}

void Portal::activate() {
  m_activated = true;
}

Vector2 Portal::getPos() {
  return m_position;
}

void Portal::setPos(Vector2 pos) {
  m_position = pos;
  m_rect = { pos.x, pos.y, m_size.x, m_size.y };
}

Vector2 Portal::getSize() {
  return m_size;
}

Color Portal::getColor() {
  return m_color;
}

Rectangle Portal::getRectangle() {
  return m_rect;
}
