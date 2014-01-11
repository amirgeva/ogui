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
#ifndef H_OGUI_CONSTANTS
#define H_OGUI_CONSTANTS

namespace OGUI {

enum Alignment { 
  ALIGN_LEFT               =  1,
  ALIGN_HCENTER            =  2,
  ALIGN_RIGHT              =  4,
  ALIGN_TOP                =  8,
  ALIGN_TOP_CENTER         = 10,
  ALIGN_VCENTER            = 16,
  ALIGN_LEFT_CENTER        = 17,
  ALIGN_CENTER             = 18,
  ALIGN_RIGHT_CENTER       = 19,
  ALIGN_BOTTOM             = 32,
  ALIGN_BOTTOM_CENTER      = 34
};

inline bool aligned(Alignment a, Alignment flag) { return ((a&flag) == flag); }

enum Orientation {
  ORIENTATION_VERTICAL,
  ORIENTATION_HORIZONTAL
};

enum SkinColors {
  SKIN_COLOR_DEFAULT_FILL,
  SKIN_COLOR_BUTTON_HILIGHT,
  SKIN_COLOR_BUTTON_LOLIGHT,
  SKIN_COLOR_CHECK_COLOR,
  SKIN_COLOR_FRAME,
  SKIN_COLOR_TABLE_HEADER_BG,
  SKIN_COLOR_TABLE_HEADER_TEXT,
  SKIN_COLOR_TEXT,
  SKIN_COLOR_LAST
};

typedef std::vector<unsigned> skin_colors;

SkinColors get_skin_color_id(const xstring& name);

const int LAYOUT_TIGHT  = 0;
const int LAYOUT_EXPAND = -1;

} // namespace OGUI

#endif // H_OGUI_CONSTANTS

