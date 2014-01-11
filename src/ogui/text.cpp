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
#include "stdafx.h"

namespace OGUI {

typedef std::vector<int> int_vec;
typedef std::vector<xstring> str_vec;

int_vec calculate_text_breaks(const xstring& text)
{
  int_vec breaks;
  auto it = text.begin();
  bool last = false;
  for (int i = 0; it != text.end(); ++it, ++i)
  {
    if (*it == ' ')
    {
      if (last) breaks.push_back(i);
      last = false;
    }
    else last = true;
  }
  return breaks;
}

void break_text_lines(font_ptr font, xstring text, int total_width, str_vec& lines)
{
  lines.clear();
  int_vec breaks = calculate_text_breaks(text);
  unsigned break_pos = 0;
  xstring cand = "";
  while (text.length() > 0 && break_pos<breaks.size())
  {
    xstring sub = text.substr(0, breaks[break_pos]);
    Rect bounds = font->get_bounds(sub);
    if (bounds.get_width() > total_width)
    {
      if (cand.empty()) return; // Not enough space for single word
      lines.push_back(cand);
      text = text.substr(breaks[break_pos - 1]);
      text.trim();
      breaks = calculate_text_breaks(text);
      break_pos = 0;
    }
    else
    {
      cand = text.substr(0, breaks[break_pos]);
      break_pos++;
    }
  }
  if (text.length() > 0) lines.push_back(text.trim());
}

void TextWidget::redraw()
{
  Image& target=get_redraw_target();
  target.fill(m_BGColor);
  Rect rect=get_rect();
  const xstring& text = get_text();
  str_vec lines(1, text);
  Rect bounds=m_Font->get_bounds(text);
  if (bounds.get_width() > rect.get_width())
  {
    break_text_lines(m_Font, text, rect.get_width(),lines);
    bounds = Rect(0, 0, 0, 0);
    for (auto& line : lines)
    {
      Rect b = m_Font->get_bounds(line);
      bounds.right = Max(bounds.right, b.get_width());
      bounds.bottom += b.get_height();
    }
  }
  Point d(rect.get_width()-bounds.get_width(),rect.get_height()-bounds.get_height());
  if ((get_alignment() & ALIGN_HCENTER)==ALIGN_HCENTER) bounds.offset(Point(d.x/2,0));
  else
  if ((get_alignment() & ALIGN_RIGHT)==ALIGN_RIGHT) bounds.offset(Point(d.x,0));

  if ((get_alignment() & ALIGN_VCENTER)==ALIGN_VCENTER) bounds.offset(Point(0,d.y/2));
  else
  if ((get_alignment() & ALIGN_BOTTOM)==ALIGN_BOTTOM) bounds.offset(Point(0,d.y));
  int x = bounds.left, y = bounds.top;
  for (auto& line : lines)
  {
    Rect line_bounds = m_Font->get_bounds(line);
    int dx = 0;
    if ((get_alignment() & ALIGN_HCENTER) == ALIGN_HCENTER) dx = (bounds.get_width() - line_bounds.get_width()) / 2;
    else
    if ((get_alignment() & ALIGN_RIGHT) == ALIGN_RIGHT) dx = (bounds.get_width() - line_bounds.get_width());
    m_Font->draw(target, Point(x + dx, y), line, m_Color);
    y += line_bounds.get_height();
  }
}

Point TextWidget::get_minimum_size() const
{
  return get_layout_margin()+m_Font->get_bounds(get_text()).get_size();
}

} // namespace OGUI
