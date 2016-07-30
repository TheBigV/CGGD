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
			using Handle = ILuint;
			using Filename = std::string;
			using Size = std::size_t;
			using Data = void*;
		public:
			enum class ComponentType: GLenum
			{
				SInt8			= GL_BYTE,
				UInt8			= GL_UNSIGNED_BYTE,
				SInt16			= GL_SHORT,
				UInt16			= GL_UNSIGNED_SHORT,
				SInt32			= GL_INT,
				UInt32			= GL_UNSIGNED_INT,
				SFloat32		= GL_FLOAT,
				Data8			= GL_2_BYTES,
				Data16			= GL_3_BYTES,
				Data32			= GL_4_BYTES,
				SFloat64		= GL_DOUBLE,
				Byte			= SInt8,
				UByte			= UInt8,
				Short			= SInt16,
				UShort			= UInt16,
				Int				= SInt32,
				UInt			= UInt32,
				Float			= SFloat32,
				Double			= SFloat64
			};
			enum class Format: GLenum
			{
				RGBA				= GL_RGBA,
			};
			enum class Origin
			{
				LowerLeft,
				UpperLeft
			};
		public:
			static Image* Load2D(const Filename& filename) throw(...);
		protected:
			Size width;
			Size height;
			Size depth;
			Format format;
			ComponentType componentType;
			Size bytesPerPixel;
			Size bitsPerPixel;
			Size mipmapsCount;
			Origin originMode;
			Data data;
		protected:
			Image(
				const Size&				width_,
				const Size&				height_,
				const Size&				depth_,
				const Format&			format_,
				const ComponentType&	componentType_,
				const Size&				bytesPerPixel_,
				const Size&				bitsPerPixel_,
				const Size&				mipmapsCount_,
				const Origin&			originMode_,
				const Data&				data_
			);
		public:
			~Image();
		public:
			inline Size GetWidth() const
			{
				return width;
			}
			inline Size GetHeight() const
			{
				return height;
			}
			inline Size GetHepth() const
			{
				return depth;
			}
			inline Format GetFormat() const
			{
				return format;
			}
			inline ComponentType GetComponentType() const
			{
				return componentType;
			}
			inline Size GetBytesPerPixel() const
			{
				return bytesPerPixel;
			}
			inline Size GetPitsPerPixel() const
			{
				return bitsPerPixel;
			}
			inline Size GetMipmapsCount() const
			{
				return mipmapsCount;
			}
			inline Origin GetOriginMode() const
			{
				return originMode;
			}
			inline Data GetData() const
			{
				return data;
			}
		};
	}
}



