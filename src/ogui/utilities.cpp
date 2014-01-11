#include "stdafx.h"

namespace OGUI {

  void collect_descendants(widget_ptr root, const xstring& type, widgets_vec& result)
  {
    if (root->get_type() == type) result.push_back(root);
    for (widget_ptr w : *root)
      collect_descendants(w, type, result);
  }


} // namespace OGUI

