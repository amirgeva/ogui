/***************************************************************************
Copyright (c) 2013-2014, Amir Geva
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#ifndef H_OGUI_BUTTON
#define H_OGUI_BUTTON

namespace OGUI {

class ButtonWidget : public StaticWidget
{
  bool       m_Pressed;
protected:
  ButtonWidget() 
  : m_Pressed(false) 
  {}
public:
  OGUI_DECLARE_WIDGET(ButtonWidget);

  virtual Point get_children_offset() const override 
  { 
    int p=m_Pressed?1:0;
    return Point(p,p);
  }

  virtual Point get_minimum_size() const { return Point(2,2)+StaticWidget::get_minimum_size(); }

  virtual Rect get_children_clip_region() const override
  {
    Rect r=StaticWidget::get_children_clip_region();
    return r.inflate(-1);
  }

  virtual void redraw() override
  {
    Image& target=get_redraw_target();
    draw_button(target, get_rect(), m_Pressed, get_skin_color(SKIN_COLOR_DEFAULT_FILL), get_skin_color(SKIN_COLOR_BUTTON_HILIGHT), get_skin_color(SKIN_COLOR_BUTTON_LOLIGHT));
  }

  virtual void set_pressed(const bool& pressed) { INVALIDATING_ASSIGN(m_Pressed,pressed); }
  virtual bool get_pressed() const       { return m_Pressed; }
};

typedef std::shared_ptr<ButtonWidget> button_widget_ptr;

class PushButtonWidget : public ButtonWidget
{
public:
  OGUI_DECLARE_WIDGET(PushButtonWidget);

  virtual bool on_mouse_down(int button, const Point& pos) override
  {
    set_pressed(true);
    ButtonWidget::on_mouse_down(button,pos);
    OGUIManager::instance()->capture_mouse(this);
    return true;
  }

  virtual bool on_mouse_up(int button, const Point& pos) override
  {
    set_pressed(false);
    if (get_rect().point_inside(pos + get_rect().top_left()))
      raise_event("clicked");
    return true;
  }
};

typedef std::shared_ptr<PushButtonWidget> push_button_widget_ptr;

class TextPushButtonWidget : public PushButtonWidget
{
  text_widget_ptr m_TextWidget;
protected:
  TextPushButtonWidget(const xstring& text="")
  {
    m_TextWidget=TextWidget::create(text);
    add_child(m_TextWidget);
  }
public:
  OGUI_DECLARE_WIDGET(TextPushButtonWidget);

  virtual void set_color(unsigned color) { m_TextWidget->set_color(color); }
  virtual void set_text(const xstring& text) { m_TextWidget->set_text(text); }
};

typedef std::shared_ptr<TextPushButtonWidget> text_push_button_widget_ptr;

class ToggleButtonWidget : public ButtonWidget
{
protected:
  bool m_ButtonDown;
  ToggleButtonWidget() : m_ButtonDown(false) {}

  virtual bool button_clicked_state(bool old_state) const
  {
    return !old_state;
  }
public:
  OGUI_DECLARE_WIDGET(ToggleButtonWidget);

  bool get_button_down() const { return m_ButtonDown; }

  void set_button_down(bool state) 
  { 
    if (state != m_ButtonDown)
    {
      invalidate();
      m_ButtonDown = state;
      raise_event("toggled", (m_ButtonDown ? "down" : "up"));
    }
  }

  virtual bool on_mouse_down(int button, const Point& pos) override
  {
    set_pressed(true);
    ButtonWidget::on_mouse_down(button, pos);
    OGUIManager::instance()->capture_mouse(this);
    return true;
  }

  virtual bool on_mouse_up(int button, const Point& pos) override
  {
    if (get_rect().point_inside(pos+get_rect().top_left()))
    {
      bool new_state=button_clicked_state(m_ButtonDown);
      set_button_down(new_state);
    }
    set_pressed(m_ButtonDown);
    return true;
  }
};

typedef std::shared_ptr<ToggleButtonWidget> toggle_button_widget_ptr;

class CheckboxWidget : public ToggleButtonWidget
{
public:
  OGUI_DECLARE_WIDGET(CheckboxWidget);

  virtual void redraw() override
  {
    ToggleButtonWidget::redraw();
    if (get_button_down())
    {
      unsigned mark_color=get_skin_color(SKIN_COLOR_CHECK_COLOR);
      unsigned shadow_color=brighten(mark_color,0.6f);
      Image& target=get_redraw_target();
      Rect rect=get_rect();
      rect.move_to(Point(0,0));
      rect.inflate(-4);
      int n=Min(rect.get_width(),rect.get_height());
      int t=3;
      int iy=0;
      for(int y=rect.top;y<rect.bottom;++y,++iy)
      {
        unsigned* row=target.get_urow(y);
        int ix=0;
        for(int x=rect.left;x<rect.right;++x,++ix)
        {
          if (abs(ix-iy)<t) row[x]=mark_color;
          if (abs(n-1-ix-iy)<t) row[x]=mark_color;
        }
      }
      rect.inflate(2);
      const float f=1.0f/9.0f;
      const float coef[] = {f,f,f,f,f,f,f,f,f};
      filter(target,rect,(const float*)coef);
    }
  }
};

typedef std::shared_ptr<CheckboxWidget> checkbox_widget_ptr;

class RadioButtonWidget : public ToggleButtonWidget
{
protected:
  virtual bool button_clicked_state(bool old_state) const override { return true; }
public:
  OGUI_DECLARE_WIDGET(RadioButtonWidget);

  virtual void redraw() override;
};

typedef std::shared_ptr<RadioButtonWidget> radio_button_widget_ptr;

class RadioGroupWidget : public StaticWidget
{
  widgets_vec m_Buttons;
public:
  OGUI_DECLARE_WIDGET(RadioGroupWidget);

  virtual void add_child(widget_ptr w) override;
};

typedef std::shared_ptr<RadioGroupWidget> radio_group_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_BUTTON

