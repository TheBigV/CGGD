#include "ErrorHandling.hpp"


WinAPI::Exception::Exception(const ErrorCode& errorCode_):
	errorText(GetErrorText(errorCode_))
{
}
WinAPI::Exception::Exception(const ErrorText& errorText_):
	errorText(errorText_)
{
}
WinAPI::ErrorText WinAPI::Exception::GetText() const
{
	return errorText;
}


bool WinAPI::IsSuccessful(const ErrorCode& errorCode)
{
	return errorCode == NO_ERROR;
}
void WinAPI::Assert(const ErrorCode& errorCode)
{
	if(!IsSuccessful(errorCode))
	{
		throw WinAPI::Exception(errorCode);
	}
}
WinAPI::ErrorText WinAPI::GetErrorText(const ErrorCode& errorCode)
{
	LPSTR messageBuffer = nullptr;

	auto messageSize = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
		(LPSTR)&messageBuffer,
		0,
		NULL
	);

	ErrorText errorText(messageBuffer, messageSize);

	LocalFree(messageBuffer);

	return errorText;
}
void WinAPI::ErrorTest() throw(...)
{
	auto errorCode = GetLastError();

	if(!IsSuccessful(errorCode))
	{
		throw Exception(errorCode);
	}
}







