#include <iostream>
#include <vector>
#include <ogui/ogui.h>
#include "SDL.h"

using namespace OGUI;

Image g_Image;
SDL_Window* g_Window=0;
SDL_Renderer* g_Renderer = 0;
SDL_Texture*  g_Texture = 0;

const int WIDTH = 640, HEIGHT = 480;

bool init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  g_Window = SDL_CreateWindow("Hello OGUI", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  g_Texture = SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);


  OGUIManager::instance()->initialize_desktop(WIDTH, HEIGHT);
  g_Image = Image(WIDTH, HEIGHT);

  {
    // These lines are the layout loading part.  Complex GUI has a more complex set of these lines
    OGUIManager::instance()->clear();
    widget_ptr button = TextPushButtonWidget::create("Push Me");
    button->set_rect(Rect(200, 200, 440, 280));
    OGUIManager::instance()->get_desktop()->add_child(button);
  }
  return true;
}

void deinit()
{
  SDL_DestroyTexture(g_Texture);
  SDL_DestroyRenderer(g_Renderer);
  SDL_DestroyWindow(g_Window);
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  init();

  bool done = false;
  while (!done)
  {
    SDL_Event e;
    bool do_sleep = true;
    while (SDL_PollEvent(&e)){
      do_sleep = false;
      if (e.type == SDL_QUIT) done = true;
      if (e.type == SDL_KEYDOWN) OGUIManager::instance()->on_keyboard(e.key.keysym.sym);
      if (e.type == SDL_MOUSEBUTTONDOWN) OGUIManager::instance()->mouse_down(0, e.motion.x, e.motion.y);
      if (e.type == SDL_MOUSEBUTTONUP)   OGUIManager::instance()->mouse_up(0, e.motion.x, e.motion.y);
    }
    if (OGUIManager::instance()->get_desktop()->draw(g_Image, Rect(0, 0, WIDTH, HEIGHT)))
    {
      SDL_Rect rect;
      byte* pixels;
      int   pitch;
      rect.x = rect.y = 0;
      rect.w = WIDTH;
      rect.h = HEIGHT;
      SDL_LockTexture(g_Texture, &rect, (void**)&pixels, &pitch);
      for (int y = 0; y < HEIGHT; ++y)
      {
        const byte* src = g_Image.get_row(y);
        byte* dst = pixels + (pitch*y);
        std::copy(src, src + 4 * WIDTH, dst);
      }
      SDL_UnlockTexture(g_Texture);

      do_sleep = false;
      SDL_RenderClear(g_Renderer);
      SDL_RenderCopy(g_Renderer, g_Texture, NULL, NULL);
      SDL_RenderPresent(g_Renderer);
    }
    if (do_sleep) SDL_Delay(10);
  }

  deinit();
  return 0;
}
