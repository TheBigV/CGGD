#include <iostream>
using namespace std;

#include <WinAPI/Window.hpp>
using namespace CGGD::WinAPI;

#include <OpenGL/WinAPI.hpp>
using namespace CGGD::OpenGL::WinAPI;

void func()
{
	auto instance = Instance::Get();
	auto windowClass = new WindowClass(instance, "class");
	auto window = new Window(windowClass, "window");
	auto deviceContext = new DeviceContext(window);
	deviceContext->SetPixelFormat();
	auto renderContext = new RenderContext(deviceContext);
	renderContext->Set();

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window->Loop();
		deviceContext->SwapBuffers();

		Sleep(10);
	}

	delete renderContext;
	delete deviceContext;
	delete window;
	delete windowClass;
	delete instance;
}

void main()
{
	try
	{
		func();
	}
	catch(CGGD::WinAPI::Exception exception)
	{
		cout << "WinAPI exception:\n" << exception.GetText() << endl;
	}
	catch(CGGD::OpenGL::Exception exception)
	{
		cout << "OpenGL exception:\n" << exception.GetText() << endl;
	}

	system("pause");
}