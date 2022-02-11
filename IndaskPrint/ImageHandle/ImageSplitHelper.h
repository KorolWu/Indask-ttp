#pragma once

#include "../Common.h"
#include <QDir>
#include <QImage>

class ImageSplitHelper
{
private:
	const SwatheSplitCfg * m_cfg;

	int m_dpiRatio;
	int m_swatheBitCount;

	unsigned int m_phNozNum;
	unsigned int m_realNozNum;

	unsigned int m_startNoz;
	unsigned int m_endNoz;

public:
	ImageSplitHelper();
	~ImageSplitHelper();


public:

	//设置分割配置(添加了引用)
	int SetSplitCfg(const SwatheSplitCfg * cfg);

	//将图形分割到swatheinfo中
	int SplitIntoSwatheInfoSet(const ImageData * data, PrintInfo ** printInfo);

    bool ClearFolder(const QString path, bool isCreate);
};

