#ifndef H_GLEW_STATIC_WRAPPER
#define H_GLEW_STATIC_WRAPPER

#define GLEW_STATIC
#include <GL/glew.h>

#ifdef _MSC_VER
#pragma comment(lib,"glew32s.lib")
#endif

#endif // H_GLEW_STATIC_WRAPPER

