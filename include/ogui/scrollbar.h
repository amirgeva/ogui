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
#ifndef H_OGUI_SCROLLBAR
#define H_OGUI_SCROLLBAR

#include <ogui/ogui.h>

namespace OGUI {

class ScrollbarWidget;
typedef std::shared_ptr<ScrollbarWidget> scrollbar_widget_ptr;

class ScrollButtonWidget : public PushButtonWidget
{
  typedef PushButtonWidget super;
  ScrollbarWidget* m_Scrollbar;
  Point            m_DownPosition;
  Rect             m_DownRect;
  Orientation      m_Orientation;
protected:
  ScrollButtonWidget() : m_Scrollbar(0), m_Orientation(ORIENTATION_VERTICAL) {}
  friend class ScrollbarWidget;
public:
  OGUI_DECLARE_WIDGET(ScrollButtonWidget);

  virtual Point get_minimum_size() const override { return Point(16,16); }
  virtual Point get_layout_preference() const override { return Point(LAYOUT_TIGHT,LAYOUT_TIGHT); }

  virtual bool on_mouse_down(int button, const Point& pos) override;
  virtual bool on_mouse_up(int button, const Point& pos) override;
  virtual bool on_mouse_drag(const Point& pos) override;
};

typedef std::shared_ptr<ScrollButtonWidget> scroll_button_widget_ptr;

class ScrollbarWidget : public StaticWidget
{
  Orientation              m_Orientation;
  float                    m_Position;
  scroll_button_widget_ptr m_Button;
  int                      m_MovementRange;
protected:
  ScrollbarWidget()
  : m_Orientation(ORIENTATION_VERTICAL)
  , m_Position(0)
  , m_MovementRange(0)
  , m_Button(ScrollButtonWidget::create())
  {
    m_Button->m_Scrollbar=this;
    m_Button->m_Orientation=m_Orientation;
    set_layout(layout_ptr());
    add_child(m_Button);
  }
public:
  OGUI_DECLARE_WIDGET(ScrollbarWidget);

  virtual void set_orientation(const Orientation& o) 
  { 
    if (m_Orientation!=o)
    {
      m_Orientation=o;
      m_Button->m_Orientation=o;
      m_Button->invalidate();
      update_button_rect();
    }
  }

  virtual float get_position() const          { return m_Position; }

  virtual void update_position(float pos)
  {
    if (m_Position != pos)
    {
      m_Position = pos;
      raise_event("scroll", xstring(pos));
    }
  }

  virtual void set_position(const float& pos)        
  {
    m_Position = pos;
    update_button_rect();
  }

  virtual void set_rect(const Rect& r) override
  {
    bool update_button=(get_rect()!=r);
    StaticWidget::set_rect(r);
    if (update_button)
      update_button_rect();
  }

  virtual void update_button_rect()
  {
    Rect rect=get_rect();
    rect.move_to(Point(0,0));
    rect.inflate(-1);
    bool vert=(m_Orientation==ORIENTATION_VERTICAL);
    int size=vert?rect.get_height():rect.get_width();
    if (vert) rect.bottom=rect.top+m_Button->get_minimum_size().y;
    else      rect.right=rect.left+m_Button->get_minimum_size().x;
    int button_size=vert?rect.get_height():rect.get_width();
    m_MovementRange=(size-button_size);
    //std::cout << "Movement range=" << m_MovementRange << std::endl;
    int pos=int(m_Position*m_MovementRange+0.5f);
    Point ofs(0,0);
    if (vert) ofs.y=pos;
    else      ofs.x=pos;
    rect.offset(ofs);
    m_Button->set_rect(rect);
  }

  virtual int get_movement_range() const { return m_MovementRange; }

  virtual void redraw() override
  {
    Image& target=get_redraw_target();
    Rect rect=get_rect();
    draw_button(target,rect,false,get_skin_color(SKIN_COLOR_DEFAULT_FILL),get_skin_color(SKIN_COLOR_BUTTON_HILIGHT),get_skin_color(SKIN_COLOR_BUTTON_LOLIGHT));
  }

  virtual Rect get_children_clip_region() const override
  {
    Rect r=StaticWidget::get_children_clip_region();
    return r.inflate(-1);
  }

};

inline bool ScrollButtonWidget::on_mouse_down(int button, const Point& pos)
{
  m_DownPosition=pos+get_rect().top_left();
  m_DownRect=get_rect();
  return super::on_mouse_down(button,pos);
}

inline bool ScrollButtonWidget::on_mouse_up(int button, const Point& pos)
{
  Rect rect=get_rect();
  int rpos=(m_Orientation==ORIENTATION_VERTICAL)?rect.top:rect.left;
  float ratio=float(rpos)/m_Scrollbar->get_movement_range();
  m_Scrollbar->set_position(ratio);
  return super::on_mouse_up(button, pos);
}

inline bool ScrollButtonWidget::on_mouse_drag(const Point& pos)
{
  Point pofs=(pos+get_rect().top_left())-m_DownPosition;
  bool vert=(m_Orientation==ORIENTATION_VERTICAL);
  int ofs=vert?pofs.y:pofs.x;
  Rect rect=m_DownRect;
  int range=m_Scrollbar->get_movement_range();
  int new_pos=0;
  if (vert)
  {
    new_pos=rect.top+ofs;
    if (new_pos>range) new_pos=range;
    if (new_pos<0) new_pos=0;
    rect.top=new_pos;
    rect.bottom=rect.top+m_DownRect.get_height();
  }
  else
  {
    new_pos=rect.left+ofs;
    if (new_pos>range) new_pos=range;
    if (new_pos<0) new_pos=0;
    rect.left=new_pos;
    rect.right=rect.left+m_DownRect.get_width();
  }
  set_rect(rect);
  m_Scrollbar->update_position(float(new_pos)/range);
  return true;
}



} // namespace OGUI

#endif // H_OGUI_SCROLLBAR

