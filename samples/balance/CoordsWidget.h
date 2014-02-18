#ifndef CoordsWidget_h__
#define CoordsWidget_h__

#include <ogui/text.h>

using namespace OGUI;

class CoordinatesBackground : public StaticWidget
{
  text_widget_ptr m_Coords;

  struct Polygon
  {
    Polygon(unsigned c=0) : color(c) {}
    typedef std::vector<Point> pt_vec;
    pt_vec   points;
    unsigned color;
  };

  typedef std::vector<Polygon> poly_vec;
  poly_vec m_Polygons;
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

  virtual void redraw() override
  {
    StaticWidget::redraw();
    Image& target = get_redraw_target();
    int w = target.get_width(), h = target.get_height();
    unsigned color=OGUIManager::instance()->get_skin_color(SKIN_COLOR_DEFAULT_FILL);
    color=brighten(color, 0.1f);
    for (int y = 0; y < h; y += 5)
      draw_line(target, Point(0, y), Point(w, y), color);
    for (int x = 0; x < w; x += 5)
      draw_line(target, Point(x, 0), Point(x, h), color);
    for (auto& poly : m_Polygons)
    {
      int n = poly.points.size();
      for (int i = 0; i < n;++i)
      {
        int j = i + 1;
        if (j == n) j = 0;
        draw_line(target, poly.points[i], poly.points[j], poly.color);
      }
    }
  }

  virtual bool on_mouse_move(const Point& pos) override
  {
    xstring s = S("{},{}") << pos.x << pos.y;
    m_Coords->set_text(s);
    return StaticWidget::on_mouse_move(pos);
  }

//   virtual bool on_mouse_down(int button, const Point& pos) override
//   {
// 
//   }

  void start_polygon(unsigned color) { m_Polygons.push_back(Polygon(color)); }
  void add_polygon_point(const Point& p) { m_Polygons.back().points.push_back(p); invalidate(); }
};

typedef std::shared_ptr<CoordinatesBackground> coord_background_widget_ptr;

#endif // CoordsWidget_h__
