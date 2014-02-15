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
#ifndef parse_h__
#define parse_h__

namespace OGUI {

inline void parse_xml_value(const xstring& xml_value, Orientation& value)
{
  xstring v = xml_value;
  v.to_upper();
  if (v == "VERTICAL") value = ORIENTATION_VERTICAL;
  else
    if (v == "HORIZONTAL") value = ORIENTATION_HORIZONTAL;
    else
      throw xstring("Invalid orientation value: " + xml_value);
}

inline void parse_xml_value(const xstring& xml_value, Alignment& value)
{
  int res = 0;
  xstring_tokenizer st(xml_value, " ,;|");
  while (st.has_more_tokens())
  {
    xstring t = st.get_next_token().to_upper();
    if (t == "LEFT")    res |= ALIGN_LEFT;
    if (t == "RIGHT")   res |= ALIGN_RIGHT;
    if (t == "TOP")     res |= ALIGN_TOP;
    if (t == "BOTTOM")  res |= ALIGN_BOTTOM;
    if (t == "HCENTER") res |= ALIGN_HCENTER;
    if (t == "VCENTER") res |= ALIGN_VCENTER;
    if (t == "CENTER")  res |= ALIGN_CENTER;
  }
  value = Alignment(res);
}

inline void parse_xml_value(const xstring& xml_value, xstring& value)
{
  value = xml_value;
}

inline void parse_xml_value(const xstring& xml_value, int& value)
{
  if (xml_value == "TIGHT") value = LAYOUT_TIGHT;
  else
    if (xml_value == "EXPAND") value = LAYOUT_EXPAND;
    else
      value = xml_value.as_int();
}

inline void parse_xml_value(const xstring& xml_value, unsigned& value)
{
  if (xml_value.begins_with("0x"))
    value = as_hex(xml_value);
  else
    value = xml_value.as_int();
}

inline void parse_xml_value(const xstring& xml_value, double& value)
{
  value = xml_value.as_double();
}

inline void parse_xml_value(const xstring& xml_value, float& value)
{
  value = float(xml_value.as_double());
}

inline void parse_xml_value(const xstring& xml_value, Point& value)
{
  xstring_tokenizer st(xml_value, ",");
  parse_xml_value(st.get_next_token(), value.x);
  parse_xml_value(st.get_next_token(), value.y);
}

inline void parse_xml_value(const xstring& xml_value, Rect& value)
{
  xstring_tokenizer st(xml_value, ",");
  value.left = st.get_next_token().as_int();
  value.top = st.get_next_token().as_int();
  value.right = st.get_next_token().as_int();
  value.bottom = st.get_next_token().as_int();
}

inline void parse_xml_value(const xstring& xml_value, bool& value)
{
  value = (xml_value == "true");
}

inline Orientation parse_Orientation(const xstring& value) { Orientation v; parse_xml_value(value, v); return v; }
inline Point parse_Point(const xstring& value) { Point v; parse_xml_value(value, v); return v; }
inline int parse_int(const xstring& value) { int v; parse_xml_value(value, v); return v; }
inline float parse_float(const xstring& value) { float v; parse_xml_value(value, v); return v; }
inline unsigned parse_unsigned(const xstring& value) { unsigned v; parse_xml_value(value, v); return v; }
inline bool parse_bool(const xstring& value) { bool v; parse_xml_value(value, v); return v; }
inline Alignment parse_Alignment(const xstring& value) { Alignment v; parse_xml_value(value, v); return v; }
inline xstring parse_xstring(const xstring& value) { xstring v; parse_xml_value(value, v); return v; }
inline Rect parse_Rect(const xstring& value) { Rect v; parse_xml_value(value, v); return v; }


} // namespace OGUI

#endif // parse_h__
