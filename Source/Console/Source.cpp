#include <iostream>
using namespace std;

#include <WinAPI/Window.hpp>


#include <Windows.h>

#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/wglext.h>


void main()
{
	auto instance = CGGD::WinAPI::Instance::Get();
	auto windowClass = new CGGD::WinAPI::WindowClass(instance, "name");
	delete windowClass;
	delete instance;

	/*
	auto instance = new Instance;
	auto windowClass = new WindowClass(instance);
	auto window = new Window(windowClass);
	auto deviceContext = window->GetDeviceContext();
	auto renderContext = new RenderContext(deviceContext);
	*/

	const auto handleInstance	= GetModuleHandleA(NULL);
	const auto windowClassName	= "My Window Class";

	WNDCLASSA windowClassInfo;
	{
		memset(&windowClassInfo, 0, sizeof(windowClassInfo));

		windowClassInfo.hInstance = handleInstance;
		windowClassInfo.lpszClassName = windowClassName;
		windowClassInfo.lpfnWndProc = DefWindowProcA;

		if(!RegisterClassA(&windowClassInfo))
		{
			cout << "shit happen" << endl;
		}
	}

	HWND handleWindow;
	{
		handleWindow = CreateWindowA(
			windowClassName,
			"Window Title",
			WS_SYSMENU | WS_VISIBLE,
			0, 0, 800, 600,
			NULL,
			NULL,
			handleInstance,
			NULL
		);

		if(!handleWindow)
		{
			cout << "shit happen" << endl;
		}
	}

	HDC handleDeviceContext = GetDC(handleWindow);
	{
		if(!handleDeviceContext)
		{
			cout << "shit happen" << endl;
		}
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptorInfo;
	{
		memset(&pixelFormatDescriptorInfo, 0, sizeof(pixelFormatDescriptorInfo));

		pixelFormatDescriptorInfo.nSize			= sizeof(pixelFormatDescriptorInfo);
		pixelFormatDescriptorInfo.nVersion		= 1;
		pixelFormatDescriptorInfo.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatDescriptorInfo.iPixelType	= PFD_TYPE_RGBA;
		pixelFormatDescriptorInfo.cColorBits	= 32;
		pixelFormatDescriptorInfo.cDepthBits	= 32;
		pixelFormatDescriptorInfo.cStencilBits	= 32;

		auto pixelFormat = ChoosePixelFormat(handleDeviceContext, &pixelFormatDescriptorInfo);
		if(!pixelFormat)
		{
			cout << "shit happen" << endl;
		}

		if(!SetPixelFormat(handleDeviceContext, pixelFormat, &pixelFormatDescriptorInfo))
		{
			cout << "shit happen" << endl;
		}
	}

	auto renderContext = wglCreateContext(handleDeviceContext);
	{
		if(!renderContext)
		{
			cout << "shit happen" << endl;
		}

		if(!wglMakeCurrent(handleDeviceContext, renderContext))
		{
			cout << "shit happen" << endl;
		}
	}

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		MSG message;
		{
			while(PeekMessageA(&message, handleWindow, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessageA(&message);
			}
		}

		SwapBuffers(handleDeviceContext);

		Sleep(10);
	}

	if(!DestroyWindow(handleWindow))
	{
		cout << "shit happen" << endl;
	}

	if(!UnregisterClassA(windowClassName, handleInstance))
	{
		cout << "shit happen" << endl;
	}

	system("pause");
}