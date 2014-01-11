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

void FillWidget::redraw()
{
  Image& target=get_redraw_target();
  byte color[4];
  color[0]=(m_Color>>16)&0xFF;
  color[1]=(m_Color>> 8)&0xFF;
  color[2]=(m_Color    )&0xFF;
  Rect rect=get_rect();
  fPoint pos(0,0);
  float dy=1.0f/rect.get_height();
  float dx=1.0f/rect.get_width();
  fRect grad;
  if (m_Gradient.x>=0) { grad.left=1; grad.right=1-m_Gradient.x;  }
  else                 { grad.left=1+m_Gradient.x;  grad.right=1; }
  if (m_Gradient.y>=0) { grad.top=1; grad.bottom=1-m_Gradient.y;  }
  else                 { grad.top=1+m_Gradient.y;  grad.bottom=1; }

  for(int y=0;y<rect.get_height();++y,pos.y+=dy)
  {
    byte* row=target.get_row(y);
    pos.x=0;
    for(int x=0;x<rect.get_width();++x,pos.x+=dx)
    {
      for(int i=0;i<3;++i)
        row[x*4+i]=byte(color[i]*(grad.left+grad.get_width()*pos.x)*(grad.top+grad.get_height()*pos.y));
      row[x*4+3]=255;
    }
  }
}

} // namespace OGUI