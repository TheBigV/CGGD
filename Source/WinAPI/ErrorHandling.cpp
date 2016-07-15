#include "ErrorHandling.hpp"


CGGD::WinAPI::Exception::Exception(const ErrorCode& errorCode_):
	errorText(GetErrorText(errorCode_))
{
}
CGGD::WinAPI::Exception::Exception(const ErrorText& errorText_) :
	errorText(errorText_)
{
}
CGGD::WinAPI::ErrorText CGGD::WinAPI::Exception::GetText() const
{
	return errorText;
}


bool CGGD::WinAPI::IsSuccessful(const ErrorCode& errorCode)
{
	return errorCode == NO_ERROR;
}
CGGD::WinAPI::ErrorText CGGD::WinAPI::GetErrorText(const ErrorCode& errorCode)
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
void CGGD::WinAPI::ErrorTest()
{
	auto errorCode = GetLastError();

	ErrorTest(errorCode);
}
void CGGD::WinAPI::ErrorTest(const ErrorCode& errorCode)
{
	if(!IsSuccessful(errorCode))
	{
		throw WinAPI::Exception(errorCode);
	}
}







