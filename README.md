ogui
====
Off-screen rendered platform independent user interface library.  ([Quickstart](https://github.com/amirgeva/ogui/wiki/Getting-Started))

OGUI is a widget rendering and interaction library that is detached from
any system dependent resources.  The widgets are rendered on an off-screen bitmap, 
and hooks are in place to receive input device events.
After rendering, the UI bitmap can be either blitted to a 2D display, or copied to 
a texture to be displayed on OpenGL or Direct3D primitives.

The library's main purpose is to serve as simple UI for games and similar applications.
There are **no external dependency** on any toolkit or requirement to install a prerequisite library.
The only non-original code used is for PNG loading (libpng, zlib), and this is also included in
the repository, in order to simplify integration.
Obviously, the final blitting requires some toolkit, but this selection is left to the user
of the library.

The API is simple and using new C++11 constructs, allows to create rather complex 
interactions with ease.