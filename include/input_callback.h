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
#ifndef input_callback_h__
#define input_callback_h__

class InputCallback
{
public:
  enum SpecialKeys {
    F1=224, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    LEFT, UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN,
    HOME, END, INSERT
  };

  enum MouseButtons
  {
    BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT, BUTTON_SCROLLUP, BUTTON_SCROLLDOWN
  };

  virtual ~InputCallback() {}
  virtual void on_keyboard(unsigned char key) = 0;
  virtual void mouse_down(int button, int x, int y) = 0;
  virtual void mouse_up(int button, int x, int y) = 0;
  virtual void mouse_move(int x, int y) = 0;
  virtual void mouse_drag(int x, int y) = 0;
  virtual void mouse_scroll(int direction) { }
};


#endif // input_callback_h__
