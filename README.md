ogui
====
Off-screen rendered platform independent user interface library.

Basically, it's a widget rendering and interaction library that is detached from
any system dependent resources.  The widgets are rendered on an off-screen bitmap, 
and hooks are in place to receive input device events.
After rendering, the UI bitmap can be either blitted to a 2D display, or copied to 
a texture to be displayed on OpenGL or Direct3D primitives.

The library's main purpose is to serve as simple UI for games and similar applications.
The API is simple and using new C++11 constructs, allows to create rather complex 
interactions with ease.