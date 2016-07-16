#pragma region Include
#pragma once


#include <string>

#include <WinAPI/ErrorHandling.hpp>
#include <WinAPI/Window.hpp>

#include "ErrorHandling.hpp"
#include "Functions.hpp"
#pragma endregion


namespace CGGD
{
	namespace OpenGL
	{
		namespace WinAPI
		{
			class RenderContext
			{
			public:
				using DeviceContext = CGGD::WinAPI::DeviceContext;
				using Handle = HGLRC;
			public:
				static void Reset();
			protected:
				DeviceContext*const deviceContext;
				const Handle handle;
			public:
				RenderContext(DeviceContext* deviceContext_);
				~RenderContext();
			public:
				inline Handle GetHandle() const
				{
					return handle;
				}
			public:
				void Set();
			};
			class RenderContextExtended
			{
			public:
				using DeviceContext = CGGD::WinAPI::DeviceContext;
			private:
				class Initer
				{
				public:
					Initer();
				};
			private:
				static const Initer initer;
				static const GLint attribs[];
			public:
				static void Reset();
			public:
				using Handle = HGLRC;
			protected:
				const DeviceContext* deviceContext;
				const Handle handle;
			public:
				RenderContextExtended(DeviceContext* deviceContext_);
				~RenderContextExtended();
			public:
				void Set();
			};
		}
	}
}



