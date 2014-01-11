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
#ifndef H_OGUI_UTILITIES
#define H_OGUI_UTILITIES

namespace OGUI {

struct Color
{
  byte r,g,b,a;

  Color(unsigned c)
    : r((c    )&0xFF)
    , g((c>> 8)&0xFF)
    , b((c>>16)&0xFF)
    , a((c>>24)&0xFF)
  {}

  Color(byte R, byte G, byte B, byte A)
    : r(R), g(G), b(B), a(A) {}

  template<class T>
  explicit Color(T R, T G, T B, T A)
    : r(byte(R)), g(byte(G)), b(byte(B)), a(byte(A)) {}

  Color& gray()
  {
    unsigned sum = unsigned(r) + unsigned(g) + unsigned(b);
    sum /= 3;
    r = g = b = sum;
    return *this;
  }

  Color& brighten()
  {
    r = byte((unsigned(r) + 255) / 2);
    g = byte((unsigned(g) + 255) / 2);
    b = byte((unsigned(b) + 255) / 2);
    return *this;
  }

  unsigned compose() const
  {
    return (unsigned(a)<<24) | (unsigned(b)<<16) | (unsigned(g)<<8) | unsigned(r);
  }
};

struct fColor
{
  float r,g,b,a;
  fColor() : r(0), g(0), b(0), a(0) {}
  void add(const Color& c, float ratio)
  {
    r+=c.r*ratio;
    g+=c.g*ratio;
    b+=c.b*ratio;
    a+=c.a*ratio;
  }
  void add(unsigned c, float ratio)
  {
    add(Color(c),ratio);
  }
  void clamp()
  {
    r=Max(r,0.0f); r=Min(r,255.0f);
    g=Max(g,0.0f); g=Min(g,255.0f);
    b=Max(b,0.0f); b=Min(b,255.0f);
    a=Max(a,0.0f); a=Min(a,255.0f);
  }
  unsigned compose() const
  {
    Color c(r,g,b,a);
    return c.compose();
  }
};

inline unsigned brighten(unsigned color, float ratio)
{
  Color c(color);
  c.r=byte(c.r*(1.0f-ratio)+255*ratio);
  c.g=byte(c.g*(1.0f-ratio)+255*ratio);
  c.b=byte(c.b*(1.0f-ratio)+255*ratio);
  return c.compose();
}

} // namespace OGUI

#endif // H_OGUI_UTILITIES

