#include "ErrorHandling.hpp"


CGGD::OpenIL::Exception::Exception(const ErrorCode& errorCode_):
	errorText(GetErrorText(errorCode_))
{
}
CGGD::OpenIL::Exception::Exception(const ErrorText& errorText_) :
	errorText(errorText_)
{
}
CGGD::OpenIL::ErrorText CGGD::OpenIL::Exception::GetText() const
{
	return errorText;
}


bool CGGD::OpenIL::IsSuccessful(const ErrorCode& errorCode)
{
	return errorCode == IL_NO_ERROR;
}
CGGD::OpenIL::ErrorText CGGD::OpenIL::GetErrorText(const ErrorCode& errorCode)
{
	switch(errorCode)
	{
		case IL_INVALID_ENUM: return "IL_INVALID_ENUM";
		case IL_OUT_OF_MEMORY: return "IL_OUT_OF_MEMORY";
		case IL_FORMAT_NOT_SUPPORTED: return "IL_FORMAT_NOT_SUPPORTED";
		case IL_INVALID_VALUE: return "IL_INVALID_VALUE";
		case IL_ILLEGAL_OPERATION: return "IL_ILLEGAL_OPERATION";
		case IL_ILLEGAL_FILE_VALUE: return "IL_ILLEGAL_FILE_VALUE";
		case IL_INVALID_FILE_HEADER: return "IL_INVALID_FILE_HEADER";
		case IL_INVALID_PARAM: return "IL_INVALID_PARAM";
		case IL_COULD_NOT_OPEN_FILE: return "IL_COULD_NOT_OPEN_FILE";
		case IL_INVALID_EXTENSION: return "IL_INVALID_EXTENSION";
		case IL_FILE_ALREADY_EXISTS: return "IL_FILE_ALREADY_EXISTS";
		case IL_OUT_FORMAT_SAME: return "IL_OUT_FORMAT_SAME";
		case IL_STACK_OVERFLOW: return "IL_STACK_OVERFLOW";
		case IL_STACK_UNDERFLOW: return "IL_STACK_UNDERFLOW";
		case IL_INVALID_CONVERSION: return "IL_INVALID_CONVERSION";
		case IL_LIB_JPEG_ERROR: return "IL_LIB_JPEG_ERROR";
		case IL_LIB_PNG_ERROR: return "IL_LIB_PNG_ERROR";
		case IL_UNKNOWN_ERROR: return "IL_UNKNOWN_ERROR";
		case ILUT_NOT_SUPPORTED: return "ILUT_NOT_SUPPORTED";
	}
	throw Exception("Unknown error code");
}
void CGGD::OpenIL::ErrorTest()
{
	auto errorCode = ilGetError();

	ErrorTest(errorCode);
}
void CGGD::OpenIL::ErrorTest(const ErrorCode& errorCode)
{
	if(!IsSuccessful(errorCode))
	{
		throw OpenIL::Exception(errorCode);
	}
}







