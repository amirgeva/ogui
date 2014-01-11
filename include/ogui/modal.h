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
    static std::shared_ptr<ModalWidget> create(widget_ptr tree, modal_callback cb)
    {
      std::shared_ptr<ModalWidget> w(new ModalWidget(tree, cb));
      OGUIManager::instance()->set_modal_widget(w);
      return w;
    }

  };

  typedef std::shared_ptr<ModalWidget> modal_widget_ptr;

  modal_widget_ptr create_text_query_dialog(const xstring& query, unsigned possible_results, ModalWidget::modal_callback cb);

} // namespace OGUI

#endif // modal_h__
