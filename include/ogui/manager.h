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
#ifndef H_OGUI_MANAGER
#define H_OGUI_MANAGER

#include <functional>
#include <list>
#include <memory>
#include <xstring.h>
#include <input_callback.h>
#include <ogui/font.h>


namespace OGUI {

class   Layout;
class   Widget;
typedef std::shared_ptr<Widget> widget_ptr;
typedef std::shared_ptr<Layout> layout_ptr;
typedef std::function<void(xstring,xstring,xstring)> event_callback;
#define OGUI_EVENT_CALLBACK [this](const xstring& name, const xstring& event_type, const xstring& param)

class OGUIManager : public InputCallback
{
public:
  static OGUIManager* instance()
  {
    static std::unique_ptr<OGUIManager> ptr(new OGUIManager);
    return ptr.get();
  }
  font_ptr    get_default_font() { return m_Font; }
  void        set_default_font(font_ptr font) { m_Font=font; }
  unsigned    get_skin_color(SkinColors which);
  void        set_skin_color(SkinColors which, unsigned value);

  const skin_colors& get_skin_colors() const { return m_SkinColors.back(); }
  void               push_color_state();
  void               pop_color_state();

  void        load_skin(const xstring& skin_file) { load_skin(std::ifstream(skin_file)); }
  void        load_skin(std::istream& skin_is);

  bool        add_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type, event_callback callback);
  bool        remove_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type);
  void        raise_event(const xstring& name, const xstring& type, const xstring& params);

  /** Clear all widgets in the desktop and remove all listeners */
  void        clear();

  widget_ptr  get_desktop();

  void        set_modal_widget(widget_ptr w);

  void        capture_mouse(Widget* w) { m_MouseCapture=w; }

  virtual void on_keyboard(unsigned char key) override {}
  virtual void mouse_down(int button, int x, int y) override;
  virtual void mouse_up(int button, int x, int y) override;
  virtual void mouse_move(int x, int y) override;
  virtual void mouse_drag(int x, int y) override;
private:
  friend struct std::default_delete<OGUIManager>;

  OGUIManager()
    : m_MouseCapture(0)
  {
    initialize_desktop();
    load_default_skin();
  }
  ~OGUIManager() {}
  OGUIManager(const OGUIManager&) {}
  OGUIManager& operator= (const OGUIManager&) { return *this; }

  void initialize_desktop();
  void load_default_skin();

  typedef std::list<skin_colors> colors_stack;
  colors_stack m_SkinColors;

  widget_ptr& get_event_recipient() { if (m_ModalWidget) return m_ModalWidget; return m_Desktop; }

  widget_ptr            m_Desktop;
  font_ptr              m_Font;
  Widget*               m_MouseCapture;
  widget_ptr            m_ModalWidget;

  struct listener
  {
    listener() {}
    listener(const xstring& listener_name, event_callback cb)
      : name(listener_name), callback(cb) {}
    xstring name;
    event_callback callback;
  };
  typedef std::vector<listener> listener_seq;
  typedef std::unordered_map<xstring,listener_seq> listener_map;

  bool remove_listener(const xstring& listener_name, listener_seq& seq);

  listener_map m_Listeners;
};


} // namespace OGUI

#endif // H_OGUI_MANAGER

