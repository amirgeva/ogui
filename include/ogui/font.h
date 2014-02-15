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
#ifndef H_OGUI_FONT
#define H_OGUI_FONT

#include <ogui/math2d.h>
#include <ogui/rgba_image.h>
#include <unordered_map>

namespace OGUI {

/** Font class, containing a pre-generated bitmap font
    Allows for rendering of text, and measuring its size
*/
class Font
{
  typedef std::vector<Rect> rects_vec;
  typedef std::vector<std::pair<Point,Rect>> placement_vec;
  Image     m_Image;
  char      m_FirstChar;
  int       m_TileSize;
  rects_vec m_Rects;


  void     build_rects();
  unsigned create_placement(const xstring& text, placement_vec& placement) const;
public:
  Font(Image image, char first_char, int tile_size) 
    : m_Image(image) 
    , m_FirstChar(first_char)
    , m_TileSize(tile_size)
  { 
    build_rects(); 
  }

  /** Draw the text on the target image, given the top left _offset_ and _color_ */
  void draw(Image& target, const Point& offset, const xstring& text, unsigned color) const;

  /** Returns a bounding rectangle for the given text.  
      Basically: `Rect(0,0,size.x,size.y)`
  */
  Rect  get_bounds(const xstring& text) const;

  /** Returns the area size needed to render this text */
  Point get_size(const xstring& text) const;

  /** Returns the non-cropped size of a single character */
  int  get_tile_size() const { return m_TileSize; }
};

typedef std::shared_ptr<Font> font_ptr;

/** Cache of fonts, to allow sharing pre-loaded fonts */
class FontCache
{
public:
  static FontCache* instance()
  {
    static std::unique_ptr<FontCache> ptr(new FontCache);
    return ptr.get();
  }

  /** Main use method.  Use as in the example:

      ```
      font_ptr font=FontCache::instance()->load("myfont.png");
      ```
  */
  font_ptr load(const xstring& name)
  {
    auto it = m_Fonts.find(name);
    if (it != m_Fonts.end()) return it->second;
    m_Fonts[name] = load_new(name);
    return load(name);
  }

private:
  font_ptr load_new(const xstring& name)
  {
    Image image(name);
    int tile_size = image.get_width() / 10;
    char first_char = ' ';
    return font_ptr(new Font(image, first_char, tile_size));
  }

  friend struct std::default_delete<FontCache>;
  FontCache() {}
  ~FontCache() {}
  FontCache(const FontCache&) {}
  FontCache& operator= (const FontCache&) { return *this; }

  std::unordered_map<xstring, font_ptr> m_Fonts;
};

} // namespace OGUI

#endif // H_OGUI_FONT


