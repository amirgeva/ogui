#include <ogui/ogui.h>

using namespace OGUI;

void load_table_layout();
void load_buttons_layout();
void load_imagemap_layout();

/// This function shows dynamic building of widgets in code
void load_demo_layout()
{
  widget_ptr desktop=OGUIManager::instance()->get_desktop();
  Point desk_size=desktop->get_rect().get_size();

  fill_widget_ptr background = FillWidget::create();
  background->set_rect(desktop->get_rect());
  background->set_layout(layout_ptr());
  background->set_color(0xFFFF0000);
  background->set_gradient(fPoint(1.0f, 0.5f));

  // Remove any previous widgets
  OGUIManager::instance()->clear();

  text_push_button_widget_ptr button = TextPushButtonWidget::create("Table Demo");
  button->set_rect(Rect(200, 50, 440, 80));
  button->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_table_layout();
  });
  background->add_child(button);

  button = TextPushButtonWidget::create("Buttons Demo");
  button->set_rect(Rect(200, 100, 440, 130));
  button->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_buttons_layout();
  });
  background->add_child(button);

  button = TextPushButtonWidget::create("ImageMap Demo");
  button->set_rect(Rect(200, 150, 440, 180));
  button->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_imagemap_layout();
  });
  background->add_child(button);

  desktop->add_child(background);
}
