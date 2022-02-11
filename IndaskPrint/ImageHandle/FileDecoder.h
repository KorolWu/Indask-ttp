#pragma once
#include "../Common.h"

class FileDecoder
{
private:
	//0:未知  1：bmp  2：tiff
	int m_fileType;
	//图像文件路径
	Char * m_file;

	void * m_bmpDecoder;
	void * m_tiffDecoder;

public:
	FileDecoder(const Char * file);
	~FileDecoder();

public:
	//验证文件的有效性
	int CheckFileValidate();

	//解析文件
	//获取的内存data不需要释放，由FileDecoder自行处理
	int GetImageData(ImageData &data);

};

