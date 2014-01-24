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
#ifndef H_OGUI_GENERATOR
#define H_OGUI_GENERATOR

#include <functional>
#include <xstring.h>
#include <xml.h>
#include <ogui/math2d.h>
#include <ogui/widget.h>

namespace OGUI {

  /** Load GUI layout from an XML source.
      Example of usage when loading from an XML file:

      ```
      xml_element_ptr root=load_xml_from_file("my_layout.xml");
      widget_ptr ui=load_layout_xml(root);
      ```

      Here is a more elaborate example, that loads and set the UI:

      ```
      OGUIManager::instance()->clear();
      xml_element_ptr root=load_xml_from_file("my_layout.xml");
      get_desktop()->add_child(load_layout_xml(root));
      ```
  */
  widget_ptr load_layout_xml(const xml_element_ptr root);

} // namespace OGUI

#endif // H_OGUI_GENERATOR

