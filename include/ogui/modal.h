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
#ifndef modal_h__
#define modal_h__

#include <ogui/widget.h>

namespace OGUI {

enum DialogResult {
  DR_OK      =1,
  DR_CANCEL  =2,
  DR_YES     =4,
  DR_NO      =8
};

/** Generic widget for a modal pattern, typically used for popup dialogs over existing UIs
    When a modal widget is active (only one is possible at any given time), it gets all
    user input
*/
class ModalWidget : public Widget
{
public:
  typedef std::function<void(DialogResult)> modal_callback;
protected:
  modal_callback m_ResultCallback;

  void init_callback(const xstring& name, DialogResult res)
  {
    widget_ptr w = search(name);
    if (!w) return;
    if (w->get_type().ends_with("ButtonWidget"))
    {
      w->add_listener(get_name(), "clicked", [this, res](const xstring&, const xstring&, const xstring&)
      {
        OGUIManager::instance()->remove_listener(get_name(),"","");
        modal_callback cb = m_ResultCallback; // Copy because this object is about to be deleted
        OGUIManager::instance()->set_modal_widget(widget_ptr());
        cb(res);
      });
    }
  }

  void init_callbacks()
  {
    init_callback("ok",     DR_OK);
    init_callback("cancel", DR_CANCEL);
    init_callback("yes",    DR_YES);
    init_callback("no",     DR_NO);
  }

  ModalWidget(widget_ptr tree, modal_callback cb)
    : m_ResultCallback(cb)
  {
    set_rect(get_desktop()->get_rect());
    add_child(tree);
    init_callbacks();
  }

public:
  /** Take a preloaded widget tree and construct a modal widget that contains it.
      If the widget tree contains buttons of any of the standard responses: (yes,no,ok,cancel)
      [The button can have any text, but must have a name of one of these four]
      The callback will be called to indicate the selection.
  */
  static std::shared_ptr<ModalWidget> create(widget_ptr tree, modal_callback cb)
  {
    std::shared_ptr<ModalWidget> w(new ModalWidget(tree, cb));
    OGUIManager::instance()->set_modal_widget(w);
    return w;
  }

};

typedef std::shared_ptr<ModalWidget> modal_widget_ptr;

/** Create a simple text dialog that shows a prompt, and has buttons that match the bitwise combination
    specified in possible_results
    The callback will be activated with the selected option.  
    Useful for typical  "Are you sure you want to Z?" dialogs
*/
modal_widget_ptr create_text_query_dialog(const xstring& query, unsigned possible_results, ModalWidget::modal_callback cb);



} // namespace OGUI

#endif // modal_h__
