#include <iostream>
#include <vector>
#include <ogui/ogui.h>
#include <ogui/parse.h>
#include "CoordsWidget.h"
#include "textrb.h"
#include "scene.h"

void Scene::load(int width, int height)
{
  m_CoordsWidget = CoordinatesBackground::create();
  m_CoordsWidget->set_rect(Rect(0, 0, width, height));
  m_CoordsWidget->start_polygon(0xFF00FF00);
  m_CoordsWidget->add_listener("scene", "clicked", OGUI_EVENT_CALLBACK
  {
    clicked(parse_Point(param));
  });
  widget_ptr desktop = OGUIManager::instance()->get_desktop();
  desktop->add_child(m_CoordsWidget);
  buttons_group_ptr g = ButtonsGroup::create();
  g->add_button("Wing");
  g->add_button("Motor");
  g->add_button("Battery");
  g->set_rect(Rect(200, 0, 800, 32));
  desktop->add_child(g);
  g->add_listener("scene","select",OGUI_EVENT_CALLBACK
  {
    set_mode(param);
  });
}

void Scene::clicked(const Point& p)
{
  if (m_Mode == "Wing")
  {
    m_CoordsWidget->add_polygon_point(pixel_to_mm(p));
    //m_WingPoints.push_back(pixel_to_mm(p));
  }
}
