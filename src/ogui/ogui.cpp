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
#include "def_font.h"

namespace MLG {
  int get_screen_width();
  int get_screen_height();
}

namespace OGUI {

xstring Widget::generate_unique_name()
{
  static int id = 0;
  return xstring(++id);
}

Point Widget::get_minimum_size() const 
{ 
  return Point(1,1); 
}

bool Widget::draw(Image& target, const Rect& region) 
{
  bool rc=false;
  for(auto& c : m_Children)
  {
    Rect rect=c->get_rect();
    rect.intersect(region);
    rc|=c->draw(target,rect);
  }
  if (m_ForceMofified)
  {
    m_ForceMofified = false;
    rc = true;
  }
  return rc;
}

void Widget::set_parent(Widget* p)
{
  m_Parent = p;
}


widget_ptr Widget::find_leaf_widget(const Point& pos)
{
  for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it)
  {
    auto& c = *it;
    if (!c->enabled()) continue;
    const Rect& r = c->get_rect();
    if (r.point_inside(pos))
    {
      widget_ptr res = c->find_leaf_widget(pos - r.top_left());
      if (!res) return c;
      return    res;
    }
  }
  return widget_ptr();
}

bool Widget::on_mouse_down(int button, const Point& pos) 
{
  bool child_found = false;
  for(auto it=m_Children.rbegin();it!=m_Children.rend();++it)
  {
    auto& c=*it;
    if (!c->enabled()) continue;
    const Rect& r=c->get_rect();
    if (r.point_inside(pos))
    {
      child_found = true;
      if (c->on_mouse_down(button, pos - r.top_left())) return true;
    }
  }
  if (!child_found)
  {
    OGUIManager::instance()->capture_mouse(this);
    raise_event("mouse_down",S(pos));
    return true;
  }
  return false;
}

bool Widget::on_mouse_up(int button, const Point& pos)
{
  Rect r = get_rect();
  r.move_to(Point(0, 0));
  if (r.point_inside(pos))
  {
    raise_event("clicked",S(pos));
    return true;
  }
  return false;
}

bool Widget::on_mouse_move(const Point& pos)
{
  raise_event("mouse_move", S(pos));
  return true;
}

bool Widget::on_mouse_drag(const Point& pos)
{
  raise_event("mouse_drag", S(pos));
  return true;
}

bool Widget::on_mouse_enter(const Point& pos)
{
  raise_event("mouse_enter", S(pos));
  return true;
}

bool Widget::on_mouse_leave(const Point& pos)
{
  raise_event("mouse_leave", S(pos));
  return true;
}




void transform_disabled(Image& image)
{
  unsigned w = image.get_width(), h = image.get_height();
  for (unsigned y = 0; y < h; ++y)
  {
    unsigned* row = image.get_urow(y);
    for (unsigned x = 0; x < w; ++x)
    {
      Color c(row[x]);
      row[x] = c.gray().brighten().compose();
    }
  }
}

StaticWidget::StaticWidget()
: m_Layout(new HorizontalLayout)
, m_Inverted(false)
{}

void StaticWidget::arrange_layout()
{
  if (!valid() && m_Layout && !empty())
    m_Layout->arrange(this);
}

bool StaticWidget::draw(Image& target, const Rect& region)
{
  bool rc=false;
  Rect local_region=region;
  local_region.offset(-get_rect().top_left());
  arrange_layout();
  if (!valid())
  {
    Rect desktop_rect=to_desktop(get_rect());
    redraw();
    validate();
    Rect children_local_region=local_region;
    children_local_region.intersect(get_children_clip_region());
    Widget::draw(get_redraw_target(),children_local_region);
    rc=true;
    if (inverted()) get_redraw_target().invert();
    if (!enabled()) transform_disabled(get_redraw_target());
  }
  Rect rect=m_DrawImage.get_rect();
  //m_DrawImage.save_to_file("ogui_sub.png");
  Point offset(0,0);
  if (get_parent()) offset=get_parent()->get_children_offset();
  Point dst_pt=region.top_left();
  dst_pt+=offset;
  rect.intersect(local_region);
  if (blended_draw())
    target.blend_channel(m_DrawImage,rect,dst_pt);
  else 
    target.paste(m_DrawImage,rect,dst_pt);
  //target.save_to_file("ogui_target.png");
  return rc;
}

Point StaticWidget::get_minimum_size() const 
{ 
  if (m_Layout && !empty())
    return m_Layout->get_minimum_size(this);
  if (std::distance(begin(),end())==1)
  {
    widget_ptr w=*begin();
    return w->get_minimum_size();
  }
  Point pref=get_layout_preference();
  Point res=Point(1,1)+get_layout_margin(); 
  if (pref.x>0) res.x=pref.x;
  if (pref.y>0) res.y=pref.y;
  return res;
}



widget_ptr get_desktop() 
{ 
  return OGUIManager::instance()->get_desktop();
}

struct membuf: std::streambuf 
{
  membuf(const byte* buffer, size_t size) 
  {
    byte* bptr=const_cast<byte*>(buffer);
    char* ptr=reinterpret_cast<char*>(bptr);
    this->setg(ptr, ptr, ptr + size);
  }
};

struct imemstream: virtual membuf, public std::istream {
  imemstream(const byte* buffer, size_t size)
    : membuf(buffer, size)
    , std::istream(static_cast<std::streambuf*>(this)) {
  }
};

void OGUIManager::initialize_desktop(int width, int height)
{
  m_Desktop = Widget::create();
  m_Desktop->set_rect(Rect(0, 0, width, height));
}

widget_ptr OGUIManager::get_desktop()
{
  return m_Desktop;
}

void OGUIManager::load_default_skin()
{
  imemstream ms(default_font,sizeof(default_font));
  Image font_image(ms);
  int size=font_image.get_width()/10;
  m_Font=font_ptr(new Font(font_image,' ',size));

  m_SkinColors.push_back(skin_colors(SKIN_COLOR_LAST));
  skin_colors& sc = m_SkinColors.back();
  sc[SKIN_COLOR_DEFAULT_FILL]=0xFF808080;
  sc[SKIN_COLOR_FRAME] = 0xFFFF0000;
  sc[SKIN_COLOR_BUTTON_HILIGHT]=0xFFDDDDDD;
  sc[SKIN_COLOR_BUTTON_LOLIGHT]=0xFF222222;
  sc[SKIN_COLOR_CHECK_COLOR]=0xFF000000;
  sc[SKIN_COLOR_TABLE_HEADER_TEXT]=0xFFFFFFFF;
  sc[SKIN_COLOR_TABLE_HEADER_BG]=0xFFFF7777;
  sc[SKIN_COLOR_TEXT] = 0xFF000000;
}

void parse_xml_value(const xstring& xml_value, unsigned& value);
void OGUIManager::load_skin(std::istream& skin_is)
{
  xml_element_ptr root=load_xml_from_stream(skin_is);
  for (auto c : *root)
  {
    if (c->get_type() == "color")
    {
      xstring name = c->get_attribute("name");
      xstring value = c->get_attribute("value");
      SkinColors id=get_skin_color_id("SKIN_COLOR_" + name);
      if (id != SKIN_COLOR_LAST)
      {
        unsigned uval;
        parse_xml_value(value, uval);
        m_SkinColors.back()[id] = uval;
      }
    }
  }
}

void OGUIManager::clear()
{
  m_LastCursorLeafWidget = widget_ptr();
  m_Listeners.clear();
  get_desktop()->clear_children();
}

void OGUIManager::mouse_down(int button, int x, int y)
{
  widget_ptr& w = get_event_recipient();
  Point p = w->from_desktop(Point(x, y));
  w->on_mouse_down(button,p);
}

void OGUIManager::mouse_up(int button, int x, int y)
{
  if (m_MouseCapture) 
  {
    Point p=m_MouseCapture->from_desktop(Point(x,y));
    m_MouseCapture->on_mouse_up(button,p);
    m_MouseCapture=0;
  }
  else
  {
    widget_ptr& w = get_event_recipient();
    Point p = w->from_desktop(Point(x, y));
    w->on_mouse_up(button, p);
  }
}

void OGUIManager::mouse_move(int x, int y)
{
  if (m_MouseCapture) 
  {
    Point p=m_MouseCapture->from_desktop(Point(x,y));
    m_MouseCapture->on_mouse_move(p);
  }
  else
  {
    widget_ptr& w = get_event_recipient();
    Point global_pos(x, y);
    Point p = w->from_desktop(global_pos);
    widget_ptr leaf=w->find_leaf_widget(p);
    if (leaf)
    {
      p = leaf->from_desktop(global_pos);
      if (leaf != m_LastCursorLeafWidget)
      {
        if (m_LastCursorLeafWidget) m_LastCursorLeafWidget->on_mouse_leave(m_LastCursorLeafWidget->from_desktop(global_pos));
        leaf->on_mouse_enter(p);
        m_LastCursorLeafWidget = leaf;
      }
      else
      {
        leaf->on_mouse_move(p);
      }
    }
    else
      w->on_mouse_move(p);
  }
}

void OGUIManager::mouse_drag(int x, int y)
{
  if (m_MouseCapture) 
  {
    Point p=m_MouseCapture->from_desktop(Point(x,y));
    m_MouseCapture->on_mouse_drag(p);
  }
  else
  {
    widget_ptr& w = get_event_recipient();
    Point p = w->from_desktop(Point(x, y));
    w->on_mouse_drag(p);
  }
}

void OGUIManager::set_modal_widget(widget_ptr w)
{
  if (m_ModalWidget) { m_ModalWidget->remove(); }
  m_ModalWidget = w;
  if (w) get_desktop()->add_child(w);
}

xstring build_key(const xstring& name, const xstring& type)
{
  return name+"|"+type;
}

bool OGUIManager::add_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type, event_callback callback)
{
  auto& seq = m_Listeners[build_key(target_name, event_type)];
  for (auto& l : seq)
    if (l.name == listener_name) return false;
  seq.push_back(listener(listener_name,callback));
  return true;
}

bool OGUIManager::remove_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type)
{
  bool rc = false;
  if (target_name == "" || event_type == "")
  {
    for (auto& p : m_Listeners)
      rc|=remove_listener(listener_name, p.second);
  }
  else
  {
    auto it = m_Listeners.find(build_key(target_name, event_type));
    if (it != m_Listeners.end())
    {
      listener_seq& seq = it->second;
      rc|=remove_listener(listener_name, seq);
    }
  }
  return rc;
}

bool OGUIManager::remove_listener(const xstring& listener_name, listener_seq& seq)
{
  for (auto sit = seq.begin(); sit != seq.end(); ++sit)
  {
    if (sit->name == listener_name)
    {
      seq.erase(sit);
      return true;
    }
  }
  return false;
}


void OGUIManager::raise_event(const xstring& name, const xstring& type, const xstring& params)
{
  xstring key=name+"|"+type;
  auto it=m_Listeners.find(key);
  if (it!=m_Listeners.end())
  {
    // Copy of sequence is intentional.  GUI changes often clear listeners during the next loop
    listener_seq seq=it->second;
    for(auto& l : seq)
    {
      l.callback(name,type,params);
    }
  }
}

void OGUIManager::set_skin_color(SkinColors which, unsigned value)
{
  (m_SkinColors.back())[which] = value;
}

unsigned OGUIManager::get_skin_color(SkinColors which)
{ 
  return (m_SkinColors.back())[which]; 
}

void OGUIManager::push_color_state()
{
  m_SkinColors.push_back(m_SkinColors.back());
}

void OGUIManager::pop_color_state()
{
  if (m_SkinColors.size() > 1)
    m_SkinColors.pop_back();
}

namespace ColorNameMapping {

  struct SkinColorName
  {
    const char* name;
    SkinColors  id;
  };

  static const SkinColorName skin_color_names[] = {
  #include <ogui/skin_colors.inl>
  };

}

SkinColors get_skin_color_id(const xstring& name)
{
  const int n = sizeof(ColorNameMapping::skin_color_names) / sizeof(ColorNameMapping::SkinColorName);
  for (int i = 0; i < n; ++i)
  {
    if (name == ColorNameMapping::skin_color_names[i].name)
      return ColorNameMapping::skin_color_names[i].id;
  }
  return SKIN_COLOR_LAST;
}

struct StdButton
{
  const char* text;
  const char* name;
  const DialogResult res;
};

static const StdButton std_buttons[] = {
  { "Ok",     "ok",     DR_OK     },
  { "Cancel", "cancel", DR_CANCEL },
  { "Yes",    "yes",    DR_YES    },
  { "No",     "no",     DR_NO     }
};

modal_widget_ptr create_text_query_dialog(const xstring& query, unsigned possible_results, ModalWidget::modal_callback cb)
{
  frame_widget_ptr frame = FrameWidget::create();
  Rect rect = get_desktop()->get_rect();
  rect.inflate(-rect.get_width() / 4, -rect.get_height() / 4, -rect.get_width() / 4, -rect.get_height() / 4);
  frame->set_rect(rect);
  int sp = rect.get_height() / 12;
  frame->set_layout(layout_ptr(new VerticalLayout));
  frame->set_layout_spacing(Point(sp,sp));
  frame->set_layout_margin(Point(sp,sp));
  frame->add_child(TextWidget::create(query));
  widget_ptr button_bar = StaticWidget::create();
  button_bar->set_layout(layout_ptr(new HorizontalLayout));
  button_bar->set_layout_spacing(Point(sp, sp));
  button_bar->set_layout_weight(0.2f);
  int n_buttons = sizeof(std_buttons) / sizeof(StdButton);
  for (int i = 0; i < n_buttons; ++i)
  {
    if ((possible_results&std_buttons[i].res) != 0)
    {
      widget_ptr button = TextPushButtonWidget::create(std_buttons[i].text);
      button->set_name(std_buttons[i].name);
      button_bar->add_child(button);
    }
  }
  frame->add_child(button_bar);
  return ModalWidget::create(frame, cb);
}


} // OGUI
 