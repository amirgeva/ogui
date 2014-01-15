#include <iostream>
#include <vector>
#include <glew.h>
#include <glut.h>
#include <string.h>
#include <ogui/ogui.h>

using namespace OGUI;

const char* vertex_shader_src =
"#version 330\n\n"
"in vec3 vertex;\n"
"in vec2 texcoord;\n\n"
"uniform float ar;\n\n"
"smooth out vec2 vTexCoord;\n\n"
"void main()\n"
"{\n"
"  mat4 proj=mat4(1/ar,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);\n"
"  gl_Position=proj * vec4(vertex,1);\n"
"  vTexCoord=texcoord;\n"
"}\n\n";

const char* fragment_shader_src = 
"#version 330\n\n"
"uniform sampler2D utexture;\n\n"
"in vec2 vTexCoord;\n\n"
"out vec4 vFragColor;\n\n"
"void main()\n{\n"
"  vFragColor = texture(utexture, vTexCoord);\n"
"}\n\n";

GLuint g_VertexShader=0, g_FragmentShader=0, g_Program=0;
GLuint g_VBO = 0, g_IBO = 0, g_Texture=0;
Image g_Image;

bool initialized = false;

bool init();

void render()
{
  glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  float w = float(glutGet(GLUT_WINDOW_WIDTH));
  float h = float(glutGet(GLUT_WINDOW_HEIGHT));
  glViewport(0, 0, GLsizei(w), GLsizei(h));

  if (!initialized)
  {
    initialized = true;
    if (!init()) glutExit();
  }

  glUseProgram(g_Program);
  float ar = w / h;
  GLuint ar_loc = glGetUniformLocation(g_Program, "ar");
  glUniform1f(ar_loc, ar);

  GLuint v_loc=glGetAttribLocation(g_Program, "vertex");
  GLuint t_loc = glGetAttribLocation(g_Program, "texcoord");
  GLuint txtr_loc = glGetUniformLocation(g_Program, "utexture");

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, g_Texture);
  if (OGUIManager::instance()->get_desktop()->draw(g_Image, g_Image.get_rect()))
  {
    g_Image.save_to_file("d:\\tmp\\image.png");
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, GLsizei(w), GLsizei(h), GL_RGBA, GL_UNSIGNED_BYTE, g_Image.get_row(0));
  }
  glUniform1i(txtr_loc, 0);

  glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
  GLint stride = 5*sizeof(float);
  glVertexAttribPointer(v_loc, 3, GL_FLOAT, GL_FALSE, stride, 0);
  glEnableVertexAttribArray(v_loc);

  const GLvoid* toffset = (const GLvoid*)(3 * sizeof(float));
  glVertexAttribPointer(t_loc, 2, GL_FLOAT, GL_FALSE, stride, toffset);
  glEnableVertexAttribArray(t_loc);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

  glDisableVertexAttribArray(v_loc);
  glDisableVertexAttribArray(t_loc);

  glutSwapBuffers();
}

bool init()
{
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);

  OGUIManager::instance()->initialize_desktop(w, h);
  g_Image = Image(w, h);
  widget_ptr button = TextPushButtonWidget::create("Push Me");
  button->set_rect(Rect(200, 200, 440, 280));
  OGUIManager::instance()->get_desktop()->add_child(button);

  float ar = float(w) / h;
  glGenTextures(1, &g_Texture);
  glBindTexture(GL_TEXTURE_2D, g_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  std::vector<unsigned> pixels(w*h);
  for (int i = 0; i < (w*h); ++i)
    pixels[i] = i|0xFF000000;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);


  g_VertexShader=glCreateShader(GL_VERTEX_SHADER);
  GLint status, len;
  len = strlen(vertex_shader_src);
  glShaderSource(g_VertexShader, 1, &vertex_shader_src, &len);
  glCompileShader(g_VertexShader);
  glGetShaderiv(g_VertexShader, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    GLint mlen;
    glGetShaderiv(g_VertexShader, GL_INFO_LOG_LENGTH, &mlen);
    std::string s;
    s.resize(mlen);
    char* ptr = &s[0];
    glGetShaderInfoLog(g_VertexShader, mlen, 0, ptr);
    std::cout << "Failed to compile vertex shader\n" << std::endl;
    std::cout << s << std::endl;
    return false;
  }
  g_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  len = strlen(fragment_shader_src);
  glShaderSource(g_FragmentShader, 1, &fragment_shader_src, &len);
  glCompileShader(g_FragmentShader);
  glGetShaderiv(g_FragmentShader, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    std::cout << "Failed to compile fragment shader\n" << std::endl;
    return false;
  }

  g_Program = glCreateProgram();
  glAttachShader(g_Program, g_VertexShader);
  glAttachShader(g_Program, g_FragmentShader);
  glLinkProgram(g_Program);
  glGetProgramiv(g_Program, GL_LINK_STATUS, &status);
  if (!status)
  {
    std::cout << "Failed to link shaders program\n" << std::endl;
    return false;
  }

  glGenBuffers(1, &g_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
  const float vertices[] = { -ar,1,0,0,0,  ar,1,0,1,0,   ar,-1,0,1,1,  -ar,-1, 0,0,1 };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &g_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);
  const unsigned short indices[] = { 0, 1, 2, 0, 2, 3 };
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  return true;
}

void deinit()
{
  glDeleteBuffers(1, &g_VBO);
  glDeleteBuffers(1, &g_IBO);
  glDeleteTextures(1, &g_Texture);
  glDeleteProgram(g_Program);
  glDeleteShader(g_VertexShader);
  glDeleteShader(g_FragmentShader);
}

static void mouse_click(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
    OGUIManager::instance()->mouse_down(button, x, y);
  else
    OGUIManager::instance()->mouse_up(button, x, y);
}

static void mouse_drag(int x, int y)
{
  OGUIManager::instance()->mouse_drag(x, y);
}

static void idle_action()
{
  glutPostRedisplay();
}


int main( int argc, char **argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "OpenGL Sample" );
    glutDisplayFunc(render);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_drag);
    glutIdleFunc(idle_action);
    glewInit();

    glutMainLoop();
    deinit();
    return 0;
}
