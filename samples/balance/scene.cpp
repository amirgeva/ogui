#include <iostream>
#include <vector>
#include <ogui/ogui.h>
#include "CoordsWidget.h"
#include "textrb.h"


void load_scene(int width, int height)
{
  coord_background_widget_ptr bg = CoordinatesBackground::create();
  bg->set_rect(Rect(0, 0, width, height));
  widget_ptr desktop = OGUIManager::instance()->get_desktop();
  desktop->add_child(bg);
  buttons_group_ptr g = ButtonsGroup::create();
  g->add_button("Wing");
  g->add_button("Motor");
  g->add_button("Battery");
  g->set_rect(Rect(200, 0, 800, 32));
  desktop->add_child(g);
}
