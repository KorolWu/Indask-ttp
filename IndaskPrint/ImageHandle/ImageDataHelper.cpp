#include "ImageDataHelper.h"

//每行字节数
//1字节对齐
#define BYTESPERROW1(nw, nBpp) (((nw * nBpp) + 7) >> 3)
//4字节对齐
#define	BYTESPERROW4(nw, nBpp) ((((nw * nBpp) + 31) >> 5) << 2)

ImageDataHelper::ImageDataHelper(const ImageData & data)
	:m_data(data)
{
	m_bytesPerRow = GetRowBytes(m_data.Width, m_data.BitsPerPixel, m_data.AlignBytes);
}

ImageDataHelper::~ImageDataHelper()
{
}

int ImageDataHelper::GetRowBytes(int width, int bpp, int alignBytes)
{
	if (alignBytes == 4)
		return  BYTESPERROW4(width, bpp);
	else if (alignBytes == 1)
		return  BYTESPERROW1(width, bpp);
	else
		return 0;
}

unsigned char ImageDataHelper::GetPx(int x, int y)
{
	//数据区起始位
	unsigned char * rowImage = this->GetRowAt(y);

	//获取数据
	return GetRowPx(rowImage, x);
}

unsigned char ImageDataHelper::GetRowPx(unsigned char * rowImage, int x)
{
	//获取数据
	if (m_data.BitsPerPixel == 1)
	{
		//对应字节数据
		unsigned char pxs = (*(rowImage + (x >> 3)) >> (7 - x % 8)) & 0x01;
		return (pxs == m_data.BlackIndexVal) ? 0 : 255;
	}
	else // 8bit
	{
		//查看颜色是否反转了
		if (m_data.BlackIndexVal == 0)//没反转
			return  *(rowImage + x);
		else//颜色被反转了
			return  255 - (*(rowImage + x));
	}
}
