#pragma once
#include "../Common.h"

class FileDecoder
{
private:
	//0:δ֪  1��bmp  2��tiff
	int m_fileType;
	//ͼ���ļ�·��
	Char * m_file;

	void * m_bmpDecoder;
	void * m_tiffDecoder;

public:
	FileDecoder(const Char * file);
	~FileDecoder();

public:
	//��֤�ļ�����Ч��
	int CheckFileValidate();

	//�����ļ�
	//��ȡ���ڴ�data����Ҫ�ͷţ���FileDecoder���д���
	int GetImageData(ImageData &data);

};

