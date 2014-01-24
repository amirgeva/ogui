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
#define OGUI_EVENT_CALLBACK_FUNC [](const xstring& name, const xstring& event_type, const xstring& param)

class OGUIManager : public InputCallback
{
public:
  static OGUIManager* instance()
  {
    static std::unique_ptr<OGUIManager> ptr(new OGUIManager);
    return ptr.get();
  }

  /** Main initialization method.  Must be called once, to indicate the size of 
      the virtual desktop
  */
  void        initialize_desktop(int width, int height);

  /** Return the current default font.  Initial font is preloaded automatically */
  font_ptr    get_default_font() { return m_Font; }

  /** Replace the default font with an alternative */
  void        set_default_font(font_ptr font) { m_Font=font; }

  /** Return a color by using one of the following indices:
  ```
          SKIN_COLOR_DEFAULT_FILL       - Fill color of static widgets
          SKIN_COLOR_BUTTON_HILIGHT     - Top and left highlight of 3D button look
          SKIN_COLOR_BUTTON_LOLIGHT     - Bottom and right highlight of 3D button look
          SKIN_COLOR_CHECK_COLOR        - Color of check mark in checkbox
          SKIN_COLOR_FRAME              - Color of FrameWidget border
          SKIN_COLOR_TABLE_HEADER_BG    - Background color of column headers in a table
          SKIN_COLOR_TABLE_HEADER_TEXT  - Text color of column headers in a table
          SKIN_COLOR_TEXT               - Text color (in TextWidget)
  ```
  */
  unsigned    get_skin_color(SkinColors which);
  void        set_skin_color(SkinColors which, unsigned value);

  /** Return the current skin colors.  */
  const skin_colors& get_skin_colors() const { return m_SkinColors.back(); }

  /** Save the current colors in the stack and place a copy of them on the top.
      This is used during layout XML loading, to allow local sub-tree color overrides
  */
  void               push_color_state();
  void               pop_color_state();

  /** Load color configuration from a file. The file is an XML of format similar to the following:
  ```
  <skin>
    <color name="DEFAULT_FILL" value="0xFF000000"/>
    <color name="TEXT" value="0xFFFF00FF"/>
    .
    .
    .
    .
  </skin>
  ```
  */
  void        load_skin(const xstring& skin_file) 
  {
    std::ifstream f(skin_file);
    load_skin(f); 
  }

  /** Load color configuration from a stream */
  void        load_skin(std::istream& skin_is);

  /** Register a listener to accept event callbacks.
      The listener_name is needed only for later calls to remove_listener
      target_name is the name of widget that is expected to raise events
      event_type is event type string, which can be one of the following: 
      
      * clicked
      * toggled
      * mouse_move
      * mouse_drag
      * mouse_enter
      * mouse_leave
      * scroll

      The callback has the prototype of:  func(const xstring& name, const xstring& type, const xstring& param)
      
      * name        - Name of widget that generated the event
      * type        - Event type (see list above)
      * param       - Free format parameter, depending on event type

      Typical cases use one of the following macros to define a lambda callback:

      * OGUI_EVENT_CALLBACK
      * OGUI_EVENT_CALLBACK_FUNC


      Example:

      ```
      OGUIManager::instance()->add_listener("myname","widget_name","clicked",OGUI_EVENT_CALLBACK_FUNC
      {
        do_something;
      });
      ```

      Calling add_listener on the widget directly shortens the code by using the widget's get_name() as the
      first parameter to this call.

      Example:

      ```
      widget->add_listener("myname","clicked",OGUI_EVENT_CALLBACK_FUNC
      {
      do_something;
      });
      ```

  */
  bool        add_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type, event_callback callback);

  /** Remove a previously registered listener.
      Using clear() also removes all listeners
  */
  bool        remove_listener(const xstring& listener_name, const xstring& target_name, const xstring& event_type);

  /** Called by widgets to notify with regards to an event that just occurred */
  void        raise_event(const xstring& name, const xstring& type, const xstring& params);

  /** Clear all widgets in the desktop and remove all listeners */
  void        clear();

  /** Return the desktop widget.  Usually used to add child UI elements */
  widget_ptr  get_desktop();

  /** Register a modal widget - See [ModalWidget](ModalWidget)
      All input events are then sent to this widget, until another or an empty widget is assigned
  */
  void        set_modal_widget(widget_ptr w);

  /** Called to direct all mouse events to a specific widget.
      Usually used when a widget is clicked to direct drag events to it, even if the cursor left 
      the widget's area
  */
  void        capture_mouse(Widget* w) { m_MouseCapture=w; }

  /** Hook for keyboard events.  Not implemented yet */
  virtual void on_keyboard(unsigned char key) override {}

  virtual void mouse_down(int button, int x, int y) override;
  virtual void mouse_up(int button, int x, int y) override;
  virtual void mouse_move(int x, int y) override;
  virtual void mouse_drag(int x, int y) override;
  virtual void mouse_scroll(int direction) override;
private:
  friend struct std::default_delete<OGUIManager>;

  OGUIManager()
    : m_MouseCapture(0)
  {
    load_default_skin();
  }
  ~OGUIManager() {}
  OGUIManager(const OGUIManager&) {}
  OGUIManager& operator= (const OGUIManager&) { return *this; }

  void load_default_skin();

  typedef std::list<skin_colors> colors_stack;
  colors_stack m_SkinColors;

  widget_ptr& get_event_recipient() { if (m_ModalWidget) return m_ModalWidget; return m_Desktop; }

  widget_ptr            m_Desktop;
  font_ptr              m_Font;
  Widget*               m_MouseCapture;
  widget_ptr            m_LastCursorLeafWidget;
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

