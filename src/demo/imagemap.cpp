#include <ogui/ogui.h>
#include <ogui/parse.h>

using namespace OGUI;

void load_demo_layout();

static const int MAP_WIDTH = 400;
static const int MAP_HEIGHT = 300;

struct MapRegion
{
  const char* name;
  unsigned    color;
};

static const MapRegion g_Regions[] = {
  { "Circle",    0xFFE07030 },
  { "Rectangle", 0xFF30B040 },
  { "Triangle",  0xFF30C0E0 },
};
static const int REGION_COUNT = sizeof(g_Regions) / sizeof(g_Regions[0]);

/// Returns the index of the region containing (x,y), or -1 for the background
static int region_at(int x, int y)
{
  int dx = x - 100, dy = y - 100;
  if (dx*dx + dy*dy <= 60*60) return 0;
  if (x >= 220 && x < 360 && y >= 40 && y < 140) return 1;
  // Triangle with apex (200,170) and base from (100,280) to (300,280)
  if (y >= 170 && y < 280 && abs(x - 200) <= (y - 170) * 100 / 110) return 2;
  return -1;
}

/// Draws the map, brightening the selected region
static image_ptr create_map_image(int selected)
{
  image_ptr image(new Image(MAP_WIDTH, MAP_HEIGHT));
  for (int y = 0; y < MAP_HEIGHT; ++y)
  {
    unsigned* row = image->get_urow(y);
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
      int r = region_at(x, y);
      if (r < 0) row[x] = 0xFFE0E0E0;
      else if (r == selected) row[x] = brighten(g_Regions[r].color, 0.5f);
      else row[x] = g_Regions[r].color;
    }
  }
  return image;
}

/// Shows an image with named regions, reporting which region was clicked
void load_imagemap_layout()
{
  widget_ptr desktop = OGUIManager::instance()->get_desktop();

  // Remove previous widgets
  OGUIManager::instance()->clear();

  fill_widget_ptr background = FillWidget::create();
  background->set_rect(desktop->get_rect());
  background->set_layout(layout_ptr());
  background->set_color(0xFF0000AA);
  background->set_gradient(fPoint(1.0f, 0.5f));

  text_widget_ptr title = TextWidget::create("ImageMap Demo - click a shape");
  title->set_rect(Rect(40, 20, 600, 50));
  background->add_child(title);

  text_widget_ptr status = TextWidget::create("Nothing selected");
  status->set_rect(Rect(40, 380, 600, 410));
  background->add_child(status);

  // "clicked" is raised with the click position, local to the image
  image_widget_ptr map = ImageWidget::create();
  map->attach_image(create_map_image(-1));
  map->set_rect(Rect(40, 60, 40 + MAP_WIDTH, 60 + MAP_HEIGHT));
  ImageWidget* map_ptr = map.get();
  map->add_listener("demo", "clicked", [map_ptr, status](const xstring& name, const xstring& event_type, const xstring& param)
  {
    Point pos = parse_Point(param);
    int r = region_at(pos.x, pos.y);
    map_ptr->attach_image(create_map_image(r));
    xstring where = (r < 0 ? xstring("Background") : xstring(g_Regions[r].name));
    status->set_text(where + " clicked at " + param);
  });
  background->add_child(map);

  text_push_button_widget_ptr back = TextPushButtonWidget::create("Back");
  back->set_rect(Rect(460, 60, 600, 90));
  back->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_demo_layout();
  });
  background->add_child(back);

  desktop->add_child(background);
}
