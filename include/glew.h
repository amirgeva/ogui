#ifndef H_GLEW_STATIC_WRAPPER
#define H_GLEW_STATIC_WRAPPER



#ifdef _MSC_VER
#define GLEW_STATIC
#include <GL/mglew.h>
#pragma comment(lib,"glew32s.lib")
#else
#undef GLEW_STATIC
#include <GL/glew.h>
#endif

#endif // H_GLEW_STATIC_WRAPPER

