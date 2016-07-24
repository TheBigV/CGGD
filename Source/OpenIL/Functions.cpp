#include "Functions.hpp"


CGGD::OpenIL::Initer CGGD::OpenIL::Initer::initer;


CGGD::OpenIL::Image* CGGD::OpenIL::Image::Load2D(const Filename& filename)
{
	auto image = ilGenImage();
	ErrorTest();
	ilBindImage(image);
	ErrorTest();

	if(IsSuccessful(ilLoadImage(filename.c_str())))
	{
		ErrorTest();

		auto width = ilGetInteger(IL_IMAGE_WIDTH);
		auto height = ilGetInteger(IL_IMAGE_HEIGHT);
		auto depth = ilGetInteger(IL_IMAGE_DEPTH);

		auto inILIFormat = ilGetInteger(IL_IMAGE_BPP);
		auto inILType = ilGetInteger(IL_IMAGE_TYPE);
		auto inILFormat = ilGetInteger(IL_IMAGE_FORMAT);
		auto inILBytes = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		auto inILBits = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		auto ilMipmap = ilGetInteger(IL_NUM_MIPMAPS);
		auto ilOriginMode = ilGetInteger(IL_IMAGE_ORIGIN);	// IL_ORIGIN_LOWER_LEFT, IL_ORIGIN_UPPER_LEFT

		if(ilOriginMode != IL_ORIGIN_LOWER_LEFT)
		{
			iluFlipImage();
		}

		auto inILData = ilGetData();
	}
	else
	{
		ErrorTest();
	}

	ilDeleteImage(image);
	ErrorTest();

	return nullptr;
}
CGGD::OpenIL::Image::Image()
{

}
CGGD::OpenIL::Image::~Image()
{

}


