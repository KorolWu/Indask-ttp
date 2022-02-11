#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QCheckBox>
#include "MvCameraControl.h"
#include "MyCamera.h"

///
/// \brief The CameraWidget class 用来显示相机取像，和参数设置的一个界面
///
class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = nullptr);

signals:

public slots:
private:


    /*状态*/
    bool  m_bRetStatus;                         //表示函数返回状态
    bool  m_bCreateDevice;                      //是否创建设备
    bool  m_bOpenDevice;                        //是否打开设备
    bool  m_bStartGrabbing;                     //是否开始抓图
    int   m_nTriggerMode;                       //触发模式
    int   m_nTriggerSource;                     //触发源
    int m_width, m_height;
    /*设备相关*/
    CMyCamera*      m_pcMyCamera;               //CMyCamera封装了常用接口
    MV_CC_DEVICE_INFO_LIST m_stDevList;         //设备信息列表结构体变量，用来存储设备列表
    unsigned char*  m_pBufForDriver;            // 用于从驱动获取图像的缓存
    unsigned int    m_nBufSizeForDriver;
    //image src
    QLabel* m_srcImage;

    QTimer *m_timer;

    //用来枚举检索到的相机
    QComboBox *m_pDeveceList;

    QPushButton *m_pOpenBtn; //打开相机
    void onOpenClicked();

    QDoubleSpinBox *m_pGain;   // 增益
    QDoubleSpinBox *m_pExposure; //曝光时间

    QPushButton *m_pSetBtn;

    QHBoxLayout *m_playout;

    QCheckBox *m_pCheckBox;//是否连续采集
    QPushButton *m_pSaveBtn;

    //x y方向上的偏移
    QSpinBox *m_pXoffect;
    QSpinBox *m_pYoffect;
    QPushButton *m_pSetOffectBtn;

    //不提供触发源的设置，默认都是软触发没有io触发
    void initUi();

    //设置曝光时间 & 增益
    bool setGainAndExposure(const float &gain, const float &exposure);
    void onSetClicked();
    bool  GetExposureTime();
    bool  GetGain();
    bool openCamera();
    bool closeCamera();
    bool enumCamera();
    void updateImage();
};

#endif // CAMERAWIDGET_H
