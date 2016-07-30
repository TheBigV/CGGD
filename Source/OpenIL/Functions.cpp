#include "Functions.hpp"


CGGD::OpenIL::Initer CGGD::OpenIL::Initer::initer;


CGGD::OpenIL::Image* CGGD::OpenIL::Image::Load2D(const Filename& filename)
{
	Handle handle = ilGenImage(); ErrorTest();
	ilBindImage(handle); ErrorTest();

	if(ilLoadImage(filename.c_str()))
	{
		ErrorTest();

		auto ilWidth = ilGetInteger(IL_IMAGE_WIDTH);
		auto ilHeight = ilGetInteger(IL_IMAGE_HEIGHT);
		auto ilDepth = ilGetInteger(IL_IMAGE_DEPTH);
		auto ilFormat = ilGetInteger(IL_IMAGE_FORMAT); // GL_RGBA
		auto ilType = ilGetInteger(IL_IMAGE_TYPE);
		auto ilBytes = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		auto ilBits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		auto ilMipmap = ilGetInteger(IL_NUM_MIPMAPS);
		auto ilOriginMode = ilGetInteger(IL_IMAGE_ORIGIN);	// IL_ORIGIN_LOWER_LEFT, IL_ORIGIN_UPPER_LEFT
		auto ilData = ilGetData();

		Size width = ilWidth > 0 ? ilWidth :
			throw Exception("Invalid width: " + std::to_string(ilWidth));

		Size height = ilHeight > 0 ? ilHeight :
			throw Exception("Invalid height: " + std::to_string(ilHeight));

		Size depth = ilDepth > 0 ? ilDepth :
			throw Exception("Invalid depth: " + std::to_string(ilDepth));

		Format format = (Format)ilFormat;
		{
			switch(format)
			{
				case CGGD::OpenIL::Image::Format::RGBA:
					break;
				default:
					throw Exception("Invalid component format: " + (decltype(ilFormat))format);
			}
		}

		ComponentType componentType = (ComponentType)ilType;
		{
			switch(componentType)
			{
				case CGGD::OpenIL::Image::ComponentType::SInt8:
				case CGGD::OpenIL::Image::ComponentType::UInt8:
				case CGGD::OpenIL::Image::ComponentType::SInt16:
				case CGGD::OpenIL::Image::ComponentType::UInt16:
				case CGGD::OpenIL::Image::ComponentType::SInt32:
				case CGGD::OpenIL::Image::ComponentType::UInt32:
				case CGGD::OpenIL::Image::ComponentType::SFloat32:
				case CGGD::OpenIL::Image::ComponentType::Data8:
				case CGGD::OpenIL::Image::ComponentType::Data16:
				case CGGD::OpenIL::Image::ComponentType::Data32:
				case CGGD::OpenIL::Image::ComponentType::SFloat64:
					break;
				default:
					throw Exception("Invalid component type: " + (decltype(ilType))componentType);
			}
		}

		Size bytesPerPixel = ilBytes >= 1 ? ilBytes :
			throw Exception("Invalid bytes per pixel: " + std::to_string(ilBytes));

		Size bitsPerPixel = ilBits >= 1 ? ilBits :
			throw Exception("Invalid bits per pixel: " + std::to_string(ilBits));

		Size mipmapsCount = ilMipmap >= 0 ? ilMipmap :
			throw Exception("Invalid mipmaps count: " + std::to_string(ilMipmap));

		Origin originMode = ilOriginMode == IL_ORIGIN_LOWER_LEFT ? Origin::LowerLeft :
			ilOriginMode == IL_ORIGIN_UPPER_LEFT ? Origin::UpperLeft :
			throw Exception("Invalid origin mode: " + std::to_string(ilOriginMode));

		Data data = ilData != nullptr ? ilData :
			throw Exception("Invalid data(null)");

		auto image = new Image(
			width,
			height,
			depth,
			format,
			componentType,
			bytesPerPixel,
			bitsPerPixel,
			mipmapsCount,
			originMode,
			data
		);

		try
		{
			ilDeleteImage(handle);
			ErrorTest();
		}
		catch(...)
		{
			delete image;

			throw;
		}

		return image;
	}
	else
	{
		ErrorTest();
	}

	ilDeleteImage(handle);
	ErrorTest();

	return nullptr;
}
CGGD::OpenIL::Image::Image(
	const Size& width_,
	const Size& height_,
	const Size& depth_,
	const Format& format_,
	const ComponentType& componentType_,
	const Size& bytesPerPixel_,
	const Size& bitsPerPixel_,
	const Size& mipmapsCount_,
	const Origin& originMode_,
	const Data& data_
):
	width(width_),
	height(height_),
	depth(depth_),
	format(format_),
	componentType(componentType_),
	bytesPerPixel(bytesPerPixel_),
	bitsPerPixel(bitsPerPixel_),
	mipmapsCount(mipmapsCount_),
	originMode(originMode_),
	data(malloc(bytesPerPixel*width*height*depth))
{
	memcpy(data, data_, bytesPerPixel*width*height*depth);
}
CGGD::OpenIL::Image::~Image()
{
	free(data);
}


