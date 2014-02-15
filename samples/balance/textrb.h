#ifndef textrb_h__
#define textrb_h__

#include <ogui/button.h>

using namespace OGUI;

class TextRadioButton : public RadioButtonWidget
{
  text_widget_ptr m_Text;
protected:
  TextRadioButton(const xstring& text = "")
    : m_Text(TextWidget::create(text))
  {
    add_child(m_Text);
  }
public:
  OGUI_DECLARE_WIDGET(TextRadioButton);
  virtual void redraw() override
  {
    ButtonWidget::redraw();
  }
  virtual const xstring& get_text() const { return m_Text->get_text(); }
};

typedef std::shared_ptr<TextRadioButton> text_radio_widget_ptr;

class ButtonsGroup : public FrameWidget
{
  radio_group_widget_ptr m_Group;
protected:
  ButtonsGroup()
    : m_Group(RadioGroupWidget::create())
  {
    m_Group->set_layout(layout_ptr(new HorizontalLayout));
    add_child(m_Group);
    m_Group->add_listener("group", "select", OGUI_EVENT_CALLBACK
    {
      text_radio_widget_ptr button = std::static_pointer_cast<TextRadioButton>(m_Group->search(param));
      selection_changed(button->get_text());
    });
  }
public:
  OGUI_DECLARE_WIDGET(ButtonsGroup);

  void add_button(const xstring& text)
  {
    widget_ptr b = TextRadioButton::create(text);
    m_Group->add_child(b);
  }

  void selection_changed(const xstring& text)
  {
    raise_event("select", text);
  }
};

typedef std::shared_ptr<ButtonsGroup> buttons_group_ptr;


#endif // textrb_h__
