#pragma once


#include <string>

#include <Windows.h>


namespace CGGD
{
	namespace WinAPI
	{
		typedef DWORD			ErrorCode;
		typedef std::string		ErrorText;


		class Exception
		{
		protected:
			const ErrorText errorText;
		public:
			Exception(const ErrorCode& errorCode_);
			Exception(const ErrorText& errorText_);
		public:
			ErrorText GetText() const;
		};


		bool IsSuccessful(const ErrorCode& errorCode);
		ErrorText GetErrorText(const ErrorCode& errorCode);
		void ErrorTest() throw(...);
		void ErrorTest(const ErrorCode& errorCode) throw(...);
	}
}



