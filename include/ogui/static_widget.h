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

/** A blank canvas widget that is the concrete base class for the vast majority of widgets.
    It has an image that is filled during re-draws and during the recursive draws of its
    widget subtree.   Unless some widget in the subtree changes, this image can be used
    to draw this widget subtree with a simple blit.
*/
class StaticWidget : public Widget
{
  Image       m_DrawImage;
  layout_ptr  m_Layout;
  bool        m_Inverted;
protected:
  /** Allocate and return the draw image for this widget.  Must be called from redraw() */
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

  /** Set the layout policy for this widget, in order to arrange its children.
      The default layout is HorizontalLayout
      If no layout is needed, call  set_layout(layout_ptr())
  */
  virtual void  set_layout(layout_ptr layout) { m_Layout=layout; }
  virtual Point get_minimum_size() const override;

  /** Returns true if this widget should be drawn as alpha-blended (alpha channel), or false
      if it is to be copied as is. */
  virtual bool  blended_draw() const { return false; }

  /** Create the visual representation of the widget.  Overridden by derived class 
      The default look is blank fill with the default color
  */
  virtual void  redraw() { get_redraw_target().fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL)); }

  /** Draws the children onto this widget's image and then draws this image to the target */
  virtual bool  draw(Image& target, const Rect& region) override;

  /** Returns true if this widget's image should be inverted.  Useful for selection type scenarios */
  virtual bool  inverted() const { return m_Inverted; }

  /** Determine if this widget's image should be inverted.  Useful for selection type scenarios */
  virtual void  set_inverted(bool state) { INVALIDATING_ASSIGN(m_Inverted, state); }
};

typedef std::shared_ptr<StaticWidget> static_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_STATIC_WIDGET

