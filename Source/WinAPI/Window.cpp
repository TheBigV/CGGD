#include "Window.hpp"


CGGD::WinAPI::Instance* CGGD::WinAPI::Instance::Get()
{
	return new Instance(GetModuleHandleA(NULL));
}
CGGD::WinAPI::Instance::Instance(HINSTANCE handle_):
	handle(handle_)
{
}


CGGD::WinAPI::WindowClass::WindowClass(Instance* instance_, const Name& name_):
	instance(instance_),
	name(name_)
{
	WNDCLASSA windowClassInfo;
	{
		memset(&windowClassInfo, 0, sizeof(windowClassInfo));

		windowClassInfo.hInstance		= instance->GetHandle();
		windowClassInfo.lpszClassName	= name.c_str();
		windowClassInfo.lpfnWndProc = DefWindowProcA;

		if(!RegisterClassA(&windowClassInfo))
		{
			// TODO error handling
		}
	}
}
CGGD::WinAPI::WindowClass::~WindowClass()
{
	if(!UnregisterClassA(name.c_str(), instance->GetHandle()))
	{
		// TODO
	}
}
