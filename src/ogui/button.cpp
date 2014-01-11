/***************************************************************************
Copyright (c) 2013, Amir Geva
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
#include "stdafx.h"

namespace OGUI {


  void RadioButtonWidget::redraw()
  {
    Image& target = get_redraw_target();
    target.fill(get_skin_color(SKIN_COLOR_DEFAULT_FILL));
    Rect rect = target.get_rect();
    bool marked = get_button_down();
    fPoint center(rect.get_width() *0.5f, rect.get_height() *0.5f);
    float radius = Min(center.x, center.y) - 6;
    for (int y = 0; y < rect.get_height(); ++y)
    {
      unsigned* row = target.get_urow(y);
      for (int x = 0; x < rect.get_width(); ++x)
      {
        float p = sqrt(sqr(x - center.x) + sqr(y - center.y));
        if (marked && p < (radius - 2.5f))
        {
          float m = (p - (radius - 3.0f));
          int shade = int(exp(m) * 100);
          row[x] = 0xFF000000 | (shade << 16) | (shade << 8) | shade;
        }
        else
        {
          float d = fabs(p - radius);
          if (d < 1.5f)
          {
            int shade = int(d * 64);
            row[x] = 0xFF000000 | (shade << 16) | (shade << 8) | shade;
          }
        }
      }
    }
  }


  void RadioGroupWidget::add_child(widget_ptr w)
  {
    StaticWidget::add_child(w);
    collect_descendants(w, "RadioButtonWidget", m_Buttons);
    for (auto& button : m_Buttons)
    {
      button->add_listener(get_name(), "toggled", [this, button](const xstring& name, const xstring& event_type, const xstring& param)
      {
        if (param == "down")
        {
          for (auto& cand : m_Buttons)
          {
            if (cand != button)
            {
              radio_button_widget_ptr other = std::static_pointer_cast<RadioButtonWidget>(cand);
              other->set_button_down(false);
            }
          }
        }
      });
    }
  }

} // namespace OGUI
