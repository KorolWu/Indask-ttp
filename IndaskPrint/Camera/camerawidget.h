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
/// \brief The CameraWidget class ������ʾ���ȡ�񣬺Ͳ������õ�һ������
///
class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = nullptr);

signals:

public slots:
private:


    /*״̬*/
    bool  m_bRetStatus;                         //��ʾ��������״̬
    bool  m_bCreateDevice;                      //�Ƿ񴴽��豸
    bool  m_bOpenDevice;                        //�Ƿ���豸
    bool  m_bStartGrabbing;                     //�Ƿ�ʼץͼ
    int   m_nTriggerMode;                       //����ģʽ
    int   m_nTriggerSource;                     //����Դ
    int m_width, m_height;
    /*�豸���*/
    CMyCamera*      m_pcMyCamera;               //CMyCamera��װ�˳��ýӿ�
    MV_CC_DEVICE_INFO_LIST m_stDevList;         //�豸��Ϣ�б�ṹ������������洢�豸�б�
    unsigned char*  m_pBufForDriver;            // ���ڴ�������ȡͼ��Ļ���
    unsigned int    m_nBufSizeForDriver;
    //image src
    QLabel* m_srcImage;

    QTimer *m_timer;

    //����ö�ټ����������
    QComboBox *m_pDeveceList;

    QPushButton *m_pOpenBtn; //�����
    void onOpenClicked();

    QDoubleSpinBox *m_pGain;   // ����
    QDoubleSpinBox *m_pExposure; //�ع�ʱ��

    QPushButton *m_pSetBtn;

    QHBoxLayout *m_playout;

    QCheckBox *m_pCheckBox;//�Ƿ������ɼ�
    QPushButton *m_pSaveBtn;

    //x y�����ϵ�ƫ��
    QSpinBox *m_pXoffect;
    QSpinBox *m_pYoffect;
    QPushButton *m_pSetOffectBtn;

    //���ṩ����Դ�����ã�Ĭ�϶�������û��io����
    void initUi();

    //�����ع�ʱ�� & ����
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
