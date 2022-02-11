#include "../stdafx.h"
#include "FileDecoder.h"
using namespace std;


#define m_bmpHlp ((System::Drawing::Bitmap *)m_bmpDecoder)
#define m_tiffHlp ((TiffHelper *)m_tiffDecoder)

FileDecoder::FileDecoder(const Char * file)
	: m_file(nullptr)
	, m_fileType(0)
	, m_bmpDecoder(nullptr)
	, m_tiffDecoder(nullptr)
{
	size_t slen = 0;

	if (file == nullptr)
		return;

	slen = Strlen(file);
	if (slen != 0)
	{
		m_file = new Char[slen + 1];
		Strcpy_s(m_file, slen + 1, file);
	}
}

FileDecoder::~FileDecoder()
{
	if (m_file != nullptr)
	{
		delete [] m_file;
		m_file = nullptr;
	}

	if (m_bmpDecoder != nullptr)
	{
		delete m_bmpHlp; m_bmpDecoder = nullptr;
	}

	if (m_tiffDecoder != nullptr)
	{
		delete m_tiffHlp; m_tiffDecoder = nullptr;
	}
}

int FileDecoder::CheckFileValidate()
{
	if (m_file == nullptr)
		return ERR_PB_INVALIDFILENAME;

	//检查文件格式是否支持
	int index = System::Text::StringHelper::LastIndexOf(m_file, _T('.'));

	//是否为bmp和tiff格式
	if (index == -1)
		return ERR_PB_INVALIDFILENAME;

	const Char * tmp = &m_file[index + 1];

	//比较扩展名
	if (Strcmp(tmp, _T("bmp")) == 0)
		m_fileType = 1;
	else if (Strcmp(tmp, _T("tiff")) == 0 || Strcmp(tmp, _T("tif")) == 0)
		m_fileType = 2;
	else
		m_fileType = 0;

	if (m_fileType == 0)
		return ERR_PB_UNSUPIMGFORMAT;

	//检查文件是否存在
	if (!System::IO::File::Exists(m_file))
		return ERR_PB_FILENOTEXIST;

	if (m_fileType == 1)//bmp
	{
		m_bmpDecoder = new System::Drawing::Bitmap();
		if (!m_bmpHlp->LoadFromFile(m_file))
			return ERR_PB_LOADFILEFAILED;
	}
	else//2 tiff
	{
		m_tiffDecoder = new TiffHelper(m_file);
		if (!m_tiffHlp->ReadFile())
			return ERR_PB_LOADFILEFAILED;
	}

	return ERR_PB_NOERR;
}

int FileDecoder::GetImageData(ImageData &data)
{
	if (m_fileType == 1)//bmp
	{
		data.Width = m_bmpHlp->Width();
		data.Height = m_bmpHlp->Height();

		data.BitsPerPixel = m_bmpHlp->GetBitCount();
		data.Data = m_bmpHlp->GetRawData();


		data.AlignBytes = 4;//bmp为四字节对齐
		data.YDir = 1;

		if (data.BitsPerPixel <= 8)
		{
			//判断颜色表数据
			RGBQUAD & palette = *m_bmpHlp->GetPalette().Palette;

			//颜色表信息不对
			if (m_bmpHlp->GetPalette().Count <= 0)
				return ERR_PB_UNSUPIMGFORMAT;

			//判断单色位图的第一个颜色表是否为黑色
			if (palette.rgbBlue == 0
				&& palette.rgbGreen == 0
				&& palette.rgbRed == 0)
			{
				data.BlackIndexVal = 0;
			}
			else
			{
				data.BlackIndexVal = 1;
			}
		}
		else
		{
			data.BlackIndexVal = 0;
		}
	}
	else if (m_fileType == 2)
	{
		data.Width = m_tiffHlp->Width();
		data.Height = m_tiffHlp->Height();

		data.BitsPerPixel = m_tiffHlp->GetBitCount();
		data.Data = m_tiffHlp->GetRawData();


		data.AlignBytes = 1;//tiff为1字节对齐
		data.YDir = 0;

		data.BlackIndexVal = m_tiffHlp->IsWhiteSmall() ? 1 : 0;
	}
	else
	{
		return ERR_PB_UNSUPIMGFORMAT;
	}

	//只支持单色及8bit图
	if (data.BitsPerPixel != 8 && data.BitsPerPixel != 1)
		return ERR_PB_UNSUPIMGFORMAT;

	return ERR_PB_NOERR;
}
