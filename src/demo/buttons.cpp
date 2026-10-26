#include <ogui/ogui.h>

using namespace OGUI;

void load_demo_layout();

static int g_ClickCount = 0;

static text_widget_ptr add_label(widget_ptr parent, const xstring& text, const Rect& rect)
{
  text_widget_ptr label = TextWidget::create(text);
  label->set_rect(rect);
  parent->add_child(label);
  return label;
}

/// Shows the different button types and the events they raise
void load_buttons_layout()
{
  widget_ptr desktop = OGUIManager::instance()->get_desktop();

  // Remove previous widgets
  OGUIManager::instance()->clear();

  fill_widget_ptr background = FillWidget::create();
  background->set_rect(desktop->get_rect());
  background->set_layout(layout_ptr());
  background->set_color(0xFF00AA00);
  background->set_gradient(fPoint(1.0f, 0.5f));

  add_label(background, "Buttons Demo", Rect(220, 20, 420, 50));

  // Status line at the bottom shows the last event received
  text_widget_ptr status = add_label(background, "Click something", Rect(40, 400, 600, 430));

  // Push button: raises "clicked"
  g_ClickCount = 0;
  text_push_button_widget_ptr push = TextPushButtonWidget::create("Click Me");
  push->set_rect(Rect(40, 80, 200, 110));
  text_widget_ptr counter = add_label(background, "Clicked 0 times", Rect(220, 80, 440, 110));
  push->add_listener("demo", "clicked", [counter, status](const xstring& name, const xstring& event_type, const xstring& param)
  {
    ++g_ClickCount;
    counter->set_text("Clicked " + S(g_ClickCount) + " times");
    status->set_text("Push button clicked");
  });
  background->add_child(push);

  // Checkboxes: raise "toggled" with "down" or "up"
  const char* checkbox_names[] = { "Option A", "Option B" };
  for (int i = 0; i < 2; ++i)
  {
    xstring label = checkbox_names[i];
    int y = 140 + i * 40;
    checkbox_widget_ptr cb = CheckboxWidget::create();
    cb->set_rect(Rect(40, y, 70, y + 30));
    add_label(background, label, Rect(80, y, 240, y + 30));
    cb->add_listener("demo", "toggled", [status, label](const xstring& name, const xstring& event_type, const xstring& param)
    {
      status->set_text(label + (param == "down" ? " checked" : " unchecked"));
    });
    background->add_child(cb);
  }

  // Radio group: only one radio button can be down, the group raises "select" with the button's name
  radio_group_widget_ptr group = RadioGroupWidget::create();
  group->set_rect(Rect(320, 140, 600, 260));
  group->set_layout(layout_ptr());
  const char* sizes[] = { "Small", "Medium", "Large" };
  radio_button_widget_ptr radios[3];
  for (int i = 0; i < 3; ++i)
  {
    int y = i * 40;
    radios[i] = RadioButtonWidget::create();
    radios[i]->set_name(sizes[i]);
    radios[i]->set_rect(Rect(0, y, 30, y + 30));
    add_label(group, sizes[i], Rect(40, y, 200, y + 30));
    group->add_child(radios[i]);
  }
  radios[1]->set_button_down(true);
  group->add_listener("demo", "select", [status](const xstring& name, const xstring& event_type, const xstring& param)
  {
    xstring selected = param;
    int p = selected.find('#');
    if (p >= 0) selected = selected.substr(0, p);
    status->set_text("Size selected: " + selected);
  });
  background->add_child(group);

  text_push_button_widget_ptr back = TextPushButtonWidget::create("Back");
  back->set_rect(Rect(40, 330, 200, 360));
  back->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_demo_layout();
  });
  background->add_child(back);

  desktop->add_child(background);
}
