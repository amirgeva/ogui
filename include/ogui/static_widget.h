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
#ifndef H_OGUI_STATIC_WIDGET
#define H_OGUI_STATIC_WIDGET

#include <ogui/rgba_image.h>
#include <ogui/layout.h>
#include <ogui/widget.h>

namespace OGUI {

class StaticWidget : public Widget
{
  Image       m_DrawImage;
  layout_ptr  m_Layout;
  bool        m_Inverted;
protected:
  Image& get_redraw_target() 
  { 
    Rect rect=get_rect();
    if (m_DrawImage.get_size() != rect.get_size())
    {
      if (!rect.valid())
        throw xstring("Invalid static widget rect");
      m_DrawImage = Image(rect.get_size());
      m_DrawImage.fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL));
    }
    return m_DrawImage; 
  }
  virtual void arrange_layout();
  StaticWidget();
public:
  OGUI_DECLARE_WIDGET(StaticWidget);

  virtual void  set_layout(layout_ptr layout) { m_Layout=layout; }
  virtual Point get_minimum_size() const override;
  virtual bool  blended_draw() const { return false; }
  virtual void  redraw() { get_redraw_target().fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL)); }
  virtual bool  draw(Image& target, const Rect& region) override;
  virtual bool  inverted() const { return m_Inverted; }
  virtual void  set_inverted(bool state) { INVALIDATING_ASSIGN(m_Inverted, state); }
};

typedef std::shared_ptr<StaticWidget> static_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_STATIC_WIDGET

