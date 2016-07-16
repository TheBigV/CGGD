#pragma region Include

#include <vector>
#include <iostream>
using namespace std;

#include <WinAPI/Window.hpp>
using namespace CGGD;
using namespace CGGD::WinAPI;

#include <OpenGL/WinAPI.hpp>
#include <OpenGL/Functions.hpp>
using namespace CGGD::OpenGL;
using namespace CGGD::OpenGL::WinAPI;

#pragma endregion


void func()
{
	auto instance = Instance::Get();
	auto windowClass = new WindowClass(instance, "class");
	auto window = new Window(windowClass, "window");
	auto deviceContext = new DeviceContext(window);
	deviceContext->SetPixelFormat();
	auto renderContext = new RenderContextExtended(deviceContext);
	renderContext->Set();

	GLuint attributeBuffer;
	{
		glGenVertexArrays(1, &attributeBuffer);
		glBindVertexArray(attributeBuffer);
	}

	GLuint vertexBuffer;
	{
		std::vector<float> source = {-0.5f, -0.5f, +0.5f, -0.5f, 0.0f, +0.5f};

		glGenBuffers(1, &vertexBuffer);
		OpenGL::ErrorTest();

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		OpenGL::ErrorTest();

		glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(source)::value_type)*source.size(), source.data(), GL_STATIC_DRAW);
		OpenGL::ErrorTest();
	}

	GLuint program = glCreateProgram();
	{
		auto CompileShader = [](GLuint shader)
		{
			glCompileShader(shader);

			GLint compileResult;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

			if(compileResult != GL_TRUE)
			{
				GLint errorCodeLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorCodeLength);

				char *buffer = (char*)malloc(errorCodeLength + 1);
				int length;
				glGetShaderInfoLog(shader, errorCodeLength, &length, buffer);

				buffer[errorCodeLength] = '\0';

				auto errorText = "[glCompileShader] Error:\n" + string(buffer);

				free(buffer);

				throw OpenGL::Exception(errorText);
			}
		};
		auto LinkProgram = [](GLuint program)
		{
			glLinkProgram(program);

			GLint linkResult;
			glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

			if(linkResult != GL_TRUE)
			{
				GLint errorCodeLength;

				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorCodeLength);

				char *buffer = (char*)malloc(errorCodeLength + 1);
				int length = errorCodeLength;

				glGetProgramInfoLog(program, errorCodeLength, &length, buffer);

				buffer[errorCodeLength] = '\0';
				string code = string(buffer);

				free(buffer);

				throw OpenGL::Exception(code);
			}
		};

		OpenGL::ErrorTest();

		GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
		{
			OpenGL::ErrorTest();

			std::string source = "#version 330 core\nin vec2 vPos; void main(){gl_Position = vec4(vPos,0,1);}";
			auto data = source.data();
			GLint length = source.size();

			glShaderSource(shaderVertex, 1, &data, &length);
			OpenGL::ErrorTest();

			CompileShader(shaderVertex);
			OpenGL::ErrorTest();
		}
		GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
		{
			OpenGL::ErrorTest();

			std::string source = "#version 330 core\nout vec4 outColor; void main(){outColor = vec4(0,1,0,1);}";
			auto data = source.data();
			GLint length = source.size();

			glShaderSource(shaderFragment, 1, &data, &length);
			OpenGL::ErrorTest();

			CompileShader(shaderFragment);
			OpenGL::ErrorTest();
		}

		glAttachShader(program, shaderVertex);
		OpenGL::ErrorTest();

		glAttachShader(program, shaderFragment);
		OpenGL::ErrorTest();

		LinkProgram(program);
		OpenGL::ErrorTest();

		glDeleteShader(shaderVertex);
		glDeleteShader(shaderFragment);

		glUseProgram(program);
		OpenGL::ErrorTest();

		auto attribute_vPos = glGetAttribLocation(program, "vPos");
		glVertexAttribPointer(attribute_vPos, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 2, nullptr);
		glEnableVertexAttribArray(attribute_vPos);
	}

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		OpenGL::ErrorTest();
	
		window->Loop();
		deviceContext->SwapBuffers();
	
		Sleep(10);
	}

	glDeleteProgram(program);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &attributeBuffer);

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