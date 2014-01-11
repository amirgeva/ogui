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
class RadioGroupWidgetGenerator : public TWidgetGenerator<RadioGroupWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") set_value(widget,&RadioGroupWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&RadioGroupWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&RadioGroupWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&RadioGroupWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&RadioGroupWidget::set_alignment,value);
      if (name=="name") set_value(widget,&RadioGroupWidget::set_name,value);
      if (name=="rect") set_value(widget,&RadioGroupWidget::set_rect,value);
    }
    return widget;
  }
};

class ButtonWidgetGenerator : public TWidgetGenerator<ButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&ButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&ButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&ButtonWidget::set_rect,value);
    }
    return widget;
  }
};

class WidgetGenerator : public TWidgetGenerator<Widget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") set_value(widget,&Widget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&Widget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&Widget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&Widget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&Widget::set_alignment,value);
      if (name=="name") set_value(widget,&Widget::set_name,value);
      if (name=="rect") set_value(widget,&Widget::set_rect,value);
    }
    return widget;
  }
};

class FrameWidgetGenerator : public TWidgetGenerator<FrameWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="color") set_value(widget,&FrameWidget::set_color,value);
      if (name=="width") set_value(widget,&FrameWidget::set_width,value);
      if (name=="layout_weight") set_value(widget,&FrameWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&FrameWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&FrameWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&FrameWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&FrameWidget::set_alignment,value);
      if (name=="name") set_value(widget,&FrameWidget::set_name,value);
      if (name=="rect") set_value(widget,&FrameWidget::set_rect,value);
    }
    return widget;
  }
};

class ScrollbarWidgetGenerator : public TWidgetGenerator<ScrollbarWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="orientation") set_value(widget,&ScrollbarWidget::set_orientation,value);
      if (name=="position") set_value(widget,&ScrollbarWidget::set_position,value);
      if (name=="rect") set_value(widget,&ScrollbarWidget::set_rect,value);
      if (name=="layout_weight") set_value(widget,&ScrollbarWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ScrollbarWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ScrollbarWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ScrollbarWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ScrollbarWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ScrollbarWidget::set_name,value);
      if (name=="rect") set_value(widget,&ScrollbarWidget::set_rect,value);
    }
    return widget;
  }
};

class ScrollAreaWidgetGenerator : public TWidgetGenerator<ScrollAreaWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="vertical_scrollbar") set_value(widget,&ScrollAreaWidget::set_vertical_scrollbar,value);
      if (name=="scroll_position") set_value(widget,&ScrollAreaWidget::set_scroll_position,value);
      if (name=="layout_weight") set_value(widget,&ScrollAreaWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ScrollAreaWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ScrollAreaWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ScrollAreaWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ScrollAreaWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ScrollAreaWidget::set_name,value);
      if (name=="rect") set_value(widget,&ScrollAreaWidget::set_rect,value);
    }
    return widget;
  }
};

class TextPushButtonWidgetGenerator : public TWidgetGenerator<TextPushButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="text") set_value(widget,&TextPushButtonWidget::set_text,value);
      if (name=="pressed") set_value(widget,&TextPushButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&TextPushButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&TextPushButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&TextPushButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&TextPushButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&TextPushButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&TextPushButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&TextPushButtonWidget::set_rect,value);
    }
    return widget;
  }
};

class CheckboxWidgetGenerator : public TWidgetGenerator<CheckboxWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&CheckboxWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&CheckboxWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&CheckboxWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&CheckboxWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&CheckboxWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&CheckboxWidget::set_alignment,value);
      if (name=="name") set_value(widget,&CheckboxWidget::set_name,value);
      if (name=="rect") set_value(widget,&CheckboxWidget::set_rect,value);
    }
    return widget;
  }
};

class TableWidgetGenerator : public TWidgetGenerator<TableWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="column_count") set_value(widget,&TableWidget::set_column_count,value);
      if (name=="header_bg_color") set_value(widget,&TableWidget::set_header_bg_color,value);
      if (name=="header_color") set_value(widget,&TableWidget::set_header_color,value);
      if (name=="column_names") set_value(widget,&TableWidget::set_column_names,value);
      if (name=="column_weights") set_value(widget,&TableWidget::set_column_weights,value);
      if (name=="layout_weight") set_value(widget,&TableWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&TableWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&TableWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&TableWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&TableWidget::set_alignment,value);
      if (name=="name") set_value(widget,&TableWidget::set_name,value);
      if (name=="rect") set_value(widget,&TableWidget::set_rect,value);
    }
    return widget;
  }
};

class ImageWidgetGenerator : public TWidgetGenerator<ImageWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="image") set_value(widget,&ImageWidget::set_image,value);
      if (name=="layout_weight") set_value(widget,&ImageWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ImageWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ImageWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ImageWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ImageWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ImageWidget::set_name,value);
      if (name=="rect") set_value(widget,&ImageWidget::set_rect,value);
    }
    return widget;
  }
};

class PushButtonWidgetGenerator : public TWidgetGenerator<PushButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&PushButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&PushButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&PushButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&PushButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&PushButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&PushButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&PushButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&PushButtonWidget::set_rect,value);
    }
    return widget;
  }
};

class ScrollButtonWidgetGenerator : public TWidgetGenerator<ScrollButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&ScrollButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&ScrollButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ScrollButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ScrollButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ScrollButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ScrollButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ScrollButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&ScrollButtonWidget::set_rect,value);
    }
    return widget;
  }
};

class RadioButtonWidgetGenerator : public TWidgetGenerator<RadioButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&RadioButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&RadioButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&RadioButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&RadioButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&RadioButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&RadioButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&RadioButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&RadioButtonWidget::set_rect,value);
    }
    return widget;
  }
};

class FillWidgetGenerator : public TWidgetGenerator<FillWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="color") set_value(widget,&FillWidget::set_color,value);
      if (name=="layout_weight") set_value(widget,&FillWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&FillWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&FillWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&FillWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&FillWidget::set_alignment,value);
      if (name=="name") set_value(widget,&FillWidget::set_name,value);
      if (name=="rect") set_value(widget,&FillWidget::set_rect,value);
    }
    return widget;
  }
};

class StaticWidgetGenerator : public TWidgetGenerator<StaticWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") set_value(widget,&StaticWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&StaticWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&StaticWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&StaticWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&StaticWidget::set_alignment,value);
      if (name=="name") set_value(widget,&StaticWidget::set_name,value);
      if (name=="rect") set_value(widget,&StaticWidget::set_rect,value);
    }
    return widget;
  }
};

class TextWidgetGenerator : public TWidgetGenerator<TextWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="blended_draw") set_value(widget,&TextWidget::set_blended_draw,value);
      if (name=="text") set_value(widget,&TextWidget::set_text,value);
      if (name=="font") set_value(widget,&TextWidget::set_font,value);
      if (name=="color") set_value(widget,&TextWidget::set_color,value);
      if (name=="bg_color") set_value(widget,&TextWidget::set_bg_color,value);
      if (name=="layout_weight") set_value(widget,&TextWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&TextWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&TextWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&TextWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&TextWidget::set_alignment,value);
      if (name=="name") set_value(widget,&TextWidget::set_name,value);
      if (name=="rect") set_value(widget,&TextWidget::set_rect,value);
    }
    return widget;
  }
};

class ToggleButtonWidgetGenerator : public TWidgetGenerator<ToggleButtonWidget>
{
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") set_value(widget,&ToggleButtonWidget::set_pressed,value);
      if (name=="layout_weight") set_value(widget,&ToggleButtonWidget::set_layout_weight,value);
      if (name=="layout_preference") set_value(widget,&ToggleButtonWidget::set_layout_preference,value);
      if (name=="layout_margin") set_value(widget,&ToggleButtonWidget::set_layout_margin,value);
      if (name=="layout_spacing") set_value(widget,&ToggleButtonWidget::set_layout_spacing,value);
      if (name=="alignment") set_value(widget,&ToggleButtonWidget::set_alignment,value);
      if (name=="name") set_value(widget,&ToggleButtonWidget::set_name,value);
      if (name=="rect") set_value(widget,&ToggleButtonWidget::set_rect,value);
    }
    return widget;
  }
};

inline widget_ptr widget_parse(xml_element_ptr el)
{
  if (el->get_type() == "RadioGroupWidget") return RadioGroupWidgetGenerator::parse(el);
  if (el->get_type() == "ButtonWidget") return ButtonWidgetGenerator::parse(el);
  if (el->get_type() == "Widget") return WidgetGenerator::parse(el);
  if (el->get_type() == "FrameWidget") return FrameWidgetGenerator::parse(el);
  if (el->get_type() == "ScrollbarWidget") return ScrollbarWidgetGenerator::parse(el);
  if (el->get_type() == "ScrollAreaWidget") return ScrollAreaWidgetGenerator::parse(el);
  if (el->get_type() == "TextPushButtonWidget") return TextPushButtonWidgetGenerator::parse(el);
  if (el->get_type() == "CheckboxWidget") return CheckboxWidgetGenerator::parse(el);
  if (el->get_type() == "TableWidget") return TableWidgetGenerator::parse(el);
  if (el->get_type() == "ImageWidget") return ImageWidgetGenerator::parse(el);
  if (el->get_type() == "PushButtonWidget") return PushButtonWidgetGenerator::parse(el);
  if (el->get_type() == "ScrollButtonWidget") return ScrollButtonWidgetGenerator::parse(el);
  if (el->get_type() == "RadioButtonWidget") return RadioButtonWidgetGenerator::parse(el);
  if (el->get_type() == "FillWidget") return FillWidgetGenerator::parse(el);
  if (el->get_type() == "StaticWidget") return StaticWidgetGenerator::parse(el);
  if (el->get_type() == "TextWidget") return TextWidgetGenerator::parse(el);
  if (el->get_type() == "ToggleButtonWidget") return ToggleButtonWidgetGenerator::parse(el);
  return widget_ptr();
}


