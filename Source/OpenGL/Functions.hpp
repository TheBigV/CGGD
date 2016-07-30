#pragma region Include
#pragma once


#include <Windows.h> // TODO: add #ifdef WIN/LIN/MAC

#include "Header.hpp"
#pragma endregion


namespace CGGD
{
	namespace OpenGL
	{
		extern PFNWGLCREATECONTEXTATTRIBSARBPROC			wglCreateContextAttribsARB;

		extern PFNGLGENVERTEXARRAYSPROC						glGenVertexArrays;
		extern PFNGLDELETEVERTEXARRAYSPROC					glDeleteVertexArrays;
		extern PFNGLBINDVERTEXARRAYPROC						glBindVertexArray;

		extern PFNGLGENBUFFERSPROC							glGenBuffers;
		extern PFNGLDELETEBUFFERSPROC						glDeleteBuffers;
		extern PFNGLBINDBUFFERPROC							glBindBuffer;
		extern PFNGLBUFFERDATAPROC							glBufferData;

		extern PFNGLCREATEPROGRAMPROC						glCreateProgram;
		extern PFNGLDELETEPROGRAMPROC						glDeleteProgram;
		extern PFNGLUSEPROGRAMPROC							glUseProgram;
		extern PFNGLLINKPROGRAMPROC							glLinkProgram;
		extern PFNGLVALIDATEPROGRAMPROC						glValidateProgram;
		extern PFNGLGETPROGRAMIVPROC						glGetProgramiv;
		extern PFNGLGETPROGRAMINFOLOGPROC					glGetProgramInfoLog;

		extern PFNGLCREATESHADERPROC						glCreateShader;
		extern PFNGLDELETESHADERPROC						glDeleteShader;
		extern PFNGLSHADERSOURCEPROC						glShaderSource;
		extern PFNGLCOMPILESHADERPROC						glCompileShader;
		extern PFNGLATTACHSHADERPROC						glAttachShader;
		extern PFNGLDETACHSHADERPROC						glDetachShader;
		extern PFNGLGETSHADERIVPROC							glGetShaderiv;
		extern PFNGLGETSHADERINFOLOGPROC					glGetShaderInfoLog;

		extern PFNGLGETUNIFORMLOCATIONPROC					glGetUniformLocation;
		extern PFNGLUNIFORM1FPROC							glUniform1f;
		extern PFNGLUNIFORM1IPROC							glUniform1i;

		extern PFNGLGETATTRIBLOCATIONPROC					glGetAttribLocation;
		extern PFNGLVERTEXATTRIBPOINTERPROC					glVertexAttribPointer;
		extern PFNGLENABLEVERTEXATTRIBARRAYPROC				glEnableVertexAttribArray;
		extern PFNGLDISABLEVERTEXATTRIBARRAYPROC			glDisableVertexAttribArray;

		extern PFNGLACTIVETEXTUREPROC						glActiveTexture;
	}
}



