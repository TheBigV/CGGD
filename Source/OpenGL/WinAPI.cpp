#include "WinAPI.hpp"


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







