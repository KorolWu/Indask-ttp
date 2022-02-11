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
        //�����ļ���
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
    float npi = 360;//��ͷdpi       !!!                                                         !!!!!
    int needImgbit = 1;

    m_cfg = cfg;

    //��ȡ��ͷNPI�������
    m_phNozNum = 1024;//PHParams::GetPHBriefInfo(m_cfg->PHType, &npi, &needImgbit);           !!!!!

    m_swatheBitCount = 8;

    m_dpiRatio = int(0.5 + m_cfg->PrintDPI / npi);

    if (m_dpiRatio <= 0)
        return -1;//ERR_PB_INPUTERR;

    //У����ʼ��ͷ
    if ((m_cfg->EndNoz + 1) > m_phNozNum)
        m_endNoz = m_phNozNum - 1;
    else
        m_endNoz = m_cfg->EndNoz;

    if (m_endNoz < m_cfg->StartNoz)
        m_startNoz = m_endNoz;
    else
        m_startNoz = m_cfg->StartNoz;

    //ʵ����Ч��������
    m_realNozNum = m_endNoz - m_startNoz + 1;

    if (m_realNozNum <= 0)
        return -2;//ERR_PB_INPUTERR;

    return -3;//ERR_PB_NOERR;
}

int ImageSplitHelper::SplitIntoSwatheInfoSet(const ImageData * data, PrintInfo ** printInfo)
{
    //�������ý���ͼ�ηָ�
    ImageDataHelper * imgHlp = new ImageDataHelper(*data);

    if (imgHlp == nullptr)
        return -1;//ERR_PB_INPUTERR;

    int height = data->Height;
    int width = data->Width;

    int passNum = m_dpiRatio;

    int stepsNum = width / (m_realNozNum * m_dpiRatio) +
            (width % (m_realNozNum * m_dpiRatio) != 0 ? 1 : 0);

    //swatheͼƬ��Ϣ                                                           4���ֽڶ���
    int rowBytes = ImageDataHelper::GetRowBytes(m_phNozNum, m_swatheBitCount, 4);

    //��ǰstepʱ��һpass��Ӧͼ��X���
    int startWidthIndexPx = 0;
    int startPassIndexPx = 0;
    //ͼ���X��������
    int pxIndex = 0;
    //��ǰpass��
    int curNum = 0;
    //ͼ�񻺳���
    unsigned char val = 0;
    //�����Ч��pass����
    int sur = (width - (stepsNum - 1)* (passNum * m_realNozNum));
    int lastValidPass = sur >= passNum ? passNum : (sur);

    //������ļ�·��
    char fileName[260];
    SwatheInfo ** swSet = nullptr;

    //�����Ҫ����ͼƬ�������ļ���
    if (m_cfg->IsSave != 0)
    {
        if (!ClearFolder(m_cfg->SaveDir, true))
            goto labErr;
    }

    swSet = new SwatheInfo *[stepsNum *passNum];

    for (int stepIndex = 0; stepIndex < stepsNum; stepIndex++)//��
    {
        //ÿһ����ʼ������λ
        startWidthIndexPx = (stepIndex * passNum * m_realNozNum);

        for (int passIndex = 0; passIndex < passNum; passIndex++)//Pass
        {
            //���ಿ�����Ѿ�����ͼ��߽�
            if ((stepIndex + 1) >= stepsNum && (passIndex + 1) > lastValidPass)
                break;
            //ÿһpass��ʼ������λ��
            startPassIndexPx = startWidthIndexPx + passIndex * 1;
            curNum++;

            unsigned char * buff = new unsigned char[rowBytes *height];//buff������Ϊ4��������

            /********************** ����ÿpass��ͼ�� *************************/

            for (int y = 0; y < height; y++)
            {
                //��������ʼλ
                unsigned char * rowImage = imgHlp->GetRowAt(y);

                for (unsigned int x = 0; x < m_phNozNum; x++)
                {
                    //�����Ч�׵Ŀռ�
                    if (x >= m_startNoz && x <= m_endNoz)
                    {
                        //�������ڵ�����λ��
                        //(nozIndex - m_cfg->StartNoz)Ϊ�����ͼ���λ��
                        pxIndex = startPassIndexPx + (x - m_startNoz)* m_dpiRatio;

                        //��������������ɫ
                        if (pxIndex >= width)
                            val = 255;
                        else//��ȡ����
                            val = imgHlp->GetRowPx(rowImage, pxIndex);
                    }
                    else//��ʼ����������ð�ɫ���
                    {
                        val = 255;//����Ϊ��ɫ
                    }

                    //������ݣ��Ҷȼ�����ֵԽ��Խ�ڣ�
                    buff[x + y * rowBytes] = val;
                }//x
            }//y

            //���� SwatheInfo
            {
                SwatheInfo *sw = new SwatheInfo();
                sw->Width = m_phNozNum;
                sw->Height = height;
                //һ������ռ�õı�����1,2,4��8bit
                sw->BitsPerPixel = m_swatheBitCount;//HS��ֻ֧�ֵ�ɫλͼ
                //ͼ�񻺳�
                sw->Data = buff;
                //���ݳ��ȣ��ֽ�����
                sw->Length = rowBytes * height;
                sw->PHType = m_cfg->PHType;

                swSet[passNum * stepIndex + passIndex] = sw;
            }

            //����ͼ��
            if (m_cfg->IsSave != 0)
            {
                //��ʽ��ʱ��
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
