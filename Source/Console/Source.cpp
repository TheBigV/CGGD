#include <iostream>

#include <Windows.h>


void main()
{
	auto handleInstance = GetModuleHandle(NULL);

	WNDCLASS windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = L"My Window Class";
		windowClass.hInstance = handleInstance;
		windowClass.lpfnWndProc = DefWindowProc;
	}

	if(!RegisterClass(&windowClass))
	{
		std::cout << "Shit happen while class registration" << std::endl;
	}

	HWND handleWindow;
	{
		if(!CreateWindow(
			L"My Window Class",
			L"Window Title",
			WS_SYSMENU | WS_VISIBLE,
			0, 0, 800, 600,
			NULL,
			NULL,
			handleInstance,
			NULL
		))
		{
			std::cout << "Shit happen while window creation" << std::endl;
		}
	}

	while(GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		MSG msg;
		{
			while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		Sleep(10);
	}

	std::system("pause");
}