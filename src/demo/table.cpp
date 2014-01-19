#include <ogui/ogui.h>
#include <xml.h>

using namespace OGUI;

xstring root_dir = ROOTDIR;

widget_ptr g_BuyButton;
widget_ptr g_SellButton;
table_widget_ptr g_Table;
text_widget_ptr g_LastResult;

void load_demo_layout();

void display_result()
{
  create_text_query_dialog("You clicked Buy", DR_OK | DR_CANCEL, [](DialogResult res)
  {
    g_LastResult->set_text((res == DR_OK ? "OK" : "CANCEL"));
  });
}

void load_table_layout()
{
  // Remove previous widgets
  OGUIManager::instance()->clear();

  xml_element_ptr xml_root = load_xml_from_file(root_dir + "/data/table.xml");
  widget_ptr layout_root = load_layout_xml(xml_root);
  g_BuyButton = layout_root->search("buy");
  g_SellButton = layout_root->search("sell");
  g_BuyButton->enable(false);
  g_SellButton->enable(false);
  g_LastResult = std::static_pointer_cast<TextWidget>(layout_root->search("result"));

  g_BuyButton->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    display_result();
  });

  layout_root->search("back")->add_listener("demo", "clicked", OGUI_EVENT_CALLBACK_FUNC
  {
    load_demo_layout();
  });

  g_Table = std::static_pointer_cast<TableWidget>(layout_root->search("table"));
  for (int i = 0; i < 8; ++i)
  {
    g_Table->insert_row();
    g_Table->set_cell(i, 0, "Item #" + S(i));
    g_Table->set_cell(i, 1, "$" + S((i * 37) % 17));
    g_Table->set_cell(i, 2, S((i * 17) % 7));
    checkbox_widget_ptr cb = CheckboxWidget::create();
    if (i == 3) cb->set_button_down(true);
    g_Table->set_cell(i, 3, cb);
  }

  g_Table->add_listener("demo", "select", OGUI_EVENT_CALLBACK_FUNC
  {
    g_BuyButton->enable();
    g_SellButton->enable();
  });

  OGUIManager::instance()->get_desktop()->add_child(layout_root);
}

