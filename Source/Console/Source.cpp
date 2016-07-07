#include <iostream>

#include <ErrorHandling.hpp>


void createWindow()
{
	auto handleInstance = GetModuleHandleA(NULL);
	auto windowClassName = "My Window Class";
	auto windowTitle = "Window Title";

	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = windowClassName;
		windowClass.hInstance = handleInstance;
		windowClass.lpfnWndProc = DefWindowProc;

		if(!RegisterClassA(&windowClass))
		{
			WinAPI::ErrorTest();
		}
	}

	HWND handleWindow;
	{
		handleWindow = CreateWindowA(
			windowClassName,
			windowTitle,
			WS_SYSMENU | WS_VISIBLE,
			0, 0, 800, 600,
			NULL,
			NULL,
			handleInstance,
			NULL
		);

		WinAPI::ErrorTest();
	}

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while(PeekMessageA(&msg, handleWindow, 0, 0, PM_REMOVE))
			{
				WinAPI::ErrorTest();

				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		Sleep(10);
	}

	if(!DestroyWindow(handleWindow))
	{
		WinAPI::ErrorTest();
	}

	if(!UnregisterClassA(windowClassName, handleInstance))
	{
		WinAPI::ErrorTest();
	}
}

void main()
{
	try
	{
		createWindow();
	}
	catch(WinAPI::Exception exception)
	{
		std::cout << "Error while running: " << exception.GetText() << std::endl;
	}

	std::system("pause");
}