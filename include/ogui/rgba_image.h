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
#ifndef H_IMAGE_LIB_IMAGE
#define H_IMAGE_LIB_IMAGE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <ogui/math2d.h>

namespace OGUI {

typedef unsigned char byte;

class Transform
{
public:
  virtual ~Transform() {}
  virtual unsigned char transform(unsigned char src, int channel) const { return src; }
};


class Image
{
  typedef std::vector<byte> buffer_type;
  typedef std::shared_ptr<buffer_type> buffer_ptr;

  buffer_ptr m_Data;
  byte*      m_ExternalData;
  unsigned   m_Width;
  unsigned   m_Height;

  byte* get_image_buffer()
  {
    if (m_ExternalData) return m_ExternalData;
    buffer_type& v = *m_Data;
    return &v[0];
  }

  const byte* get_image_buffer() const
  {
    if (m_ExternalData) return m_ExternalData;
    const buffer_type& v = *m_Data;
    return &v[0];
  }

  bool prepare_copy(const Image& src, Rect& src_rect, Rect& dst_rect, const Point& dst_pt = Point(0, 0));

  void initialize(unsigned width, unsigned height)
  {
    m_Data=buffer_ptr(new buffer_type(width*height*4,255));
    m_Width=width;
    m_Height=height;
  }
  bool load_png(std::istream& is);
public:
  Image() : m_Width(0), m_Height(0), m_ExternalData(0) {}

  Image(unsigned width, unsigned height)
    : m_ExternalData(0)
  {
    initialize(width,height);
  }

  Image(const Point& size)
    : m_ExternalData(0)
  {
    initialize(size.x,size.y);
  }

  Image(unsigned width, unsigned height, byte* external)
    : m_ExternalData(external)
    , m_Width(width)
    , m_Height(height)
  {}

  Image(const std::string& png_path) 
    : m_ExternalData(0)
  {
    load_png(std::ifstream(png_path.c_str(), std::ios::in | std::ios::binary));
  }

  Image(std::istream& png_is) 
    : m_ExternalData(0)
  {
    load_png(png_is);
  }

  Image(const Image& image)
  : m_Data(image.m_Data)
  , m_ExternalData(image.m_ExternalData)
  , m_Width(image.m_Width)
  , m_Height(image.m_Height)
  {}

  ~Image(){}
  Image& operator= (const Image& image)
  {
    if (&image == this) return *this;
    m_Data=image.m_Data;
    m_ExternalData = image.m_ExternalData;
    m_Width=image.m_Width;
    m_Height=image.m_Height;
    return *this;
  }

  bool load_from_file(const char* path);
  bool save_to_file(const char* path);

  unsigned get_width()  const  { return m_Width; }
  unsigned get_height() const  { return m_Height; }
  Point    get_size()   const  { return Point(get_width(),get_height());    }
  Rect     get_rect()   const  { return Rect(0,0,get_width(),get_height()); }

  Image cut(Rect r);

  byte* get_row(unsigned y)
  {
    unsigned index=y*m_Width*4;
    byte* buffer = get_image_buffer();
    return &buffer[index];
  }

  const byte* get_row(unsigned y) const
  {
    unsigned index=y*m_Width*4;
    const byte* buffer = get_image_buffer();
    return &buffer[index];
  }

  unsigned* get_urow(unsigned y)
  {
    return reinterpret_cast<unsigned*>(get_row(y));
  }

  const unsigned* get_urow(unsigned y) const
  {
    return reinterpret_cast<const unsigned*>(get_row(y));
  }

  void invert()
  {
    for (unsigned y = 0; y < m_Height; ++y)
    {
      unsigned* row = get_urow(y);
      for (unsigned x = 0; x < m_Width; ++x)
      {
        row[x] = (row[x] & 0xFF000000) | (~row[x] & 0x00FFFFFF);
      }
    }
  }

  void fill(Rect rect, unsigned color);
  void fill(unsigned color) { fill(get_rect(),color); }

  void paste(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point());
  void blend_channel(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point(), const Transform& trans=Transform());
  void blend_constant(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point(), float src_alpha=1.0f, float dst_alpha=0.0f);
};


void filter(Image& image, const Rect& rect, const float* coef);
void draw_button(Image& target, const Rect& rect, bool sunk, unsigned bg_color, unsigned hilight, unsigned lolight);

} // namespace OGUI

#include <ogui/utilities.h>

#endif // H_IMAGE_LIB_IMAGE

