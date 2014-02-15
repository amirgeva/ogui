#ifndef CoordsWidget_h__
#define CoordsWidget_h__

#include <ogui/text.h>

using namespace OGUI;

class CoordinatesBackground : public StaticWidget
{
  text_widget_ptr m_Coords;
protected:
  CoordinatesBackground()
  {
    set_layout(layout_ptr());
    m_Coords = TextWidget::create("0,0");
    m_Coords->set_layout_preference(Point(LAYOUT_TIGHT, LAYOUT_TIGHT));
    m_Coords->set_rect(Rect(0, 0, 100, 32));
    add_child(m_Coords);
  }
public:
  OGUI_DECLARE_WIDGET(CoordinatesBackground);

  virtual bool on_mouse_move(const Point& pos) override
  {
    xstring s = S("{},{}") << pos.x << pos.y;
    m_Coords->set_text(s);
    std::cout << "Setting coords to: " << s << std::endl;
    return StaticWidget::on_mouse_move(pos);
  }
};

typedef std::shared_ptr<CoordinatesBackground> coord_background_widget_ptr;

#endif // CoordsWidget_h__
