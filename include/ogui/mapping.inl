class RadioGroupWidgetGenerator : public TWidgetGenerator<RadioGroupWidget>
{
  typedef TWidgetGenerator<RadioGroupWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ButtonWidgetGenerator : public TWidgetGenerator<ButtonWidget>
{
  typedef TWidgetGenerator<ButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class WidgetGenerator : public TWidgetGenerator<Widget>
{
  typedef TWidgetGenerator<Widget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class FrameWidgetGenerator : public TWidgetGenerator<FrameWidget>
{
  typedef TWidgetGenerator<FrameWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="color") widget->set_color(parse_unsigned(value));
      if (name=="width") widget->set_width(parse_unsigned(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ScrollbarWidgetGenerator : public TWidgetGenerator<ScrollbarWidget>
{
  typedef TWidgetGenerator<ScrollbarWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="orientation") widget->set_orientation(parse_Orientation(value));
      if (name=="position") widget->set_position(parse_float(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ScrollAreaWidgetGenerator : public TWidgetGenerator<ScrollAreaWidget>
{
  typedef TWidgetGenerator<ScrollAreaWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="vertical_scrollbar") super::set_value(widget,&ScrollAreaWidget::set_vertical_scrollbar,value);
      if (name=="scroll_position") widget->set_scroll_position(parse_Point(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class TextPushButtonWidgetGenerator : public TWidgetGenerator<TextPushButtonWidget>
{
  typedef TWidgetGenerator<TextPushButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="text") widget->set_text(parse_xstring(value));
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class CheckboxWidgetGenerator : public TWidgetGenerator<CheckboxWidget>
{
  typedef TWidgetGenerator<CheckboxWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class TableWidgetGenerator : public TWidgetGenerator<TableWidget>
{
  typedef TWidgetGenerator<TableWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="column_count") widget->set_column_count(parse_int(value));
      if (name=="header_bg_color") widget->set_header_bg_color(parse_unsigned(value));
      if (name=="header_color") widget->set_header_color(parse_unsigned(value));
      if (name=="column_names") widget->set_column_names(parse_xstring(value));
      if (name=="column_weights") widget->set_column_weights(parse_xstring(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ImageWidgetGenerator : public TWidgetGenerator<ImageWidget>
{
  typedef TWidgetGenerator<ImageWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="image") widget->set_image(parse_xstring(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class PushButtonWidgetGenerator : public TWidgetGenerator<PushButtonWidget>
{
  typedef TWidgetGenerator<PushButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ScrollButtonWidgetGenerator : public TWidgetGenerator<ScrollButtonWidget>
{
  typedef TWidgetGenerator<ScrollButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class RadioButtonWidgetGenerator : public TWidgetGenerator<RadioButtonWidget>
{
  typedef TWidgetGenerator<RadioButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class FillWidgetGenerator : public TWidgetGenerator<FillWidget>
{
  typedef TWidgetGenerator<FillWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="color") widget->set_color(parse_unsigned(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class StaticWidgetGenerator : public TWidgetGenerator<StaticWidget>
{
  typedef TWidgetGenerator<StaticWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class TextWidgetGenerator : public TWidgetGenerator<TextWidget>
{
  typedef TWidgetGenerator<TextWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="blended_draw") widget->set_blended_draw(parse_bool(value));
      if (name=="text") widget->set_text(parse_xstring(value));
      if (name=="font") widget->set_font(parse_xstring(value));
      if (name=="color") widget->set_color(parse_unsigned(value));
      if (name=="bg_color") widget->set_bg_color(parse_unsigned(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
    }
    return widget;
  }
};

class ToggleButtonWidgetGenerator : public TWidgetGenerator<ToggleButtonWidget>
{
  typedef TWidgetGenerator<ToggleButtonWidget> super;
public:
  static pointer parse(xml_element_ptr el)
  {
    pointer widget=create();
    for(auto it=el->attr_begin();it!=el->attr_end();++it)
    {
      xstring name=it->first;
      xstring value=it->second;
      if (name=="pressed") widget->set_pressed(parse_bool(value));
      if (name=="layout_weight") widget->set_layout_weight(parse_float(value));
      if (name=="layout_preference") widget->set_layout_preference(parse_Point(value));
      if (name=="layout_margin") widget->set_layout_margin(parse_Point(value));
      if (name=="layout_spacing") widget->set_layout_spacing(parse_Point(value));
      if (name=="alignment") widget->set_alignment(parse_Alignment(value));
      if (name=="name") widget->set_name(parse_xstring(value));
      if (name=="rect") widget->set_rect(parse_Rect(value));
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


