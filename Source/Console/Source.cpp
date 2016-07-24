#pragma region Include

#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include <WinAPI/Window.hpp>
using namespace CGGD;
using namespace CGGD::WinAPI;

#include <OpenGL/WinAPI.hpp>
#include <OpenGL/Functions.hpp>
using namespace CGGD::OpenGL;
using namespace CGGD::OpenGL::WinAPI;
#pragma endregion


#define PATH(x) "../../../../" + (std::string)x


std::string path(const std::string& x)
{
	return "../../../../" + x;
}
std::string loadFile(const std::string& filename)
{
	std::ifstream file(filename);

	std::string source;

	std::getline(file, source, '\0');

	file.close();

	return source;
}


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

	struct Vertex
	{
		float x;
		float y;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		float u;
		float v;
	};

	std::vector<Vertex> source = {
		Vertex{-0.5f, -0.5f, 0xFF, 0x00, 0x00, 0.0f, 0.0f},
		Vertex{+0.5f, -0.5f, 0x00, 0xFF, 0x00, 1.0f, 0.0f},
		Vertex{-0.5f, +0.5f, 0x00, 0x00, 0xFF, 0.0f, 1.0f},
		Vertex{+0.5f, +0.5f, 0x00, 0xFF, 0xFF, 1.0f, 1.0f}
	};

	std::vector<std::uint8_t> indices = {
		0, 1, 2,
		1, 2, 3
	};

	GLuint vertexBuffer;
	{
		glGenBuffers(1, &vertexBuffer);
		OpenGL::ErrorTest();

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		OpenGL::ErrorTest();

		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(decltype(source)::value_type) * source.size(), // sizeof(float) * source.size()
			source.data(), // float*
			GL_STATIC_DRAW // GL_STATIC_DRAW GL_DYNAMIC_DRAW GL_STREAM_DRAW
		);
		OpenGL::ErrorTest();
	}

	GLuint indexBuffer;
	{
		glGenBuffers(1, &indexBuffer);
		OpenGL::ErrorTest();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		OpenGL::ErrorTest();

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(decltype(indices)::value_type) * indices.size(),
			indices.data(),
			GL_STATIC_DRAW
		);
		OpenGL::ErrorTest();
	}

	GLuint texture;
	{
		size_t sizeX = 512;
		size_t sizeY = 512;
		std::vector<std::uint8_t> data(sizeX*sizeY*3);
		{
			for(size_t x = 0; x < sizeX; ++x)
			for(size_t y = 0; y < sizeY; ++y)
			{
				auto &red	= data[(x + y*sizeX) * 3 + 0];
				auto &green	= data[(x + y*sizeX) * 3 + 1];
				auto &blue	= data[(x + y*sizeX) * 3 + 2];

				if(rand() % 2 == 0)
				{
					red = 0xFF;
					green = 0xFF;
					blue = 0xFF;
				}
				else
				{
					red = 0x00;
					green = 0x00;
					blue = 0x00;
				}
			}
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB8,
			sizeX,
			sizeY,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data.data()
		);
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

			std::string source = loadFile(path("Media/Shaders/1.vs")); // "#version 330 core\nin vec2 vPos; void main(){gl_Position = vec4(vPos,0,1);}";
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

			std::string source = loadFile(path("Media/Shaders/1.fs")); // "#version 330 core\nout vec4 outColor; void main(){outColor = vec4(0,1,0,1);}";
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
		if(attribute_vPos != -1)
		{
			OpenGL::ErrorTest();
			glEnableVertexAttribArray(attribute_vPos);
			OpenGL::ErrorTest();
			glVertexAttribPointer(attribute_vPos, 2, GL_FLOAT, GL_FALSE, sizeof(decltype(source)::value_type), 0);
			OpenGL::ErrorTest();
		}
		
		auto attribute_vColor = glGetAttribLocation(program, "vColor");
		if(attribute_vColor != -1)
		{
			OpenGL::ErrorTest();
			glVertexAttribPointer(attribute_vColor, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(decltype(source)::value_type), (void*)8);
			OpenGL::ErrorTest();
			glEnableVertexAttribArray(attribute_vColor);
			OpenGL::ErrorTest();
		}

		auto attribute_vTex = glGetAttribLocation(program, "vTex");
		if(attribute_vTex != -1)
		{
			OpenGL::ErrorTest();
			glVertexAttribPointer(attribute_vTex, 2, GL_FLOAT, GL_FALSE, sizeof(decltype(source)::value_type), (void*)12);
			OpenGL::ErrorTest();
			glEnableVertexAttribArray(attribute_vTex);
			OpenGL::ErrorTest();
		}
	}

	auto uniform_offsetX = glGetUniformLocation(program, "offsetX");
	float t = 0.0f;

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		t += 0.005f;
		glUniform1f(uniform_offsetX, sin(t));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		OpenGL::ErrorTest();
	
		window->Loop();
		deviceContext->SwapBuffers();
	
		Sleep(10);
	}

	glBindTexture(GL_TEXTURE_2D, 0); glDeleteTextures(1, &texture);
	glUseProgram(0); glDeleteProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, 0); glDeleteBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); glDeleteBuffers(1, &indexBuffer);
	glBindVertexArray(0); glDeleteVertexArrays(1, &attributeBuffer);

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