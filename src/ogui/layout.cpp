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

void GridLayout::arrange(Widget* widget)
{
  if (m_Columns<1) m_Columns=1;
  Point sp=widget->get_layout_spacing();
  float sum_weights = std::accumulate(m_Weights.begin(), m_Weights.end(), 0.0f);
  Rect r=widget->get_children_clip_region();
  int maxh=0,y=r.top,x=r.left,c=0;
  int total_width = r.get_width();
  //int dx=r.get_width()/m_Columns;
  for(auto& w : *widget) maxh=Max(maxh,w->get_minimum_size().y);
  int index = 0;
  auto wit = m_Weights.begin();
  for(auto& w : *widget)
  {
    float weight = *wit++;
    int dx = int((weight / sum_weights) * total_width);
    w->set_rect(Rect(x,y,x+dx,y+maxh));
    x+=dx+sp.x;
    if (++c==m_Columns)
    {
      c=0;
      x=r.left;
      y+=maxh+sp.y;
      wit = m_Weights.begin();
    }
    ++index;
  }
}

void GridLayout::set_columns_weights(const xstring& comma_delimited_weights)
{
  m_Weights.clear();
  xstring_tokenizer st(comma_delimited_weights, ",");
  for (const auto& t : st)
    m_Weights.push_back(float(t.as_double()));
  if (m_Weights.size() < m_Columns) m_Weights.resize(m_Columns, 1.0f);
}

Point GridLayout::get_minimum_size(const Widget* widget) const
{
  Point mx(0,0);
  Point size(0,0);
  int n=0;
  for(auto& w : *widget) 
  {
    ++n;
    Point mn=w->get_minimum_size();
    mx.x=Max(mx.x,mn.x);
    mx.y=Max(mx.y,mn.y);
  }
  int rows=(n+m_Columns-1)/m_Columns;
  Point sp = widget->get_layout_spacing();
  Point spacing((m_Columns - 1)*sp.x, (rows - 1)*sp.y);
  return spacing+Point(m_Columns*mx.x,rows*mx.y);
}

void HorizontalLayout::arrange(Widget* widget)
{
  Rect r=widget->get_children_clip_region();
  int total_width = r.get_width() - (widget->get_children_count() - 1)*widget->get_layout_spacing().x;
  int total_height=r.get_height();
  bool expanded=false;
  std::vector<float> weights;
  std::vector<int> widths;
  int n=0;
  for(auto& c : *widget)
  {
    ++n;
    weights.push_back(c->get_layout_weight());
    int lp=c->get_layout_preference().x;
    if (lp==LAYOUT_EXPAND)
    {
      widths.push_back(-1);
      expanded=true;
    }
    else
    {
      if (lp==LAYOUT_TIGHT) widths.push_back(c->get_minimum_size().x);
      else widths.push_back(lp);
    }
  }
  float total_weight=0;
  if (expanded)
  {
    for(int i=0;i<n;++i)
    {
      int w=widths[i];
      if (w!=-1) total_width-=w;
      else       total_weight+=weights[i];
    }
  }
  auto it=widget->begin();
  int x=r.left;
  int y=r.top;
  for(int i=0;i<n;++i,++it)
  {
    widget_ptr wp=*it;
    Point lp=wp->get_layout_preference();
    int h=Min(wp->get_minimum_size().y,total_height);
    if (lp.y>0) h=lp.y;
    if (lp.y==LAYOUT_EXPAND) h=total_height;
    int w=widths[i];
    if (w<0) w=int((weights[i]/total_weight)*total_width);

    int dx = 0, dy = 0;
    if (h < total_height)
    {
      Alignment a = wp->get_alignment();
      if (aligned(a, ALIGN_BOTTOM)) dy = total_height - h;
      if (aligned(a, ALIGN_VCENTER)) dy = (total_height - h) / 2;
    }
    wp->set_rect(Rect(x + dx, y + dy, x + w + dx, y + h + dy));
    x += w + widget->get_layout_spacing().x;
  }
}

Point HorizontalLayout::get_minimum_size(const Widget* widget) const
{
  Point res(0, 0);
  int n = 0;
  for(auto& w : *widget)
  {
    Point mn=w->get_minimum_size();
    res.y=Max(res.y,mn.y);
    res.x+=mn.x;
    ++n;
  }
  res.x += (n - 1)*(widget->get_layout_spacing()).x;
  res += 2 * widget->get_layout_margin();
  return res;
}

void VerticalLayout::arrange(Widget* widget)
{
  Rect r=widget->get_children_clip_region();
  int total_width=r.get_width();
  int total_height=r.get_height() - (widget->get_children_count()-1)*widget->get_layout_spacing().y;
  bool expanded=false;
  std::vector<float> weights;
  std::vector<int> heights;
  int n=0;
  for(auto& c : *widget)
  {
    ++n;
    weights.push_back(c->get_layout_weight());
    int lp=c->get_layout_preference().y;
    if (lp==LAYOUT_EXPAND)
    {
      heights.push_back(-1);
      expanded=true;
    }
    else
    {
      if (lp==LAYOUT_TIGHT) heights.push_back(c->get_minimum_size().y);
      else heights.push_back(lp);
    }
  }
  float total_weight=0;
  if (expanded)
  {
    for(int i=0;i<n;++i)
    {
      int h=heights[i];
      if (h!=-1) total_height-=h;
      else       total_weight+=weights[i];
    }
  }
  auto it=widget->begin();
  int x=r.left;
  int y=r.top;
  for(int i=0;i<n;++i,++it)
  {
    widget_ptr wp=*it;
    Point lp=wp->get_layout_preference();
    Point min_size=wp->get_minimum_size();
    int w=Min(min_size.x,total_width);
    if (lp.x>0) w=lp.x;
    if (lp.x==LAYOUT_EXPAND) w=total_width;
    int h=heights[i];
    if (h<0) h=int((weights[i]/total_weight)*total_height);
    if (h<min_size.y) h=min_size.y;
    int dx = 0, dy = 0;
    if (w < total_width)
    {
      Alignment a = wp->get_alignment();
      if (aligned(a,ALIGN_RIGHT)) dx = total_width - w;
      if (aligned(a, ALIGN_HCENTER)) dx = (total_width - w) / 2;
    }
    wp->set_rect(Rect(x+dx,y+dy,x+w+dx,y+h+dy));
    y+=h+widget->get_layout_spacing().y;
  }
}

Point VerticalLayout::get_minimum_size(const Widget* widget) const
{
  Point res(0, 0);
  int n = 0;
  for (auto& w : *widget)
  {
    Point mn=w->get_minimum_size();
    res.x=Max(res.x,mn.x);
    res.y+=mn.y;
    ++n;
  }
  res.y += (n - 1)*widget->get_layout_spacing().y;
  res += 2 * widget->get_layout_margin();
  return res;
}


} // namespace OGUI
