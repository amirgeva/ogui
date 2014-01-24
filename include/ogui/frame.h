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
#ifndef H_OGUI_FRAME
#define H_OGUI_FRAME

#include <ogui/ogui.h>

namespace OGUI {

/** A widget that has a border of _width_ thickness.
    Usually used to visually group other widgets together
*/
class FrameWidget : public StaticWidget
{
  unsigned m_Color;
  int      m_Width;
  unsigned m_BGColor;

  static float fabs(float f) { return (f<0.0f?-f:f); }
  unsigned build_color(const byte* rgb, float ratio)
  {
    unsigned color=0xFF000000;
    for(int i=0;i<3;++i)
      color |= (unsigned(rgb[i]*ratio))<<(8*(2-i));
    return color;
  }
protected:
  FrameWidget() 
  : m_Color(get_skin_color(SKIN_COLOR_FRAME))
  , m_Width(7) 
  {}
public:
  OGUI_DECLARE_WIDGET(FrameWidget);

  virtual void set_color(const unsigned& color) { INVALIDATING_ASSIGN(m_Color,color); }
  virtual void set_width(const unsigned& width) { INVALIDATING_ASSIGN(m_Width,width); }

  virtual Rect get_children_clip_region() const override
  {
    Rect r=StaticWidget::get_children_clip_region();
    return r.inflate(-int(m_Width));
  }

  virtual void redraw() override
  {
    Image& target=get_redraw_target();
    target.fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL));
    float w2=m_Width*0.5f;
    int w=target.get_width(),h=target.get_height();
    byte color[] = { byte((m_Color>>16)&0xFF), byte((m_Color>> 8)&0xFF), byte((m_Color)&0xFF) };
    for(int p=0;p<m_Width;++p)
    {
      float ratio=sqrt(1.0f-fabs((p-w2)/m_Width));
      unsigned cur_color=build_color(color,ratio);
      target.fill(Rect(p,p,w-p,p+1),cur_color);
      target.fill(Rect(p,h-p-1,w-p,h-p),cur_color);
      target.fill(Rect(p,p,p+1,h-p),cur_color);
      target.fill(Rect(w-p-1,p,w-p,h-p),cur_color);
    }
  }

  virtual Point get_minimum_size() const override
  {
    return Point(m_Width*2,m_Width*2)+StaticWidget::get_minimum_size();
  }
};

typedef std::shared_ptr<FrameWidget> frame_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_FRAME

