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
#ifndef H_OGUI_IMAGE_CACHE
#define H_OGUI_IMAGE_CACHE

#include <ogui/rgba_image.h>
#include <unordered_map>

namespace OGUI {

  class ImageCache
  {
  public:
    static ImageCache* instance()
    {
      static std::unique_ptr<ImageCache> ptr(new ImageCache);
      return ptr.get();
    }

    typedef std::shared_ptr<Image> pointer;

    pointer load(const xstring& path)
    {
      auto it = m_Images.find(path);
      if (it != m_Images.end()) return it->second;
      m_Images[path] = load_new(path);
      return load(path);
    }

  private:
    virtual pointer load_new(const xstring& path)
    {
      return pointer(new Image(path));
    }

    friend struct std::default_delete<ImageCache>;
    ImageCache() {}
    ~ImageCache() {}
    ImageCache(const ImageCache&) {}
    ImageCache& operator= (const ImageCache&) { return *this; }

    std::unordered_map<xstring, pointer> m_Images;
  };



} // namespace OGUI

#endif // H_OGUI_IMAGE_CACHE

