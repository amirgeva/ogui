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
#ifndef H_OGUI_LAYOUT
#define H_OGUI_LAYOUT

#include <memory>
#include <ogui/math2d.h>

namespace OGUI {

class Widget;

class Layout
{
public:
  virtual ~Layout() {}
  virtual void  arrange(Widget* widget) {}
  virtual Point get_minimum_size(const Widget* widget) const { return Point(1,1); }
};

class GridLayout : public Layout
{
  typedef std::vector<float> weight_seq;

  unsigned   m_Columns;
  weight_seq m_Weights;
protected:
  virtual void arrange(Widget* widget) override;
public:
  GridLayout(unsigned cols=1) : m_Columns(cols), m_Weights(cols,1) {}
  virtual void  set_columns_weights(const xstring& comma_delimited_weights);
  virtual Point get_minimum_size(const Widget* widget) const override;
};

typedef std::shared_ptr<GridLayout> grid_layout_ptr;

class HorizontalLayout : public Layout
{
protected:
  virtual void arrange(Widget* widget) override;
public:
  virtual Point get_minimum_size(const Widget* widget) const override;
};

class VerticalLayout : public Layout
{
protected:
  virtual void arrange(Widget* widget) override;
public:
  virtual Point get_minimum_size(const Widget* widget) const override;
};

typedef std::shared_ptr<Layout> layout_ptr;

} // namespace OGUI

#endif // H_OGUI_LAYOUT

