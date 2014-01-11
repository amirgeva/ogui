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
#ifndef H_OGUI_WIDGET
#define H_OGUI_WIDGET

#include <vector>
#include <memory>
#include <xstring.h>
#include <ogui/math2d.h>
#include <ogui/constants.h>
#include <ogui/layout.h>
#include <ogui/manager.h>

#define OGUI_DECLARE_WIDGET(name)\
virtual xstring get_type() const { return #name; }\
                           static std::shared_ptr<name> create()                       { return std::shared_ptr<name>(new name); }\
template<class A>          static std::shared_ptr<name> create(const A& a)             { return std::shared_ptr<name>(new name(a)); }\
template<class A, class B> static std::shared_ptr<name> create(const A& a, const B& b) { return std::shared_ptr<name>(new name(a, b)); }

//#define OGUI_INSTANTIATE(name) name::instantiate()
//#define OGUI_INSTANTIATE_1(name,p1) name::instantiate(p1)
#define INVALIDATING_ASSIGN(target,source) if (target!=source) invalidate(); target=source

namespace OGUI {

  typedef std::shared_ptr<class Widget> widget_ptr;

  class Widget
  {
  private:
    static xstring generate_unique_name();
    typedef std::vector<widget_ptr> widget_seq;

    Widget*                 m_Parent;
    xstring                 m_Name;
    Rect                    m_Rect;
    bool                    m_Enabled;
    bool                    m_Valid;
    bool                    m_ForceMofified;
    widget_seq              m_Children;
    Point                   m_LayoutPreference;
    Point                   m_LayoutMargin;
    Point                   m_LayoutSpacing;
    float                   m_LayoutWeight;
    Alignment               m_Alignment;
    skin_colors             m_ColorsOverride;

    bool same_name(const xstring& name) const
    {
      const xstring& my_name = get_name();
      if (my_name == name) return true;
      int p = my_name.find('#');
      if (p < 0) return false;
      return name == my_name.substr(0, p);
    }

    void update_search_name(const xstring& name)
    {
      int p = m_Name.find('#');
      if (p >= 0) m_Name = name + m_Name.substr(p);
      else        m_Name = name + "#" + m_Name;
    }

  protected:
    Widget() 
    : m_Enabled(true)
    , m_Valid(false)
    , m_ForceMofified(false)
    , m_Parent(0)
    , m_Name(generate_unique_name()) 
    , m_LayoutPreference(LAYOUT_EXPAND,LAYOUT_EXPAND)
    , m_LayoutWeight(1.0f)
    , m_LayoutMargin(0,0)
    , m_LayoutSpacing(0,0)
    , m_Alignment(ALIGN_CENTER)
    {}

    /** Recursive call for converting coordinates from local Widget space to desktop.  Called by to_desktop below.
        Overridden by scrolling widgets to provide offset for virtual space
    */
    virtual Point to_desktop_recurse(Point p) const
    {
      p += get_rect().top_left();
      if (m_Parent) return m_Parent->to_desktop_recurse(p);
      return p;
    }

  public:
    OGUI_DECLARE_WIDGET(Widget);
    virtual ~Widget() {}

    typedef widget_seq::iterator iterator;
    typedef widget_seq::const_iterator const_iterator;
    iterator       begin()       { return m_Children.begin(); }
    iterator       end()         { return m_Children.end();   }
    const_iterator begin() const { return m_Children.begin(); }
    const_iterator end()   const { return m_Children.end();   }
    bool           empty() const { return m_Children.empty(); }
    unsigned       size()  const { return m_Children.size();  }

    virtual unsigned         get_children_count() const { return m_Children.size(); }

    virtual void             add_child(widget_ptr w) 
    { 
      m_Children.push_back(w); 
      w->set_parent(this); 
      m_ForceMofified = true;
      invalidate();
    }

    virtual void             clear_children()        
    {
      for(auto& c : m_Children)
        c->set_parent(0);
      m_Children.clear();
      m_ForceMofified = true;
      invalidate();
    }

    virtual void             remove()
    {
      if (m_Parent) m_Parent->remove_child(this);
    }

    virtual void             remove_child(Widget* wp)
    {
      for(auto it=m_Children.begin();it!=m_Children.end();++it)
      {
        if (it->get() == wp)
        {
          m_Children.erase(it);
          m_ForceMofified = true;
          wp->set_parent(0);
          invalidate();
          break;
        }
      }
    }

    virtual Point            get_minimum_size() const;
    virtual float            get_layout_weight() const { return m_LayoutWeight; }
    virtual void             set_layout_weight(const float& weight) { INVALIDATING_ASSIGN(m_LayoutWeight,weight); }
    virtual Point            get_layout_preference() const { return m_LayoutPreference; }
    virtual void             set_layout_preference(const Point& lp) { INVALIDATING_ASSIGN(m_LayoutPreference,lp); }
    virtual Point            get_layout_margin() const { return m_LayoutMargin; }
    virtual void             set_layout_margin(const Point& lm) { INVALIDATING_ASSIGN(m_LayoutMargin,lm); }
    virtual Point            get_layout_spacing() const { return m_LayoutSpacing; }
    virtual void             set_layout_spacing(const Point& ls) { INVALIDATING_ASSIGN(m_LayoutSpacing, ls); }
    virtual Alignment        get_alignment() const { return m_Alignment; }
    virtual void             set_alignment(const Alignment& a) { INVALIDATING_ASSIGN(m_Alignment, a); }

    virtual void             set_parent(Widget* p) { m_Parent=p; }

    virtual void             enable(bool state=true) { INVALIDATING_ASSIGN(m_Enabled,state); }
    virtual void             disable() { enable(false); }
    virtual bool             enabled() { return m_Enabled; }

    virtual void             invalidate() { m_Valid=false; if (m_Parent) m_Parent->invalidate(); }
    virtual void             invalidate_children() { invalidate(); for(auto& c : m_Children) c->invalidate_children(); }
    virtual void             validate() { m_Valid=true; }
    virtual bool             valid() const { return m_Valid; }

    virtual void             set_name(const xstring& name) { update_search_name(name); }
    virtual const xstring&   get_name() const { return m_Name; }

    virtual void             set_rect(const Rect& r) { INVALIDATING_ASSIGN(m_Rect,r); }

    virtual const Rect&      get_rect() const { return m_Rect; }
    virtual Widget*          get_parent() { return m_Parent; }
    virtual const Widget*    get_parent() const { return m_Parent; }

    /** Convert point from desktop coordinates to local widget space */
    virtual Point            from_desktop(Point p) const
    {
      p-=get_rect().top_left();
      if (m_Parent) return m_Parent->from_desktop(p);
      return p;
    }

    /** Convert point from local widgets space to desktop coordinates */
    virtual Point            to_desktop(const Point& p) const
    {
      return to_desktop_recurse(p - get_rect().top_left());
    }

    virtual Rect             to_desktop(const Rect& r) const
    {
      return Rect(to_desktop(r.top_left()), to_desktop(r.bottom_right()));
    }

    // Placeholder for static widgets
    virtual void             set_layout(layout_ptr layout) {}

    virtual Rect             get_children_clip_region() const 
    { 
      Rect r=get_rect(); 
      r.move_to(Point(0,0)); 
      Point m=get_layout_margin();
      r.inflate(-m.x, -m.y, -m.x, -m.y);
      return r; 
    }

    virtual Point            get_children_offset() const { return Point(0,0); }

    /** Draws all children widgets
        Returns true if any modification was done (sub widget was invalidated) 
        region is the clip area in the target coordinate space
    */
    virtual bool             draw(Image& target, const Rect& region);

    virtual void             on_mouse_down(int button, const Point& pos);
    virtual void             on_mouse_up(int button, const Point& pos);
    virtual void             on_mouse_move(const Point& pos) {}
    virtual void             on_mouse_drag(const Point& pos) {}
    virtual void             on_mouse_enter(const Point& pos) {}
    virtual void             on_mouse_leave(const Point& pos) {}
    virtual void             on_char(unsigned short ch) {}

    virtual bool             add_listener(const xstring& receiver, const xstring& event_type, event_callback cb)
    {
      return OGUIManager::instance()->add_listener(receiver,get_name(),event_type,cb);
    }

    virtual bool             remove_listener(const xstring& receiver, const xstring& event_type)
    {
      return OGUIManager::instance()->remove_listener(receiver,get_name(),event_type);
    }

    virtual void             raise_event(const xstring& type, const xstring& params="")
    {
      OGUIManager::instance()->raise_event(get_name(),type,params);
    }

    virtual widget_ptr search(const xstring& name)
    {
      for(widget_ptr child : *this)
      {
        if (child->same_name(name)) return child;
        widget_ptr res=child->search(name);
        if (res) return res;
      }
      return widget_ptr();
    }

    virtual unsigned get_skin_color(SkinColors id)
    {
      if (!m_ColorsOverride.empty())
      {
        unsigned c = m_ColorsOverride[id];
        if (c) return c;
      }
      if (m_Parent) return m_Parent->get_skin_color(id);
      return OGUIManager::instance()->get_skin_color(id);
    }

    virtual void override_skin_color(SkinColors id, unsigned color)
    {
      if (m_ColorsOverride.empty()) m_ColorsOverride.assign(SKIN_COLOR_LAST,0);
      m_ColorsOverride[id] = color;
    }

    virtual void set_colors_overrides(const skin_colors& colors)
    {
      m_ColorsOverride = colors;
    }

  };

  widget_ptr get_desktop();

  typedef std::vector<widget_ptr> widgets_vec;
  void collect_descendants(widget_ptr root, const xstring& type, widgets_vec& result);

} // namespace OGUI

#endif // H_OGUI_WIDGET



