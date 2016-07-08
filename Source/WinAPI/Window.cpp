#include "Window.hpp"


WinAPI::Instance* WinAPI::Instance::Get()
{
	return new Instance(GetModuleHandleA(NULL));
}
WinAPI::Instance::Instance(HINSTANCE handle_):
	handle(handle_)
{
}
WinAPI::Instance::Handle WinAPI::Instance::GetHangle() const
{
	return handle;
}


WinAPI::WindowClass::WindowClass(Instance* instance_, const Name& name_):
	instance(instance_),
	name(name_)
{
	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = name.c_str();
		windowClass.hInstance = instance->GetHangle();
		windowClass.lpfnWndProc = DefWindowProc;

		if(!RegisterClassA(&windowClass))
		{
			ErrorTest();
		}
	}
}
WinAPI::WindowClass::~WindowClass()
{
	if(!UnregisterClassA(name.c_str(), instance->GetHangle()))
	{
		ErrorTest();
	}
}
WinAPI::Instance* WinAPI::WindowClass::GetInstance() const
{
	return instance;
}
WinAPI::WindowClass::Name WinAPI::WindowClass::GetName() const
{
	return name;
}


WinAPI::Window::Window(WindowClass* windowClass_, const Name& name_):
	windowClass(windowClass_),
	name(name_)
{
	handle = CreateWindowA(
		windowClass->GetName().c_str(),
		name.c_str(),
		WS_SYSMENU | WS_VISIBLE,
		0, 0, 800, 600,
		NULL,
		NULL,
		windowClass->GetInstance()->GetHangle(),
		NULL
	);

	if(!handle)
	{
		WinAPI::ErrorTest();
	}
}
WinAPI::Window::~Window()
{
	if(!DestroyWindow(handle))
	{
		ErrorTest();
	}
}
WinAPI::Window::Name WinAPI::Window::GetName() const
{
	return name;
}
void WinAPI::Window::Loop() const
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





