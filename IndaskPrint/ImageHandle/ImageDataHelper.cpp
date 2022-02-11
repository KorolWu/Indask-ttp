#include "ImageDataHelper.h"

//ÿ���ֽ���
//1�ֽڶ���
#define BYTESPERROW1(nw, nBpp) (((nw * nBpp) + 7) >> 3)
//4�ֽڶ���
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
	//��������ʼλ
	unsigned char * rowImage = this->GetRowAt(y);

	//��ȡ����
	return GetRowPx(rowImage, x);
}

unsigned char ImageDataHelper::GetRowPx(unsigned char * rowImage, int x)
{
	//��ȡ����
	if (m_data.BitsPerPixel == 1)
	{
		//��Ӧ�ֽ�����
		unsigned char pxs = (*(rowImage + (x >> 3)) >> (7 - x % 8)) & 0x01;
		return (pxs == m_data.BlackIndexVal) ? 0 : 255;
	}
	else // 8bit
	{
		//�鿴��ɫ�Ƿ�ת��
		if (m_data.BlackIndexVal == 0)//û��ת
			return  *(rowImage + x);
		else//��ɫ����ת��
			return  255 - (*(rowImage + x));
	}
}
