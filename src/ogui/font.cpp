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

typedef unsigned char byte;


void Font::build_rects()
{
  unsigned rows=m_Image.get_height() / m_TileSize;
  unsigned cols=m_Image.get_width() / m_TileSize;
  for(unsigned row=0;row<rows;++row)
  {
    for(unsigned col=0;col<cols;++col)
    {
      Rect base_rect(col*m_TileSize,row*m_TileSize,(col+1)*m_TileSize,(row+1)*m_TileSize);
      Rect rect=base_rect;
      std::swap(rect.right,rect.left);
      for(int y=base_rect.top;y<base_rect.bottom;++y)
      {
        const byte* ptr=m_Image.get_row(y);
        for(int x=base_rect.left;x<base_rect.right;++x)
        {
          if (ptr[x*4+3]>31)
          {
            rect.left=Min(rect.left,x);
            rect.right=Max(rect.right,x+1);
          }
        }
      }
      if (!rect.valid())
      {
        rect.normalize();
        rect.right=rect.left+rect.get_width()/2;
      }
      m_Rects.push_back(rect);
    }
  }
}

unsigned Font::create_placement(const xstring& text, Font::placement_vec& placement) const
{
  int x=0;
  unsigned res=0;
  for(char c : text)
  {
    if (c<m_FirstChar) continue;
    unsigned index=(c-m_FirstChar);
    if (index>=m_Rects.size()) continue;
    Rect r=m_Rects[index];
    placement.push_back(std::make_pair(Point(x,0),r));
    x+=r.get_width()+1;
    res+=r.get_width()+1;
  }
  return res-1;
}

class ColorTransform : public Transform
{
  byte m_Color[4];
public:
  ColorTransform(unsigned color)
  {
    m_Color[0]=(color>>16)&0xFF;
    m_Color[1]=(color>> 8)&0xFF;
    m_Color[2]=(color    )&0xFF;
    m_Color[3]=255;
  }

  virtual byte transform(byte src, int channel) const override
  {
    return ((src*m_Color[channel])/255);
  }
};


void Font::draw(Image& target, const Point& offset, const xstring& text, unsigned color) const
{
  placement_vec placement;
  unsigned w=create_placement(text,placement);
  for(auto& pos : placement)
  {
    Point p=pos.first+offset;
    const Rect& src=pos.second;
    target.blend_channel(m_Image,src,p,ColorTransform(color));
  }
}

Rect Font::get_bounds(const xstring& text) const
{
  placement_vec placement;
  unsigned w=create_placement(text,placement);
  if (placement.empty()) return Rect();
  return Rect(0,0,w,placement.front().second.get_height());
}

} // namespace OGUI

