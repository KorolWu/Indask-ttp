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
	//ÿ��ռ�õ��ֽ���
	//alignBytes:1,4;
	static int GetRowBytes(int width, int bpp, int alignBytes);

	//��ȡÿ�е���ʼ��ַ
	inline unsigned char * GetRowAt(int rowIndex);

	//��ȡ����ֵ
	unsigned char GetPx(int x, int y);

	//��ȡ����ֵ
	//�÷�ʽЧ���Ըߣ����ٲ����ظ�����
	unsigned char GetRowPx(unsigned char * row, int x);

};


inline unsigned char * ImageDataHelper::GetRowAt(int rowIndex)
{
	if (m_data.YDir == 1)//�������ϴ洢
		return m_data.Data + (m_data.Height - 1 - rowIndex) * m_bytesPerRow;
	else//�������´洢
		return m_data.Data + rowIndex * m_bytesPerRow;
}
