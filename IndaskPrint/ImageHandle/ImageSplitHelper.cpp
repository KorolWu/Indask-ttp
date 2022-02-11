#include "ImageDataHelper.h"
#include "ImageSplitHelper.h"

ImageSplitHelper::ImageSplitHelper()
    : m_cfg(nullptr)
    , m_dpiRatio(1)
    , m_phNozNum(1)
    , m_swatheBitCount(8)
    , m_realNozNum(1)
    , m_startNoz(0)
    , m_endNoz(0)
{
}

ImageSplitHelper::~ImageSplitHelper()
{
    m_cfg = nullptr;
}
bool ImageSplitHelper:: ClearFolder(const QString path, bool isCreate)
{
    QDir *folder = new QDir;
    isCreate = false;
    bool exist = folder->exists(QString(path));
    if(exist)
    {
        isCreate = true;
        return true;
    }
    else
    {
        //创建文件夹
        bool ok = folder->mkdir(QString(path));
        if(ok)
            return true;
        else
            return false;
    }
    return true;
}

int ImageSplitHelper::SetSplitCfg(const SwatheSplitCfg * cfg)
{
    float npi = 360;//喷头dpi       !!!                                                         !!!!!
    int needImgbit = 1;

    m_cfg = cfg;

    //获取喷头NPI及喷孔数
    m_phNozNum = 1024;//PHParams::GetPHBriefInfo(m_cfg->PHType, &npi, &needImgbit);           !!!!!

    m_swatheBitCount = 8;

    m_dpiRatio = int(0.5 + m_cfg->PrintDPI / npi);

    if (m_dpiRatio <= 0)
        return -1;//ERR_PB_INPUTERR;

    //校验起始喷头
    if ((m_cfg->EndNoz + 1) > m_phNozNum)
        m_endNoz = m_phNozNum - 1;
    else
        m_endNoz = m_cfg->EndNoz;

    if (m_endNoz < m_cfg->StartNoz)
        m_startNoz = m_endNoz;
    else
        m_startNoz = m_cfg->StartNoz;

    //实际有效的喷嘴数
    m_realNozNum = m_endNoz - m_startNoz + 1;

    if (m_realNozNum <= 0)
        return -2;//ERR_PB_INPUTERR;

    return -3;//ERR_PB_NOERR;
}

int ImageSplitHelper::SplitIntoSwatheInfoSet(const ImageData * data, PrintInfo ** printInfo)
{
    //根据配置进行图形分割
    ImageDataHelper * imgHlp = new ImageDataHelper(*data);

    if (imgHlp == nullptr)
        return -1;//ERR_PB_INPUTERR;

    int height = data->Height;
    int width = data->Width;

    int passNum = m_dpiRatio;

    int stepsNum = width / (m_realNozNum * m_dpiRatio) +
            (width % (m_realNozNum * m_dpiRatio) != 0 ? 1 : 0);

    //swathe图片信息                                                           4个字节对齐
    int rowBytes = ImageDataHelper::GetRowBytes(m_phNozNum, m_swatheBitCount, 4);

    //当前step时第一pass对应图像X起点
    int startWidthIndexPx = 0;
    int startPassIndexPx = 0;
    //图像的X方向索引
    int pxIndex = 0;
    //当前pass号
    int curNum = 0;
    //图像缓冲区
    unsigned char val = 0;
    //最后有效的pass个数
    int sur = (width - (stepsNum - 1)* (passNum * m_realNozNum));
    int lastValidPass = sur >= passNum ? passNum : (sur);

    //保存的文件路径
    char fileName[260];
    SwatheInfo ** swSet = nullptr;

    //如果需要保存图片先清理文件夹
    if (m_cfg->IsSave != 0)
    {
        if (!ClearFolder(m_cfg->SaveDir, true))
            goto labErr;
    }

    swSet = new SwatheInfo *[stepsNum *passNum];

    for (int stepIndex = 0; stepIndex < stepsNum; stepIndex++)//大步
    {
        //每一步开始的像素位
        startWidthIndexPx = (stepIndex * passNum * m_realNozNum);

        for (int passIndex = 0; passIndex < passNum; passIndex++)//Pass
        {
            //其余部分是已经超出图像边界
            if ((stepIndex + 1) >= stepsNum && (passIndex + 1) > lastValidPass)
                break;
            //每一pass开始的像素位置
            startPassIndexPx = startWidthIndexPx + passIndex * 1;
            curNum++;

            unsigned char * buff = new unsigned char[rowBytes *height];//buff宽度最好为4的整数倍

            /********************** 生成每pass的图像 *************************/

            for (int y = 0; y < height; y++)
            {
                //数据区起始位
                unsigned char * rowImage = imgHlp->GetRowAt(y);

                for (unsigned int x = 0; x < m_phNozNum; x++)
                {
                    //填充有效孔的空间
                    if (x >= m_startNoz && x <= m_endNoz)
                    {
                        //计算所在的像素位置
                        //(nozIndex - m_cfg->StartNoz)为相对于图像的位置
                        pxIndex = startPassIndexPx + (x - m_startNoz)* m_dpiRatio;

                        //如果超出就填入白色
                        if (pxIndex >= width)
                            val = 255;
                        else//获取数据
                            val = imgHlp->GetRowPx(rowImage, pxIndex);
                    }
                    else//起始与结束部分用白色填充
                    {
                        val = 255;//设置为白色
                    }

                    //填充数据（灰度级，数值越大，越黑）
                    buff[x + y * rowBytes] = val;
                }//x
            }//y

            //生成 SwatheInfo
            {
                SwatheInfo *sw = new SwatheInfo();
                sw->Width = m_phNozNum;
                sw->Height = height;
                //一个像素占用的比特数1,2,4，8bit
                sw->BitsPerPixel = m_swatheBitCount;//HS版只支持单色位图
                //图像缓冲
                sw->Data = buff;
                //数据长度（字节数）
                sw->Length = rowBytes * height;
                sw->PHType = m_cfg->PHType;

                swSet[passNum * stepIndex + passIndex] = sw;
            }

            //保存图像
            if (m_cfg->IsSave != 0)
            {
                //格式化时间
                QString path = QString("%1\\Spit__Step_%2__Pass_%3__Time_%4.png").arg( m_cfg->SaveDir).arg( stepIndex + 1).arg(passIndex + 1).arg(curNum);
                QImage image(buff, m_phNozNum, height,QImage::Format::Format_Indexed8);

                 QMatrix matrix;
                 matrix.rotate(270);
                 image = image.transformed(matrix);
                 image.save(path);
                //TiffHelper::Save2File(buff, m_phNozNum, height, m_swatheBitCount, fileName, false);
            }

        }//passIndex
    }//stepIndex

    *printInfo = new PrintInfo;
    (*printInfo)->SwatheCount = curNum;
    (*printInfo)->SwatheInfoSet = swSet;
    (*printInfo)->StepNum = stepsNum;
    (*printInfo)->PassNum = passNum;

    delete imgHlp; imgHlp = nullptr;
    return 0;//ERR_PB_NOERR;

labErr:
    delete imgHlp; imgHlp = nullptr;
    return -4;//ERR_PB_DELFILEFAILED;

}
