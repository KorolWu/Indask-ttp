#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{

    m_bCreateDevice = false;
    m_bOpenDevice = false;
    m_bStartGrabbing = false;
    m_nTriggerMode = MV_TRIGGER_MODE_OFF;
    m_nTriggerSource = MV_TRIGGER_SOURCE_SOFTWARE;
    m_pcMyCamera = nullptr;

    m_pBufForDriver = nullptr;
    m_nBufSizeForDriver = 0;
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    m_width = 900;
    m_height = 600;
    this->resize(m_width,m_height);
    initUi();

    enumCamera();

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&CameraWidget::updateImage);
}

void CameraWidget::onOpenClicked()
{
    bool ret = openCamera();
    qDebug()<<ret;
    if(ret == true)
    {
        if(m_pcMyCamera != nullptr)
        {
            //m_pcMyCamera->RegisterImageCallBack(&MainWindow::cbOutput,nullptr);
           ret = m_pcMyCamera->StartGrabbing();
           if(ret == 0)
             m_timer->start(100);
           GetExposureTime();
           GetGain();
        }
    }
}

void CameraWidget::initUi()
{
    QHBoxLayout *hbox = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addStretch(1);
    m_srcImage = new QLabel();
    m_srcImage->setStyleSheet("background-color:black;");
    m_srcImage->move(5,3);
    m_srcImage->setFixedSize(560,420);  //图片的大小是4:3
    hbox->addWidget(m_srcImage);
    m_playout = new QHBoxLayout();
    m_playout->addLayout(hbox);


    QHBoxLayout *hbox1 = new QHBoxLayout();
    m_pDeveceList = new QComboBox();
    m_pDeveceList->setFixedSize(200,25);
    m_pOpenBtn = new QPushButton("Open");
    connect(m_pOpenBtn,&QPushButton::clicked,this,&CameraWidget::onOpenClicked);
    hbox1->addWidget(m_pDeveceList);
    hbox1->addWidget(m_pOpenBtn);
    vbox->addLayout(hbox1);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    QLabel *gain = new QLabel("Gain :");
    m_pGain = new QDoubleSpinBox();
    m_pGain->setMaximum(10000);
    hbox2->addWidget(gain);
    hbox2->addWidget(m_pGain);
    vbox->addLayout(hbox2);


    QHBoxLayout *hbox3 = new QHBoxLayout();
    QLabel *exposure = new QLabel("Exposure :");
    m_pExposure = new QDoubleSpinBox();
    m_pExposure->setMaximum(10000);
    hbox3->addWidget(exposure);
    hbox3->addWidget(m_pExposure);
    vbox->addLayout(hbox3);

    QHBoxLayout *hbox4 = new QHBoxLayout();
    m_pSetBtn = new QPushButton("Set");
    connect(m_pSetBtn,&QPushButton::clicked,this,&CameraWidget::onSetClicked);
    hbox4->addWidget(m_pSetBtn);
    vbox->addLayout(hbox4);

    //连续采集  保存图片
    hbox4 = new QHBoxLayout();
    m_pCheckBox = new QCheckBox("LianXu");
    m_pSaveBtn = new QPushButton("Save");
    hbox4->addWidget(m_pCheckBox);
    hbox4->addWidget(m_pSaveBtn);
    vbox->addLayout(hbox4);

    //x y 方向偏移
    hbox4 = new QHBoxLayout();
    QVBoxLayout *vbox_1 = new QVBoxLayout();
    QLabel *x_lab = new QLabel("Xoffect:");
    m_pXoffect = new QSpinBox();
    hbox4->addWidget(x_lab);
    hbox4->addWidget(m_pXoffect);
    vbox_1->addLayout(hbox4);

    hbox4 = new QHBoxLayout();
    QLabel *y_lab = new QLabel("Yoffect:");
    m_pYoffect = new QSpinBox();
    hbox4->addWidget(y_lab);
    hbox4->addWidget(m_pYoffect);
    vbox_1->addLayout(hbox4);

    hbox = new QHBoxLayout();
    m_pSetOffectBtn = new QPushButton("Set");
    hbox->addLayout(vbox_1);
    hbox->addWidget(m_pSetOffectBtn);

    vbox->addLayout(hbox);

    m_pYoffect->setMaximum(9999999);
    m_pXoffect->setMaximum(9999999);
    vbox->addStretch(3);
    m_playout->addLayout(vbox);
    this->setLayout(m_playout);
    this->setStyleSheet("QLabel{font: 18px;}QDoubleSpinBox{Padding-right:20px;Border:2px solid white;font:14px; Min-width:50px;Min-height:25px;border-radius:5px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:14px; Min-width:50px;Min-height:25px;border-radius:5px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 20px;}");

}

///
/// \brief CameraWidget::setGainAndExposure
/// \param gain      增益
/// \param exposure  曝光时间
/// \return
///
bool CameraWidget::setGainAndExposure(const float &gain, const float &exposure)
{
    int nRet = m_pcMyCamera->SetEnumValue("GainAuto", 0);

    nRet = m_pcMyCamera->SetFloatValue("Gain", (float)gain);
    if (MV_OK != nRet)
    {
        return false;
    }

    float  dfFloatValue = 0.0;

    //调节这两个曝光模式，才能让曝光时间生效 | en:Set exposure mode to valid exposure time
    nRet = m_pcMyCamera->SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED);
    if (MV_OK != nRet)
    {
        return false;
    }

    nRet = m_pcMyCamera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    nRet = m_pcMyCamera->SetFloatValue("ExposureTime", (float)exposure);
    if (MV_OK != nRet)
    {
        return false;
    }

    return true;

}

void CameraWidget::onSetClicked()
{
    double gain,exposure;
    gain = m_pGain->value();
    exposure = m_pExposure->value();
    setGainAndExposure(gain,exposure);
}

bool CameraWidget::GetExposureTime()
{
    float  fFloatValue = 0.0;
    int nRet = m_pcMyCamera->GetFloatValue("ExposureTime", &fFloatValue);
    if (MV_OK != nRet)
    {
        return false;
    }
    m_pExposure->setValue((double)fFloatValue);

    return true;
}

bool CameraWidget::GetGain()
{
    float  fFloatValue = 0.0;

    int nRet = m_pcMyCamera->GetFloatValue("Gain", &fFloatValue);
    if (MV_OK != nRet)
    {
        return false;
    }
    m_pGain->setValue((double)fFloatValue);

    return true;
}

bool CameraWidget::openCamera()
{
    if (true == m_bOpenDevice)
    {
        return false;
    }

    if(true == m_bCreateDevice)
    {
        return false;
    }
    int nIndex = m_pDeveceList->currentIndex();// DeviceList->ItemIndex;
    if ((nIndex < 0) | (nIndex >= MV_MAX_DEVICE_NUM))
    {
        qDebug()<<("Please select device");
        return false;
    }

    // 由设备信息创建设备实例 | en:Create device instance from device information
    if (nullptr == m_stDevList.pDeviceInfo[nIndex])
    {
        qDebug()<<("Device does noe exist");
        return false;
    }

    if (nullptr != m_pcMyCamera)
    {
        return false;
    }

    m_pcMyCamera = new CMyCamera;
    if (nullptr == m_pcMyCamera)
    {
        return false;
    }

    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);
    //创建设备失败 | en:Create device fail
    if (MV_OK != nRet)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = nullptr;
        //m_bRetStatus = STATUS_ERROR;
        return false;
    }

    m_bCreateDevice = true;
    m_bOpenDevice = true;
    return true;
}

bool CameraWidget::closeCamera()
{
    if (m_pcMyCamera)
    {
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
    }

    if (m_pBufForDriver)
    {
        free(m_pBufForDriver);
        m_pBufForDriver = NULL;
    }
    m_nBufSizeForDriver = 0;

    m_bOpenDevice = false;
    m_bStartGrabbing = false;
    m_bCreateDevice = false;

    return true;
}

bool CameraWidget::enumCamera()
{
    //m_bRetStatus = STATUS_OK;

    // 1. 清除设备列表框中的信息 | en:Clear information in device list
    //ui->comboBox->Clear();

    // 2. 初始化设备信息列表 | en:Initial device information list
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // 3. 枚举子网内所有设备 | en:Enumerate all device under subnet
    int nRet = CMyCamera::EnumDevices(&m_stDevList);
    if (MV_OK != nRet)
    {
        return false;
    }
    //将值加入到信息列表框中并显示出来 | en:Add result to information list and display
    unsigned int i;
    int nIp1, nIp2, nIp3, nIp4;
    for (i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
        if (nullptr == pDeviceInfo)
        {
            continue;
        }
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

            char strUserName[256] = {0};
            char strDisplayName[256] = {0};
            if (strcmp("", (char*)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
            {
                memcpy(strUserName, pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName,
                       sizeof(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));
            }
            else
            {
                sprintf_s(strUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
                          pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
                          pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
            }
            sprintf_s(strDisplayName, 256, "[%d]GigE:    %s  (%d.%d.%d.%d)",i,
                      strUserName, nIp1, nIp2, nIp3, nIp4);
            QString strDeviceName =  strDisplayName;
            m_pDeveceList->addItem(strDeviceName);//->AddItem(strDeviceName, NULL);
        }

        else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            char strUserName[256] = {0};
            char strDisplayName[256] = {0};
            if (strcmp("", (char*)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName)) != 0)
            {
                memcpy(strUserName, pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName,
                       sizeof(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName));
            }
            else
            {
                sprintf_s(strUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
                          pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName,
                          pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
            }

            sprintf_s(strDisplayName, 256, "[%d]UsbV3:  %s", i, strUserName);
            QString strDeviceName =  strDisplayName;
            m_pDeveceList->addItem(strDeviceName, NULL);
        }
        else
        {
        }
    }

    if (0 == m_stDevList.nDeviceNum)
    {
        qDebug("No device");
        return false;
    }

    m_pOpenBtn->setEnabled(true);
    //可以点击打开按钮了

    return true;
}

void CameraWidget::updateImage()
{
    if(m_pcMyCamera != nullptr)
    {
        if (false == m_bStartGrabbing)
        {
            //qDebug()<< STATUS_ERROR;
            //return;
        }

        // 获取1张图 | en:get one frame
        unsigned int nRecvBufSize = 0;
        int nRet = MV_OK;

        // ch:仅在第一次保存图像时申请缓存，在 CloseDevice 时释放
        // en:Request buffer only when first time saving image, release after CloseDevice
        if (nullptr == m_pBufForDriver)
        {
            // 从相机中获取一帧图像大小 | en:Get one frame size from camera
            nRet = m_pcMyCamera->GetIntValue("PayloadSize", &nRecvBufSize);
            if (nRet != MV_OK)
            {
                qDebug()<<("failed in get PayloadSize");

                return;
            }

            m_nBufSizeForDriver = nRecvBufSize;  // ch:一帧数据大小
            //en:One frame data size

            m_pBufForDriver = (unsigned char *)malloc(m_nBufSizeForDriver);
            if (nullptr == m_pBufForDriver)
            {
                qDebug()<<("malloc fail");
                return;
            }
        }

        MV_FRAME_OUT_INFO_EX stImageInfo = {0};
        memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
        unsigned int nDataLen = 0;


        nRet = m_pcMyCamera->GetOneFrameTimeout(m_pBufForDriver, &nDataLen, m_nBufSizeForDriver, &stImageInfo, 1000);
        qDebug()<<"getOneFrameTimeout;"<<nRet;
        if(nRet == 0 && m_pBufForDriver != nullptr)
        {

            //coutomer image data height and width becarful,maybe crash when waring width or height
            QImage image(m_pBufForDriver,stImageInfo.nWidth,stImageInfo.nHeight,QImage::Format_Grayscale8);
            QImage reImage;
            reImage = image.scaled(m_srcImage->width(),m_srcImage->height());
            QPixmap pixmap = QPixmap::fromImage(reImage);
            m_srcImage->setPixmap(pixmap);
            qDebug()<<"111111";

            // delete m_pBufForDriver; m_pBufForDriver = nullptr;
        }

    }
}
