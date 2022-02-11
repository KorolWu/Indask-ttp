#ifndef DMCNETCONTROL_H
#define DMCNETCONTROL_H

#include <QObject>
#include <QDebug>
#include "PCI_DMC.H"
#include <QTimer>
#include <QEventLoop>
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#include <QMap>
#include "DataStruct.h"
#include "../sharedata.h"
class DmcNetControl
{
public:
    DmcNetControl();

    void delay_msc(int msc);
    int openCar();
    int initCar();

    void disConnected();
    int servoONOFF(uint16_t nodeID,uint16_t slotId,uint16_t onOrOff);

    int move2home(uint16_t nodeID,uint16_t mode = 0,int offest = 0,uint16_t lowSpeed = 1000,uint16_t highSpend = 20000,double acc =1000);

    //多轴一起回原点 集合里是要回原点的轴的id
    int move2homes(QVector<uint16_t> axisVec);

    void stopHomeMove(uint16_t nodeID);
    int ppMove(QMap<uint16_t, int> &axisMap);
    void emg_stop(uint16_t axis);
    int getPosition(uint16_t  axisId);

    //获取轴的状态
    uint64_t getAxisStatus(uint16_t axisId);

    // relactive Move
    void relactiveMove(uint16_t axisId, int dir);
    uint16_t m_carNum = 0;
    int16_t m_findCarNum;
private:
    int gettimeofday(struct timeval *tp, void *tzp);
    uint16_t m_DmcCarList[32]={0};
    unsigned long m_slaveNum;

    //获取保存设置的轴的参数
    //QMap<uint16_t,AxisStruct> m_axisParameterMap;
};

#endif // DMCNETCONTROL_H
