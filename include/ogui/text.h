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
#ifndef H_OGUI_TEXT
#define H_OGUI_TEXT

#include <ogui/static_widget.h>

namespace OGUI {

class TextWidget : public StaticWidget
{
  typedef StaticWidget super;
  unsigned    m_Color;
  xstring     m_Text;
  font_ptr    m_Font;
  unsigned    m_BGColor;
  bool        m_BlendedDraw;
protected:
  TextWidget(const xstring& text="", unsigned color=0) 
    : m_Font(OGUIManager::instance()->get_default_font())
    , m_BGColor(0)
    , m_Color(color)
    , m_Text(text)
    , m_BlendedDraw(true)
  {
    if (color == 0)
      m_Color = get_skin_color(SKIN_COLOR_TEXT);
  }
public:
  OGUI_DECLARE_WIDGET(TextWidget);

  /** Returns the minimum bounding box, by measuring the text size with the assigned font */
  virtual Point get_minimum_size() const override;

  /** Sets whether the text background should be copied or transparent 
      The default is blended draw, which does not copy the background
  */
  virtual void set_blended_draw(const bool& state) { INVALIDATING_ASSIGN(m_BlendedDraw,state);  }

  /** Sets the text to be displayed */
  virtual void set_text(const xstring& text) { INVALIDATING_ASSIGN(m_Text,text); }

  /** Returns the text to be displayed */
  virtual const xstring& get_text() const { return m_Text; }

  /** Override the default font with a specific one */
  virtual void set_font(const xstring& font_name) 
  { 
    m_Font=FontCache::instance()->load(font_name);
    invalidate();
  }

  /** Returns the color of the text */
  virtual unsigned get_color() const { return m_Color; }

  /** Set the color of the text */
  virtual void set_color(const unsigned& color) { INVALIDATING_ASSIGN(m_Color, color); }

  /** Returns the color of the text background */
  virtual unsigned get_bg_color() const { return m_BGColor; }

  /** Set the color of the text background */
  virtual void set_bg_color(const unsigned& color) { INVALIDATING_ASSIGN(m_BGColor, color); }

  /** Overridden method to render the text */
  virtual void redraw() override;

  virtual bool blended_draw() const override { return m_BlendedDraw; }
};

typedef std::shared_ptr<TextWidget> text_widget_ptr;

} // namespace OGUI


#endif // H_OGUI_TEXT
