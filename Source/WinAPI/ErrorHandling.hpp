#pragma once


#include <string>

#include <Windows.h>


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
	void Assert(const ErrorCode& errorCode) throw(...);
	ErrorText GetErrorText(const ErrorCode& errorCode);
	void ErrorTest() throw(...);
}



