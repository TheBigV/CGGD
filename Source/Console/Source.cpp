#include <iostream>

#include <ErrorHandling.hpp>
#include <Window.hpp>


void createWindow()
{
	auto instance = WinAPI::Instance::Get();
	auto windowClass = new WinAPI::WindowClass(instance, "Class");
	auto window = new WinAPI::Window(windowClass, "Window");

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		window->Loop();

		Sleep(10);
	}

	delete window;
	delete windowClass;
	delete instance;
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