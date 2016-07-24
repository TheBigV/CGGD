#pragma region Include
#pragma once


#include "Header.hpp"
#include "ErrorHandling.hpp"
#pragma endregion


namespace CGGD
{
	namespace OpenIL
	{
		class Initer
		{
		private:
			static Initer initer;
		private:
			inline Initer()
			{
				if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION) throw Exception("Invalid IL version");
				if(iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION) throw Exception("Invalid ILU version");
				if(ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) throw Exception("Invalid ILUT version");

				ilInit();
				ErrorTest();
				iluInit();
				ErrorTest();
				ilutInit();
				ErrorTest();

				// ilEnable(IL_FILE_OVERWRITE);
				// ErrorTest();
				// ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
				// ErrorTest();
				// ilutRenderer(ILUT_OPENGL);
				// ErrorTest();
				// ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
				// ErrorTest();
				// ilutEnable(ILUT_OPENGL_CONV);
				// ErrorTest();
				// ilutEnable(ILUT_GL_USE_S3TC);
				// ErrorTest();
			}
		};

		class Image
		{
		public:
			using Filename = std::string;
			using Size = std::size_t;
		public:
			static Image* Load2D(const Filename& filename);
		protected:
			Size width;
			Size height;
			Size depth;
		protected:
			Image();
		public:
			~Image();
		};
	}
}



