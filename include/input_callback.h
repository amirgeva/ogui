#ifndef input_callback_h__
#define input_callback_h__

class InputCallback
{
public:
  virtual ~InputCallback() {}
  virtual void on_keyboard(unsigned char key) = 0;
  virtual void mouse_down(int button, int x, int y) = 0;
  virtual void mouse_up(int button, int x, int y) = 0;
  virtual void mouse_move(int x, int y) = 0;
  virtual void mouse_drag(int x, int y) = 0;
};


#endif // input_callback_h__
