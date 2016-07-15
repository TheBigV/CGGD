#include "ErrorHandling.hpp"


CGGD::OpenGL::Exception::Exception(const ErrorCode& errorCode_):
	errorText(GetErrorText(errorCode_))
{
}
CGGD::OpenGL::Exception::Exception(const ErrorText& errorText_) :
	errorText(errorText_)
{
}
CGGD::OpenGL::ErrorText CGGD::OpenGL::Exception::GetText() const
{
	return errorText;
}


bool CGGD::OpenGL::IsSuccessful(const ErrorCode& errorCode)
{
	return errorCode == GL_NO_ERROR;
}
CGGD::OpenGL::ErrorText CGGD::OpenGL::GetErrorText(const ErrorCode& errorCode)
{
	switch(errorCode)
	{
		case GL_INVALID_OPERATION: return "INVALID_OPERATION";
		case GL_INVALID_ENUM: return "INVALID_ENUM";
		case GL_INVALID_VALUE: return "INVALID_VALUE";
		case GL_OUT_OF_MEMORY: return "OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
	}

	throw Exception("Unknown error code");
}
void CGGD::OpenGL::ErrorTest()
{
	auto errorCode = glGetError();

	ErrorTest(errorCode);
}
void CGGD::OpenGL::ErrorTest(const ErrorCode& errorCode)
{
	if(!IsSuccessful(errorCode))
	{
		throw OpenGL::Exception(errorCode);
	}
}







