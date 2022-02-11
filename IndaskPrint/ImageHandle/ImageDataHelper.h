#pragma once
#include "../Common.h"

class ImageDataHelper
{
protected:
	const ImageData & m_data;
	int m_bytesPerRow;
public:
	//data:
	ImageDataHelper(const ImageData & data);
	~ImageDataHelper();

public:
	//每行占用的字节数
	//alignBytes:1,4;
	static int GetRowBytes(int width, int bpp, int alignBytes);

	//获取每行的起始地址
	inline unsigned char * GetRowAt(int rowIndex);

	//获取像素值
	unsigned char GetPx(int x, int y);

	//获取像素值
	//该方式效率稍高，减少部分重复计算
	unsigned char GetRowPx(unsigned char * row, int x);

};


inline unsigned char * ImageDataHelper::GetRowAt(int rowIndex)
{
	if (m_data.YDir == 1)//从下往上存储
		return m_data.Data + (m_data.Height - 1 - rowIndex) * m_bytesPerRow;
	else//从上往下存储
		return m_data.Data + rowIndex * m_bytesPerRow;
}
