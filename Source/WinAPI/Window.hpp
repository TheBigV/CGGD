#pragma once


#include <string>

#include <Windows.h>


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
			const Handle handle;
		protected:
			Instance(Handle handle_);
		public:
			inline Handle GetHandle() const
			{
				return handle;
			}
		};
		class WindowClass
		{
		public:
			typedef std::string Name;
		protected:
			const Name name;
			Instance*const instance;
		public:
			WindowClass(Instance* instance_, const Name& name_);
			~WindowClass();
		};
	}
}