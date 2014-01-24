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
#ifndef H_OGUI_IMAGE
#define H_OGUI_IMAGE

#include <ogui/ogui.h>
#include <ogui/image_cache.h>

namespace OGUI {

/** Widget that shows an image loaded from a file, as its visual appearance */
class ImageWidget : public StaticWidget
{
  image_ptr m_Image;
public:
  OGUI_DECLARE_WIDGET(ImageWidget);

  /** Override the last set image with an image from the given file */
  virtual void  set_image(const xstring& image_path) { m_Image = ImageCache::instance()->load(image_path); invalidate(); }

  /** Use a pre-loaded image, not necessarily from a file */
  virtual void  attach_image(image_ptr image) { m_Image = image; invalidate(); }

  virtual Point get_minimum_size() const override{ return m_Image->get_size(); }
  virtual Point get_layout_preference() const override{ return Point(LAYOUT_TIGHT,LAYOUT_TIGHT); }
  virtual void redraw() override
  {
    Image& target=get_redraw_target();
    target.paste(*m_Image);
  }
};

typedef std::shared_ptr<ImageWidget> image_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_IMAGE

