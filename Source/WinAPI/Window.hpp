#pragma once


#include <string>

#include <Windows.h>

#include "ErrorHandling.hpp"


namespace CGGD
{
	namespace WinAPI
	{
		class Instance
		{
		public:
			typedef HINSTANCE Handle;
		public:
			static Instance* Get();
		protected:
			const HINSTANCE handle;
		protected:
			Instance(HINSTANCE handle_);
		public:
			Handle GetHangle() const;
		};

		class WindowClass
		{
		public:
			typedef std::string Name;
		protected:
			Instance*const instance;
			const Name name;
		public:
			WindowClass(Instance* instance_, const Name& name_);
			~WindowClass();
		public:
			Instance* GetInstance() const;
			Name GetName() const;
		};

		class Window
		{
		public:
			typedef HWND Handle;
			typedef std::string Name;
		protected:
			WindowClass*const windowClass;
			const Name name;
			const Handle handle;
		public:
			Window(WindowClass* windowClass_, const Name& name_);
			~Window();
		public:
			Name GetName() const;
			Handle GetHandle() const;
			void Loop() const;
		};

		class DeviceContext
		{
		public:
			typedef HDC Handle;
		protected:
			Window*const window;
			const Handle handle;
		public:
			DeviceContext(Window* window_);
		public:
			Window* GetWindow() const;
			Handle GetHandle() const;
		public:
			void SetPixelFormat();
		public:
			void SwapBuffers() const;
		};
	}
}



