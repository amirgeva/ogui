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
#ifndef H_OGUI_FILL
#define H_OGUI_FILL

#include <ogui/static_widget.h>

namespace OGUI {

class FillWidget : public StaticWidget
{
  unsigned m_Color;
  fPoint   m_Gradient;
protected:
  FillWidget() 
  : m_Color(get_skin_color(SKIN_COLOR_DEFAULT_FILL))
  , m_Gradient(0,0) 
  {}
public:
  OGUI_DECLARE_WIDGET(FillWidget);

  virtual void  set_color(const unsigned& color) { INVALIDATING_ASSIGN(m_Color,color); }
  virtual void  set_gradient(const fPoint& gradient) { INVALIDATING_ASSIGN(m_Gradient,gradient); }

  virtual Point get_minimum_size() const override 
  { 
    return StaticWidget::get_minimum_size();
  }

  virtual void redraw() override;
};

typedef std::shared_ptr<FillWidget> fill_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_FILL

