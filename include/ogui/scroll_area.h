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
#ifndef H_OGUI_SCROLL_AREA
#define H_OGUI_SCROLL_AREA

#include <ogui/scrollbar.h>

namespace OGUI {

class ScrollAreaWidget : public StaticWidget
{
  typedef StaticWidget super;
  widget_ptr m_VerticalScrollbar;
  widget_ptr m_HorizontalScrollbar;
  Point m_ScrollPosition;
  Point m_Range;
  Image m_FullArea;
protected:
  /** Override to apply virtual scroll position offset */
  virtual Point to_desktop_recurse(Point p) const
  {
    return super::to_desktop_recurse(p) - m_ScrollPosition;
  }
public:
  OGUI_DECLARE_WIDGET(ScrollAreaWidget);

  virtual Point get_minimum_size() const override 
  {
    if (!empty()) return (*begin())->get_minimum_size();
    return Point(1,1); 
  }

  virtual void set_vertical_scrollbar(widget_ptr s) 
  {
    if (m_VerticalScrollbar) m_VerticalScrollbar->remove_listener(get_name(),"scroll");
    m_VerticalScrollbar=s;
    m_VerticalScrollbar->add_listener(get_name(),"scroll",OGUI_EVENT_CALLBACK {
      int y=int(param.as_double() * m_Range.y);
      set_scroll_position(Point(m_ScrollPosition.x,y));
    });
  }

  virtual void set_scroll_position(const Point& pos)
  {
    if (m_ScrollPosition!=pos)
    {
      m_ScrollPosition=pos;
      invalidate();
    }
  }

  virtual Point get_children_offset() const override
  {
    return -m_ScrollPosition;
  }

  virtual bool draw(Image& target, const Rect& region) override
  {
    return super::draw(target,Rect());
  }

  virtual void redraw() override 
  {
    Image& target=get_redraw_target();
    target.fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL));
    Rect rect(0,0,0,0);
    for(auto& w : *this)
      rect.accumulate(w->get_rect());
    Point size=rect.bottom_right();
    Point range = size - target.get_size();
    m_Range = Point(Max(range.x, 0), Max(range.y, 0));
  }

  virtual Point from_desktop(Point p) const override
  {
    Point res = super::from_desktop(p);
    res += m_ScrollPosition;
    return res;
  }

  virtual void on_mouse_down(int button, const Point& pos) override
  {
    super::on_mouse_down(button,pos+m_ScrollPosition);
  }

  virtual void on_mouse_up(int button, const Point& pos) override
  {
    super::on_mouse_up(button,pos+m_ScrollPosition);
  }

  virtual void on_mouse_move(const Point& pos) override
  {
    super::on_mouse_move(pos+m_ScrollPosition);
  }

  virtual void on_mouse_drag(const Point& pos) override
  {
    super::on_mouse_drag(pos+m_ScrollPosition);
  }
};

typedef std::shared_ptr<ScrollAreaWidget> scroll_area_ptr;

} // namespace OGUI

#endif // H_OGUI_SCROLL_AREA

