#pragma region Include
#include <iostream>
using namespace std;

#include <WinAPI/ErrorHandling.hpp>
#include <WinAPI/Window.hpp>
using namespace CGGD;
using namespace WinAPI;

#include <OpenGL/ErrorHandling.hpp>
using namespace CGGD;
using namespace OpenGL;
#pragma endregion

void main()
{
	auto instance = Instance::Get();
	auto windowClass = new WindowClass(instance, "Class");
	auto window = new Window(windowClass, "Window");
	auto deviceContext = new DeviceContext(window);
	//auto renderContext = new 

	PIXELFORMATDESCRIPTOR pfd;
	{
		memset(&pfd, 0, sizeof(pfd));

		pfd.nSize			= sizeof(pfd);
		pfd.nVersion		= 1;
		pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType		= PFD_TYPE_RGBA;
		pfd.cColorBits		= 32;
		pfd.cRedBits		= 8;
		pfd.cRedShift		= 0;
		pfd.cGreenBits		= 8;
		pfd.cGreenShift		= 8;
		pfd.cBlueBits		= 8;
		pfd.cBlueShift		= 16;
		pfd.cAlphaBits		= 8;
		pfd.cAlphaShift		= 24;
		pfd.cAccumBits		= 0;
		pfd.cAccumRedBits	= 0;
		pfd.cAccumGreenBits = 0;
		pfd.cAccumBlueBits	= 0;
		pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits		= 32;
		pfd.cStencilBits	= 32;
		pfd.cAuxBuffers		= 0;
		pfd.iLayerType		= 0;
		pfd.bReserved		= 0;
		pfd.dwLayerMask		= 0;
		pfd.dwVisibleMask	= 0;
		pfd.dwDamageMask	= 0;

		auto pixelFormat = ChoosePixelFormat(deviceContext->GetHandle(), &pfd);
		if(!pixelFormat)
		{
			WinAPI::ErrorTest();
		}

		if(!SetPixelFormat(deviceContext->GetHandle(), pixelFormat, &pfd))
		{
			WinAPI::ErrorTest();
		}
	}

	auto rc = wglCreateContext(deviceContext->GetHandle());
	{
		if(!rc)
		{
			OpenGL::ErrorTest();
		}

		if(!wglMakeCurrent(deviceContext->GetHandle(), rc))
		{
			OpenGL::ErrorTest();
		}
	}

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window->Loop();

		SwapBuffers(deviceContext->GetHandle());

		Sleep(10);
	}

	if(!wglMakeCurrent(NULL, NULL))
	{
		OpenGL::ErrorTest();
	}

	if(!wglDeleteContext(rc))
	{
		OpenGL::ErrorTest();
	}

	delete deviceContext;
	delete window;
	delete windowClass;
	delete instance;

	system("pause");
}