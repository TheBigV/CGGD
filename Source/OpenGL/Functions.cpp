#include "Functions.hpp"


PFNWGLCREATECONTEXTATTRIBSARBPROC			CGGD::OpenGL::wglCreateContextAttribsARB					= nullptr;

PFNGLGENVERTEXARRAYSPROC					CGGD::OpenGL::glGenVertexArrays								= nullptr;
PFNGLDELETEVERTEXARRAYSPROC					CGGD::OpenGL::glDeleteVertexArrays							= nullptr;
PFNGLBINDVERTEXARRAYPROC					CGGD::OpenGL::glBindVertexArray								= nullptr;

PFNGLGENBUFFERSPROC							CGGD::OpenGL::glGenBuffers									= nullptr;
PFNGLDELETEBUFFERSPROC						CGGD::OpenGL::glDeleteBuffers								= nullptr;
PFNGLBINDBUFFERPROC							CGGD::OpenGL::glBindBuffer									= nullptr;
PFNGLBUFFERDATAPROC							CGGD::OpenGL::glBufferData									= nullptr;

PFNGLCREATEPROGRAMPROC						CGGD::OpenGL::glCreateProgram								= nullptr;
PFNGLDELETEPROGRAMPROC						CGGD::OpenGL::glDeleteProgram								= nullptr;
PFNGLUSEPROGRAMPROC							CGGD::OpenGL::glUseProgram									= nullptr;
PFNGLLINKPROGRAMPROC						CGGD::OpenGL::glLinkProgram									= nullptr;
PFNGLVALIDATEPROGRAMPROC					CGGD::OpenGL::glValidateProgram								= nullptr;
PFNGLGETPROGRAMIVPROC						CGGD::OpenGL::glGetProgramiv								= nullptr;
PFNGLGETPROGRAMINFOLOGPROC					CGGD::OpenGL::glGetProgramInfoLog							= nullptr;

PFNGLCREATESHADERPROC						CGGD::OpenGL::glCreateShader								= nullptr;
PFNGLDELETESHADERPROC						CGGD::OpenGL::glDeleteShader								= nullptr;
PFNGLSHADERSOURCEPROC						CGGD::OpenGL::glShaderSource								= nullptr;
PFNGLCOMPILESHADERPROC						CGGD::OpenGL::glCompileShader								= nullptr;
PFNGLATTACHSHADERPROC						CGGD::OpenGL::glAttachShader								= nullptr;
PFNGLDETACHSHADERPROC						CGGD::OpenGL::glDetachShader								= nullptr;
PFNGLGETSHADERIVPROC						CGGD::OpenGL::glGetShaderiv									= nullptr;
PFNGLGETSHADERINFOLOGPROC					CGGD::OpenGL::glGetShaderInfoLog							= nullptr;

PFNGLGETUNIFORMLOCATIONPROC					CGGD::OpenGL::glGetUniformLocation							= nullptr;
PFNGLUNIFORM1FPROC							CGGD::OpenGL::glUniform1f									= nullptr;

PFNGLGETATTRIBLOCATIONPROC					CGGD::OpenGL::glGetAttribLocation							= nullptr;
PFNGLVERTEXATTRIBPOINTERPROC				CGGD::OpenGL::glVertexAttribPointer							= nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC			CGGD::OpenGL::glEnableVertexAttribArray						= nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC			CGGD::OpenGL::glDisableVertexAttribArray					= nullptr;


