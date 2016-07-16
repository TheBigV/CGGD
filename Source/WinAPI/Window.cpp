#include "Window.hpp"


CGGD::WinAPI::Instance* CGGD::WinAPI::Instance::Get()
{
	return new Instance(GetModuleHandleA(NULL));
}
CGGD::WinAPI::Instance::Instance(HINSTANCE handle_):
	handle(handle_)
{
}
CGGD::WinAPI::Instance::Handle CGGD::WinAPI::Instance::GetHangle() const
{
	return handle;
}


CGGD::WinAPI::WindowClass::WindowClass(Instance* instance_, const Name& name_):
	instance(instance_),
	name(name_)
{
	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = name.c_str();
		windowClass.hInstance = instance->GetHangle();
		windowClass.lpfnWndProc = DefWindowProcA;
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if(!RegisterClassA(&windowClass))
		{
			ErrorTest();
		}
	}
}
CGGD::WinAPI::WindowClass::~WindowClass()
{
	if(!UnregisterClassA(name.c_str(), instance->GetHangle()))
	{
		ErrorTest();
	}
}
CGGD::WinAPI::Instance* CGGD::WinAPI::WindowClass::GetInstance() const
{
	return instance;
}
CGGD::WinAPI::WindowClass::Name CGGD::WinAPI::WindowClass::GetName() const
{
	return name;
}


CGGD::WinAPI::Window::Window(WindowClass* windowClass_, const Name& name_):
	windowClass(windowClass_),
	name(name_),
	handle(CreateWindowA(
		windowClass->GetName().c_str(),
		name.c_str(),
		WS_SYSMENU | WS_VISIBLE,
		0, 0, 800, 600,
		NULL,
		NULL,
		windowClass->GetInstance()->GetHangle(),
		NULL
	))
{
	if(!handle)
	{
		WinAPI::ErrorTest();
	}
}
CGGD::WinAPI::Window::~Window()
{
	if(!DestroyWindow(handle))
	{
		ErrorTest();
	}
}
CGGD::WinAPI::Window::Name CGGD::WinAPI::Window::GetName() const
{
	return name;
}
CGGD::WinAPI::Window::Handle CGGD::WinAPI::Window::GetHandle() const
{
	return handle;
}
void CGGD::WinAPI::Window::Loop() const
{
	MSG msg;
	{
		while(PeekMessageA(&msg, handle, 0, 0, PM_REMOVE))
		{
			WinAPI::ErrorTest();

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}


CGGD::WinAPI::DeviceContext::DeviceContext(Window* window_):
	window(window_),
	handle(GetDC(window_->GetHandle()))
{
	if(!handle)
	{
		ErrorTest();
	}
}
CGGD::WinAPI::Window* CGGD::WinAPI::DeviceContext::GetWindow() const
{
	return window;
}
CGGD::WinAPI::DeviceContext::Handle CGGD::WinAPI::DeviceContext::GetHandle() const
{
	return handle;
}
void CGGD::WinAPI::DeviceContext::SetPixelFormat()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptorInfo;
	{
		memset(&pixelFormatDescriptorInfo, 0, sizeof(pixelFormatDescriptorInfo));

		pixelFormatDescriptorInfo.nSize = sizeof(pixelFormatDescriptorInfo);
		pixelFormatDescriptorInfo.nVersion = 1;
		pixelFormatDescriptorInfo.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatDescriptorInfo.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDescriptorInfo.cColorBits = 32;
		pixelFormatDescriptorInfo.cDepthBits = 32;
		pixelFormatDescriptorInfo.cStencilBits = 0;
	}

	auto pixelFormat = ChoosePixelFormat(handle, &pixelFormatDescriptorInfo);
	if(!pixelFormat)
	{
		ErrorTest();
	}

	if(!::SetPixelFormat(handle, pixelFormat, &pixelFormatDescriptorInfo))
	{
		ErrorTest();
	}
}
void CGGD::WinAPI::DeviceContext::SwapBuffers() const
{
	if(!::SwapBuffers(handle))
	{
		ErrorTest();
	}
}



