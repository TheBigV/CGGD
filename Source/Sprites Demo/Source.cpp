#pragma region Include

#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include <glm/glm.hpp>

#include <WinAPI/Window.hpp>
using namespace CGGD;
using namespace CGGD::WinAPI;

#include <OpenGL/WinAPI.hpp>
#include <OpenGL/Functions.hpp>
using namespace CGGD::OpenGL;
using namespace CGGD::OpenGL::WinAPI;

#include <OpenIL/Functions.hpp>
using namespace CGGD::OpenIL;


#define PATH(x) "../../../../" + (std::string)x
#pragma endregion


class Sprite
{
public:
	using vec2 = glm::vec2;
	using vec4 = glm::vec4;
public:
	vec2 pos = vec2(0.0f);
	vec2 size = vec2(100.0f);
	float ang = 20.0f;
	vec4 color = vec4(1.0f);
	float priority = 0.0f;
	GLuint texture = 0;
public:
	static const vec2 screen;
	static std::vector<Sprite*> sprites;
	static GLuint program;
	static GLuint bufferAttribute;
	static GLuint bufferVertex;
	static const auto stride = sizeof(float)* 2 + sizeof(float)* 2 + sizeof(std::uint32_t);
	// static std::vector<std::uint8_t> data;
	static void Init()
	{
		bufferAttribute;
		{
			glGenVertexArrays(1, &bufferAttribute);
			glBindVertexArray(bufferAttribute);
		}
		bufferVertex;
		{
			glGenBuffers(1, &bufferVertex);
			OpenGL::ErrorTest();

			glBindBuffer(GL_ARRAY_BUFFER, bufferVertex);
			OpenGL::ErrorTest();

			glBufferData(
				GL_ARRAY_BUFFER,
				stride * 4, // pos2(32f) tex2(32f) color4(8u)
				nullptr,
				GL_STATIC_DRAW
			);
			OpenGL::ErrorTest();
		}
		program = glCreateProgram();
		{
			auto loadFile = [](const std::string& filename) -> std::string
			{
				std::ifstream file(filename);

				std::string source;

				std::getline(file, source, '\0');

				file.close();

				return source;
			};
			auto compileShader = [](GLuint shader)
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
			auto linkProgram = [](GLuint program)
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

				std::string source = loadFile(PATH("Media/Shaders/Sprite/1.vs.glsl"));
				auto data = source.data();
				GLint length = source.size();

				glShaderSource(shaderVertex, 1, &data, &length);
				OpenGL::ErrorTest();

				compileShader(shaderVertex);
				OpenGL::ErrorTest();
			}
			GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
			{
				OpenGL::ErrorTest();

				std::string source = loadFile(PATH("Media/Shaders/Sprite/1.fs.glsl"));
				auto data = source.data();
				GLint length = source.size();

				glShaderSource(shaderFragment, 1, &data, &length);
				OpenGL::ErrorTest();

				compileShader(shaderFragment);
				OpenGL::ErrorTest();
			}

			glAttachShader(program, shaderVertex);
			OpenGL::ErrorTest();

			glAttachShader(program, shaderFragment);
			OpenGL::ErrorTest();

			linkProgram(program);
			OpenGL::ErrorTest();

			glDeleteShader(shaderVertex);
			glDeleteShader(shaderFragment);

			glUseProgram(program);
			OpenGL::ErrorTest();

			auto attribute_vPos = glGetAttribLocation(program, "vPos"); OpenGL::ErrorTest();
			if(attribute_vPos != -1)
			{
				glEnableVertexAttribArray(attribute_vPos);
				OpenGL::ErrorTest();
				glVertexAttribPointer(attribute_vPos, 2, GL_FLOAT, GL_FALSE, stride, 0);
				OpenGL::ErrorTest();
			}
		
			auto attribute_vTex = glGetAttribLocation(program, "vTex"); OpenGL::ErrorTest();
			if(attribute_vTex != -1)
			{
				glVertexAttribPointer(attribute_vTex, 2, GL_FLOAT, GL_FALSE, stride, (void*)8);
				OpenGL::ErrorTest();
				glEnableVertexAttribArray(attribute_vTex);
				OpenGL::ErrorTest();
			}

			auto attribute_vColor = glGetAttribLocation(program, "vColor"); OpenGL::ErrorTest();
			if(attribute_vColor != -1)
			{
				glVertexAttribPointer(attribute_vColor, 4, GL_UNSIGNED_BYTE, GL_FALSE, stride, (void*)16);
				OpenGL::ErrorTest();
				glEnableVertexAttribArray(attribute_vColor);
				OpenGL::ErrorTest();
			}

			auto uniform_textureColor = glGetUniformLocation(program, "textureColor"); OpenGL::ErrorTest();
			if(uniform_textureColor != -1)
			{
				glUniform1i(uniform_textureColor, 0);
				OpenGL::ErrorTest();
			}
		}
	}
	static void Render()
	{
		cout << "Sprites: " << sprites.size() << endl;

		std::sort(
			sprites.begin(),
			sprites.end(),
			[](Sprite* a, Sprite* b) {
				return a->priority < b->priority;
			}
		);

		auto data = (std::uint8_t*)malloc(stride * 4);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(bufferAttribute);
		glBindBuffer(GL_ARRAY_BUFFER, bufferVertex);
		glUseProgram(program);

		for(auto &sprite : sprites)
		{
			// auto sX = sinf((sprite->ang + 90.0f) / 180.0f * 3.14f);
			// auto cX = cosf((sprite->ang + 90.0f) / 180.0f * 3.14f);
			// auto sY = sinf((sprite->ang + 00.0f) / 180.0f * 3.14f);
			// auto cY = cosf((sprite->ang + 00.0f) / 180.0f * 3.14f);

			auto aY = glm::radians(sprite->ang + 00.0f);
			auto aX = glm::radians(sprite->ang + 90.0f);

			auto vX = sprite->size * 0.5f * vec2(sinf(aX), cosf(aX));
			auto vY = sprite->size * 0.5f * vec2(sinf(aY), cosf(aY));

			// auto vXx = sprite->sizeX*0.5f*sX;
			// auto vXy = sprite->sizeX*0.5f*cX;
			// auto vYx = sprite->sizeY*0.5f*sY;
			// auto vYy = sprite->sizeY*0.5f*cY;

			// *(float*)(data + stride * 0 + 0) = (sprite->posX - vXx - vYx) / (float)screenX * 2.0f - 1.0f;
			// *(float*)(data + stride * 0 + 4) = (sprite->posY - vXy - vYy) / (float)screenY * 2.0f - 1.0f;
			*(vec2*)(data + stride * 0 + 0) = (sprite->pos - vX - vY) / screen * 2.0f - 1.0f;
			*(float*)(data + stride * 0 + 8) = 0.0f;
			*(float*)(data + stride * 0 + 12) = 0.0f;
			*(std::uint8_t*)(data + stride * 0 + 16) = (std::uint8_t)(sprite->color.r * 255.0f);
			*(std::uint8_t*)(data + stride * 0 + 17) = (std::uint8_t)(sprite->color.g * 255.0f);
			*(std::uint8_t*)(data + stride * 0 + 18) = (std::uint8_t)(sprite->color.b * 255.0f);
			*(std::uint8_t*)(data + stride * 0 + 19) = (std::uint8_t)(sprite->color.a * 255.0f);

			// *(float*)(data + stride * 1 + 0) = (sprite->posX + vXx - vYx) / (float)screenX * 2.0f - 1.0f;
			// *(float*)(data + stride * 1 + 4) = (sprite->posY + vXy - vYy) / (float)screenY * 2.0f - 1.0f;
			*(vec2*)(data + stride * 1 + 0) = (sprite->pos + vX - vY) / screen * 2.0f - 1.0f;
			*(float*)(data + stride * 1 + 8) = 1.0f;
			*(float*)(data + stride * 1 + 12) = 0.0f;
			*(std::uint8_t*)(data + stride * 1 + 16) = (std::uint8_t)(sprite->color.r * 255.0f);
			*(std::uint8_t*)(data + stride * 1 + 17) = (std::uint8_t)(sprite->color.g * 255.0f);
			*(std::uint8_t*)(data + stride * 1 + 18) = (std::uint8_t)(sprite->color.b * 255.0f);
			*(std::uint8_t*)(data + stride * 1 + 19) = (std::uint8_t)(sprite->color.a * 255.0f);

			// *(float*)(data + stride * 2 + 0) = (sprite->posX - vXx + vYx) / (float)screenX * 2.0f - 1.0f;
			// *(float*)(data + stride * 2 + 4) = (sprite->posY - vXy + vYy) / (float)screenY * 2.0f - 1.0f;
			*(vec2*)(data + stride * 2 + 0) = (sprite->pos - vX + vY) / screen * 2.0f - 1.0f;
			*(float*)(data + stride * 2 + 8) = 0.0f;
			*(float*)(data + stride * 2 + 12) = 1.0f;
			*(std::uint8_t*)(data + stride * 2 + 16) = (std::uint8_t)(sprite->color.r * 255.0f);
			*(std::uint8_t*)(data + stride * 2 + 17) = (std::uint8_t)(sprite->color.g * 255.0f);
			*(std::uint8_t*)(data + stride * 2 + 18) = (std::uint8_t)(sprite->color.b * 255.0f);
			*(std::uint8_t*)(data + stride * 2 + 19) = (std::uint8_t)(sprite->color.a * 255.0f);

			// *(float*)(data + stride * 3 + 0) = (sprite->posX + vXx + vYx) / (float)screenX * 2.0f - 1.0f;
			// *(float*)(data + stride * 3 + 4) = (sprite->posY + vXy + vYy) / (float)screenY * 2.0f - 1.0f;
			*(vec2*)(data + stride * 3 + 0) = (sprite->pos + vX + vY) / screen * 2.0f - 1.0f;
			*(float*)(data + stride * 3 + 8) = 1.0f;
			*(float*)(data + stride * 3 + 12) = 1.0f;
			*(std::uint8_t*)(data + stride * 3 + 16) = (std::uint8_t)(sprite->color.r * 255.0f);
			*(std::uint8_t*)(data + stride * 3 + 17) = (std::uint8_t)(sprite->color.g * 255.0f);
			*(std::uint8_t*)(data + stride * 3 + 18) = (std::uint8_t)(sprite->color.b * 255.0f);
			*(std::uint8_t*)(data + stride * 3 + 19) = (std::uint8_t)(sprite->color.a * 255.0f);

			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, sprite->texture);

			glBufferData(GL_ARRAY_BUFFER, stride * 4, data, GL_STATIC_DRAW); OpenGL::ErrorTest();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		free(data);
	}
public:
	inline Sprite()
	{
		sprites.push_back(this);
	}
	inline ~Sprite()
	{
		sprites.erase(std::find(sprites.begin(), sprites.end(), this));
	}
};
const Sprite::vec2 Sprite::screen = Sprite::vec2(800.0f, 600.0f);
std::vector<Sprite*> Sprite::sprites;
GLuint Sprite::program;
GLuint Sprite::bufferAttribute;
GLuint Sprite::bufferVertex;


void func()
{
	auto instance = Instance::Get();
	auto windowClass = new WindowClass(instance, "class");
	auto window = new Window(windowClass, "window");
	auto deviceContext = new DeviceContext(window);
	deviceContext->SetPixelFormat();
	auto renderContext = new RenderContextExtended(deviceContext);
	renderContext->Set();

	auto loadTexture = [&](const string& filename)
	{
		GLuint texture;
		{
			auto image = Image::Load2D(filename);
			if(image->GetOriginMode() != Image::Origin::LowerLeft)
			{
				image->Flip();
			}

			glGenTextures(1, &texture); OpenGL::ErrorTest(); OpenGL::ErrorTest();
			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, texture); OpenGL::ErrorTest(); OpenGL::ErrorTest();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); OpenGL::ErrorTest();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); OpenGL::ErrorTest();
		
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); OpenGL::ErrorTest(); OpenGL::ErrorTest();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); OpenGL::ErrorTest(); OpenGL::ErrorTest();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT); OpenGL::ErrorTest(); OpenGL::ErrorTest();

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glTexImage2D(
				GL_TEXTURE_2D, 
				0, // mip level = 0
				image->GetFormat() == Image::Format::RGBA ? GL_RGBA8 : GL_RGB, // internal format
				image->GetWidth(), // width
				image->GetHeight(), // height
				0, // border = 0
				(GLenum)image->GetFormat(), // format
				(GLenum)image->GetComponentType(), //GL_UNSIGNED_BYTE,
				image->GetData()
			);
			OpenGL::ErrorTest();

			delete image;
		}

		return texture;
	};

	auto image1 = loadTexture(PATH("Media/Images/image.png"));
	auto image2 = loadTexture(PATH("Media/Images/Tiles1_D.png"));

	Sprite::Init();

	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		if(GetAsyncKeyState(VK_UP))
		{
			auto sprite = new Sprite();
			sprite->pos = Sprite::vec2(rand() % (std::uint32_t)Sprite::screen.x, rand() % (std::uint32_t)Sprite::screen.y);
			sprite->size = Sprite::vec2(100.0f);
			sprite->texture = rand() % 2 ? image1 : image2;
			sprite->color.r = (rand() % 256) / 255.0f;
			sprite->color.g = (rand() % 256) / 255.0f;
			sprite->color.b = (rand() % 256) / 255.0f;
			sprite->color.a = (rand() % 256) / 255.0f;
		}
		if(GetAsyncKeyState(VK_DOWN))
		{
			if(Sprite::sprites.size() > 0)
			{
				auto sprite = Sprite::sprites[rand() % Sprite::sprites.size()];
				delete sprite;
			}
		}

		for(auto &sprite : Sprite::sprites)
		{
			sprite->ang += 5.0f;
		}

		Sprite::Render();

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
	catch(CGGD::OpenIL::Exception exception)
	{
		cout << "OpenIL exception:\n" << exception.GetText() << endl;
	}

	system("pause");
}