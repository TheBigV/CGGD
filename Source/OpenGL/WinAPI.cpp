#include "WinAPI.hpp"


#define __CGGD__OPENGL_GET_PROC(x) x = reinterpret_cast<decltype(x)>(wglGetProcAddress(#x))


void CGGD::OpenGL::WinAPI::RenderContext::Reset()
{
	if(!wglMakeCurrent(nullptr, nullptr))
	{
		ErrorTest();
		CGGD::WinAPI::ErrorTest();
	}
}
void CGGD::OpenGL::WinAPI::RenderContext::Set()
{
	if(!wglMakeCurrent(deviceContext->GetHandle(), handle))
	{
		ErrorTest();
		CGGD::WinAPI::ErrorTest();
	}
}
CGGD::OpenGL::WinAPI::RenderContext::RenderContext(DeviceContext* deviceContext_):
	deviceContext(deviceContext_),
	handle(wglCreateContext(deviceContext->GetHandle()))
{
	if(!handle)
	{
		ErrorTest();
	}
}
CGGD::OpenGL::WinAPI::RenderContext::~RenderContext()
{
	wglDeleteContext(handle);
}


CGGD::OpenGL::WinAPI::RenderContextExtended::Initer::Initer()
{
	auto instance = CGGD::WinAPI::Instance::Get();
	auto windowClass = new CGGD::WinAPI::WindowClass(instance, "class");
	auto window = new CGGD::WinAPI::Window(windowClass, "window");
	auto deviceContext = new CGGD::WinAPI::DeviceContext(window);
	deviceContext->SetPixelFormat();
	auto renderContext = new RenderContext(deviceContext);
	renderContext->Set();


	__CGGD__OPENGL_GET_PROC(wglCreateContextAttribsARB);

	__CGGD__OPENGL_GET_PROC(glGenVertexArrays);
	__CGGD__OPENGL_GET_PROC(glDeleteVertexArrays);
	__CGGD__OPENGL_GET_PROC(glBindVertexArray);

	__CGGD__OPENGL_GET_PROC(glGenBuffers);
	__CGGD__OPENGL_GET_PROC(glDeleteBuffers);
	__CGGD__OPENGL_GET_PROC(glBindBuffer);
	__CGGD__OPENGL_GET_PROC(glBufferData);

	__CGGD__OPENGL_GET_PROC(glCreateProgram);
	__CGGD__OPENGL_GET_PROC(glDeleteProgram);
	__CGGD__OPENGL_GET_PROC(glUseProgram);
	__CGGD__OPENGL_GET_PROC(glLinkProgram);
	__CGGD__OPENGL_GET_PROC(glValidateProgram);
	__CGGD__OPENGL_GET_PROC(glGetProgramiv);
	__CGGD__OPENGL_GET_PROC(glGetProgramInfoLog);

	__CGGD__OPENGL_GET_PROC(glCreateShader);
	__CGGD__OPENGL_GET_PROC(glDeleteShader);
	__CGGD__OPENGL_GET_PROC(glShaderSource);
	__CGGD__OPENGL_GET_PROC(glCompileShader);
	__CGGD__OPENGL_GET_PROC(glAttachShader);
	__CGGD__OPENGL_GET_PROC(glDetachShader);
	__CGGD__OPENGL_GET_PROC(glGetShaderiv);
	__CGGD__OPENGL_GET_PROC(glGetShaderInfoLog);

	__CGGD__OPENGL_GET_PROC(glGetUniformLocation);
	__CGGD__OPENGL_GET_PROC(glUniform1f);
	__CGGD__OPENGL_GET_PROC(glUniform1i);

	__CGGD__OPENGL_GET_PROC(glGetAttribLocation);
	__CGGD__OPENGL_GET_PROC(glVertexAttribPointer);
	__CGGD__OPENGL_GET_PROC(glEnableVertexAttribArray);
	__CGGD__OPENGL_GET_PROC(glDisableVertexAttribArray);

	__CGGD__OPENGL_GET_PROC(glActiveTexture);


	RenderContext::Reset();

	delete renderContext;
	delete deviceContext;
	delete window;
	delete windowClass;
	delete instance;
}


const CGGD::OpenGL::WinAPI::RenderContextExtended::Initer CGGD::OpenGL::WinAPI::RenderContextExtended::initer;
const GLint CGGD::OpenGL::WinAPI::RenderContextExtended::attribs[] = {
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0, 0
};
void CGGD::OpenGL::WinAPI::RenderContextExtended::Reset()
{
	if(!wglMakeCurrent(nullptr, nullptr))
	{
		ErrorTest();
		CGGD::WinAPI::ErrorTest();
	}
}
void CGGD::OpenGL::WinAPI::RenderContextExtended::Set()
{
	if(!wglMakeCurrent(deviceContext->GetHandle(), handle))
	{
		ErrorTest();
		CGGD::WinAPI::ErrorTest();
	}
}
CGGD::OpenGL::WinAPI::RenderContextExtended::RenderContextExtended(DeviceContext* deviceContext_):
	deviceContext(deviceContext_),
	handle(wglCreateContextAttribsARB(deviceContext->GetHandle(), nullptr, attribs))
{
	if(!handle)
	{
		ErrorTest();
	}
}
CGGD::OpenGL::WinAPI::RenderContextExtended::~RenderContextExtended()
{
	wglDeleteContext(handle);
}



