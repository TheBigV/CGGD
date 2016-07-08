#include <iostream>
using namespace std;

#include <WinAPI/ErrorHandling.hpp>
#include <WinAPI/Window.hpp>
using namespace CGGD;
using namespace WinAPI;

void main()
{
	auto instance = Instance::Get();
	auto windowClass = new WindowClass(instance, "Class");
	auto window = new Window(windowClass, "Window");

	while(true)
	{
		window->Loop();

		Sleep(10);
	}

	delete window;
	delete windowClass;
	delete instance;

	system("pause");
}