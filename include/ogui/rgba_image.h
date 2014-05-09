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

/** Platform independent 32bpp RGBA image class.  Used as a rendering target for OGUI widgets
    pixels can later be copied to a texture, or blitted to the screen
*/
class Image
{
  typedef std::vector<byte> buffer_type;
  typedef std::shared_ptr<buffer_type> buffer_ptr;

  buffer_ptr m_Data;
  byte*      m_ExternalData;
  unsigned   m_Width;
  unsigned   m_Height;
  bool       m_Modified;

  bool  owned_data() const { return !m_ExternalData; }

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
  /** Construct an empty image */
  Image() 
  : m_Width(0)
  , m_Height(0)
  , m_ExternalData(0)
  , m_Modified(false) 
  {}

  /** Construct an image of the given size */
  Image(unsigned width, unsigned height)
  : m_ExternalData(0)
  , m_Modified(false)
  {
    initialize(width,height);
  }

  /** Construct an image of the given size */
  Image(const Point& size)
  : m_ExternalData(0)
  , m_Modified(false)
  {
    initialize(size.x,size.y);
  }

  /** Construct an image of the given size, and attach an external (not-owned) pixel buffer */
  Image(unsigned width, unsigned height, byte* external)
  : m_ExternalData(external)
  , m_Width(width)
  , m_Height(height)
  , m_Modified(false)
  {}

  /** Load image from a PNG file */
  Image(const std::string& png_path) 
  : m_ExternalData(0)
  , m_Modified(false)
  {
    std::ifstream f(png_path.c_str(), std::ios::in | std::ios::binary);
    load_png(f);
  }

  /** Load image from a PNG contained in the binary string */
  Image(std::istream& png_is)
  : m_ExternalData(0)
  , m_Modified(false)
  {
    load_png(png_is);
  }

  Image(const Image& image)
  : m_Data(image.m_Data)
  , m_ExternalData(image.m_ExternalData)
  , m_Width(image.m_Width)
  , m_Height(image.m_Height)
  , m_Modified(image.m_Modified)
  {}

  ~Image(){}

  Image& operator= (const Image& image)
  {
    if (&image == this) return *this;
    m_Data=image.m_Data;
    m_ExternalData = image.m_ExternalData;
    m_Width=image.m_Width;
    m_Height=image.m_Height;
    m_Modified = image.m_Modified;
    return *this;
  }

  /** Load from a PNG file */
  bool load_from_file(const char* path);

  /** Save to a PNG file */
  bool save_to_file(const char* path) const;

  unsigned get_width()  const  { return m_Width; }
  unsigned get_height() const  { return m_Height; }
  Point    get_size()   const  { return Point(get_width(),get_height());    }
  Rect     get_rect()   const  { return Rect(0,0,get_width(),get_height()); }

  /** Return a new image that is a subset of this image, given the bounding rectangle */
  Image cut(Rect r);

  /** Makes sure the pixel buffer of the image is not shared.  Make a copy if necessary */
  void sever()
  {
    if (owned_data() && !m_Data.unique())
    {
      buffer_ptr p = m_Data;
      m_Data = buffer_ptr(new buffer_type(*p));
    }
  }

  /** Modifying access to pixels.  Sets the modified flag */
  byte* get_row(unsigned y)
  {
    // Sever owned pixel buffer, if shared
    sever();
    m_Modified = true;
    unsigned index=y*m_Width*4;
    byte* buffer = get_image_buffer();
    return &buffer[index];
  }

  /** Read-only access to pixels.  Does not set the modified flag */
  const byte* get_row(unsigned y) const
  {
    unsigned index=y*m_Width*4;
    const byte* buffer = get_image_buffer();
    return &buffer[index];
  }

  /** Modifying access to pixels.  Sets the modified flag.  Returns a pointer to 32 bit elements. */
  unsigned* get_urow(unsigned y)
  {
    return reinterpret_cast<unsigned*>(get_row(y));
  }

  /** Read-only access to pixels.  Does not set the modified flag.  Returns a pointer to 32 bit elements.  */
  const unsigned* get_urow(unsigned y) const
  {
    return reinterpret_cast<const unsigned*>(get_row(y));
  }

  /** Invert (bitwise) all color channels, keeping the alpha channel the same */
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

  /** Returns true if the image pixel buffer was retrieved for writing */
  bool is_modified() const { return m_Modified; }

  /** Reset the modified flag.  Can be used to detect later modifications with the  is_modified() method */
  void reset_modified()    { m_Modified = false; }

  /** Fills a rectangle in the image with the given color */
  void fill(Rect rect, unsigned color);

  /** Fills the image with the given color */
  void fill(unsigned color) { fill(get_rect(), color); }

  /** Copies the source image, or part of it specified in src_rect, to this image at dst_pt position */
  void paste(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point());

  /** Similar to paste, but does alpha blending  SOURCE_ALPHA x SOURCE + (1-SOURCE_ALPHA) x DESTINATION 
      Provides an optional transformation of the source pixels, to be applied just before the blend
  */
  void blend_channel(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point(), const Transform& trans=Transform());

  /** Similar to paste, but does alpha blending  src_alpha x SOURCE + dst_alpha x DESTINATION */
  void blend_constant(const Image& src, Rect src_rect=Rect(), const Point& dst_pt=Point(), float src_alpha=1.0f, float dst_alpha=0.0f);
};

/** Apply a generic 3x3 window filter to the image, using the 9 coefficients in the:  coef 
    The default rect is for the entire image
*/
void filter(Image& image, const float* coef, Rect rect = Rect(0, 0, 0, 0));

/** Draw the 3D highlights for a button like pattern.  sunk indicates whether to flip the hilight and lolight
    colors, and create the visual effect of a pressed button.  Typical hilight is white, and lolight is black
*/
void draw_button(Image& target, const Rect& rect, bool sunk, unsigned bg_color, unsigned hilight, unsigned lolight);

/** Draw a simple line on the image, from point to point, using the given color
*/
void draw_line(Image& target, const Point& from, const Point& to, unsigned color);

typedef std::shared_ptr<Image> image_ptr;

} // namespace OGUI

#include <ogui/utilities.h>

#endif // H_IMAGE_LIB_IMAGE

