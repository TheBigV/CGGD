#pragma once


#include <string>

#include <Windows.h>

#include "ErrorHandling.hpp"


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
		typedef std::string Name;
	protected:
		WindowClass*const windowClass;
		const Name name;
		HWND handle;
	public:
		Window(WindowClass* windowClass_, const Name& name_);
		~Window();
	public:
		Name GetName() const;
		void Loop() const;
	};
}



