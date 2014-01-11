#ifndef H_OGUI_TRANSPARENT
#define H_OGUI_TRANSPARENT

#include <ogui/static_widget.h>

namespace OGUI {

class TransparentWidget : public StaticWidget
{
public:
  virtual void redraw() override
  {
    Image& target=get_redraw_target();
    target.fill(0);
  }
};

} // namespace OGUI

#endif // H_OGUI_TRANSPARENT

