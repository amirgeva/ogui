#ifndef scene_h__
#define scene_h__

#include "CoordsWidget.h"

class Scene
{
  typedef std::vector<Point> pt_vec;
  coord_background_widget_ptr m_CoordsWidget;
  xstring m_Mode;
  pt_vec  m_WingPoints;

  void set_mode(const xstring& mode)
  {
    m_Mode = mode;
  }

  void clicked(const Point& p);

  int m5(int i) const { return 5 * (i / 5); }

  Point pixel_to_mm(const Point& p)
  {
    return Point(m5(p.x), m5(p.y));
  }


public:
  void load(int width, int height);
};

#endif // scene_h__
