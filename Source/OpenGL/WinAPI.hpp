#pragma region Include
#pragma once


#include <string>

#include <WinAPI/ErrorHandling.hpp>
#include <WinAPI/Window.hpp>

#include "ErrorHandling.hpp"
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
				typedef CGGD::WinAPI::DeviceContext DeviceContext;
				typedef HGLRC Handle;
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
				inline void Set()
				{
					if(!wglMakeCurrent(deviceContext->GetHandle(), handle))
					{
						ErrorTest();
						CGGD::WinAPI::ErrorTest();
					}
				}
			};
		}
	}
}



