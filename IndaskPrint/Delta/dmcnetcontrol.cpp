#include "dmcnetcontrol.h"

DmcNetControl::DmcNetControl()
// :m_axisParameterMap(ShareData::getInstance()->m_axisParameterMap)
{

}

void DmcNetControl::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}

///
/// \brief DmcNetControl::initCar 0 初始化成功 返回板卡的数量 m_carNum
/// \return
///
int DmcNetControl::openCar()
{
    int16_t ret = _DMC_01_open(&m_findCarNum);
    return ret;
}

int DmcNetControl::initCar()
{
    int16_t ret = 9;
    uint16_t carNum;
    for(uint16_t i = 0; i <m_findCarNum ;i++)
    {
        ret = _DMC_01_get_CardNo_seq(i,&carNum);
        m_DmcCarList[i] = carNum;
        ret =_DMC_01_pci_initial(m_DmcCarList[i]);
        if(ret != 0)
            return ret;

        ret =_DMC_01_initial_bus(m_DmcCarList[i]);
        ret =_DMC_01_start_ring(m_DmcCarList[i],0);
        if(ret != 0)
            return ret;
    }
    _DMC_01_get_node_table(m_carNum,&m_slaveNum);
    return 0;

}

void DmcNetControl::disConnected()
{
    _DMC_01_close();
}


///
/// \brief DmcNetControl::servoONOFF 默认就一张卡  0 松磁  1 励磁
/// \param nodeID   是私服的站号
/// \param slotId   基本都是0
/// \param onOrOff
/// \return    99 表示已经励磁
///
int DmcNetControl::servoONOFF(uint16_t nodeID, uint16_t slotId, uint16_t onOrOff)
{
    //检查是否已经励磁
    unsigned long MC_status;
    int16_t rt = _DMC_01_motion_status(m_carNum,nodeID,slotId,&MC_status);
    // MC_status bit 8 = 1 代表已经再励磁状态
    if(((MC_status >> 8) & 0x01)==1)
    {
        qDebug()<<"MC_status"<<MC_status;
        if(onOrOff == 1)
            return 99;
    }

    rt = _DMC_01_ipo_set_svon(m_carNum, nodeID, slotId , onOrOff);
    return rt;
}

///
/// \brief DmcNetControl::move2home
/// \param nodeID
/// \param slotId
/// \param mode
/// \param offest
/// \param lowSpeed
/// \param highSpend
/// \param acc
/// \return  0 回零成功 -1 超时  -2 励磁失败
///
int DmcNetControl::move2home(uint16_t nodeID, uint16_t mode, int offest, uint16_t lowSpeed, uint16_t highSpend, double acc)
{
    if(servoONOFF(nodeID,0,1) == 0)
    {
        uint16_t rt = _DMC_01_set_home_config(0,nodeID,0,mode,offest,lowSpeed,highSpend,acc);
        rt &= _DMC_01_set_home_move(0,nodeID,0);
        if(rt == 0)
        {
            uint16_t status = 1;
            unsigned long motionStatus = 0;
            struct timeval s,e;
            double timeUseWait = 0;
            gettimeofday(&s,nullptr);
            while (true) {
                gettimeofday(&e,nullptr);
                delay_msc(10);
                timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);

                //默认15秒钟没回到原点就gg
                if(timeUseWait >= 15000)
                {
                    stopHomeMove(nodeID);
                    return -1;//timeout
                }

                _DMC_01_motion_done(0,nodeID,0,&status);
                //bit 1 2,10到位,12，14pel  15 mel 负
                _DMC_01_motion_status(0,nodeID,0,&motionStatus);
                //qDebug()<<"status="<< status<<"Mstatus="<<motionStatus;
                if(status == 0 && (((motionStatus >>1) & 0x1 )== 1) && (((motionStatus >>2) & 0x1 )== 1) && (((motionStatus >>10) & 0x1 )== 1) && (((motionStatus >>12) & 0x1 )== 1))//这里默认检查 状态位的第一位
                {
                    return 0;
                }
            }
        }

    }
    else
    {
        //励磁失败
        return -2;
    }
    return -3;
}

///
/// \brief DmcNetControl::move2homes  多轴一起回原点
/// \param axisVec 回原点轴的id
/// \return
///
int DmcNetControl::move2homes(QVector<uint16_t> axisVec)
{
    for(int i = 0; i < axisVec.size(); i++)
    {
        servoONOFF(axisVec.at(i),0,1);
    }
    for(int i = 0 ; i < axisVec.size();i++)
    {                                                         //回原点模式固定位17 0偏移，300lowSpeed
        uint16_t rt = _DMC_01_set_home_config(0,axisVec.at(i),0,17,0,1000,ShareData::getInstance()->m_axisParameterMap[axisVec.at(i)].homeVmax,ShareData::getInstance()->m_axisParameterMap[axisVec.at(i)].acc);
        rt &= _DMC_01_set_home_move(0,axisVec.at(i),0);
        if(rt != 0)
        {
            for(int j = 0 ;j < axisVec.size(); j++)
            {
                stopHomeMove(axisVec.at(j));
            }
            return rt;
        }
    }
    uint16_t status = 1;
    unsigned long motionStatus = 0;
    struct timeval s,e;
    double timeUseWait = 0;
    gettimeofday(&s,nullptr);
    QVector <uint16_t> checkOrg;
    checkOrg.clear();
    while (true) {
        gettimeofday(&e,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);

        //默认15秒钟没回到原点就gg
        if(timeUseWait >= 40000)
        {
            for(int j = 0 ;j < axisVec.size(); j++)
            {
                stopHomeMove(axisVec.at(j));
            }
            return -1;//timeout
        }

        for(int i = 0; i < axisVec.size(); i++)
        {
            _DMC_01_motion_done(0,axisVec.at(i),0,&status);
            //bit 1 2,10到位,12，14pel  15 mel 负
            _DMC_01_motion_status(0,axisVec.at(i),0,&motionStatus);
            if(status == 0 && (((motionStatus >>1) & 0x1 )== 1) && (((motionStatus >>2) & 0x1 )== 1) && (((motionStatus >>10) & 0x1 )== 1) && (((motionStatus >>12) & 0x1 )== 1))//这里默认检查 状态位的第一位
            {
                if(!checkOrg.contains(axisVec.at(i)))
                {
                    checkOrg.append(axisVec.at(i));
                }
            }
            if(axisVec.size() == checkOrg.size())
            {
                return 0;
            }
        }

    }

}

void DmcNetControl::stopHomeMove(uint16_t nodeID)
{
    /* Stop Home move */
    uint16_t rt = _DMC_01_escape_home_move(m_carNum, nodeID, 0);
    if(rt == 0)
        return;
}

///
/// \brief DmcNetControl::ppMove 多轴绝对运动
/// \param axisMap 轴的id，目标位置   轴的参数也是从<轴ID，轴参数> 两个map 通过axis_id 联系起来
/// \return 都到位后返回值 = 0
///
int DmcNetControl::ppMove(QMap<uint16_t, int> &axisMap)
{
    int ret = 0;
    for(auto it = axisMap.begin();it != axisMap.end();it ++)
    {
        ret  &= servoONOFF(it.key(),0,1);//-------------------slotID 默认= 0---------------------
    }
    if(ret != 0)
        return -6;//轴没有励磁，励磁失败
    for(auto it = axisMap.begin();it != axisMap.end();it ++)
    {
        _DMC_01_start_ta_move(m_carNum,it.key(),0 ,it.value(),0,ShareData::getInstance()->m_axisParameterMap[it.key()].vMax,ShareData::getInstance()->m_axisParameterMap[it.key()].acc,ShareData::getInstance()->m_axisParameterMap[it.key()].dcc);
    }
    QVector<uint16_t> axisMoveDown;
    axisMoveDown.clear();
    uint16_t status = 1;
    unsigned long motionStatus = 0;
    struct timeval s,e;
    double timeUseWait = 0;
    gettimeofday(&s,nullptr);
    while (true) {
        gettimeofday(&e,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);

        //默认25秒钟没到就gg
        if(timeUseWait >= 25000)
        {
            return -1;//timeout
        }
        for(auto it = axisMap.begin();it != axisMap.end();it ++)
        {
            _DMC_01_motion_done(0,it.key(),0,&status);
            //bit 1 2,10到位,12，14pel  15 mel 负
            _DMC_01_motion_status(m_carNum,it.key(),0,&motionStatus);

            //判断是否有轴报警 bit 9 = DrviceErr
            if(((motionStatus >>9) & 0x1 )== 1)
            {
                //将所有的轴停止
                for(auto ito = axisMap.begin();ito != axisMap.end();it++ )
                {
                    emg_stop(ito.key());
                }
                return -2;
            }

            //马达停止 且到达位置 bit 10 = target
            if(status == 0 &&  (((motionStatus >>10) & 0x1 )== 1))
            {
                if(false == axisMoveDown.contains(it.key()))
                {
                    axisMoveDown.append(it.key());
                    qDebug()<<"move down insert"<<it.key();
                }

            }
            //到位的集合和要移动轴的集合size相同
            if(axisMap.size() == axisMoveDown.size())
                return 0;
        }
    }

}

void DmcNetControl::emg_stop(uint16_t axis)
{
    _DMC_01_emg_stop(m_carNum,axis,0);
}

int DmcNetControl::getPosition(uint16_t axisId)
{
    long pos;
    _DMC_01_get_position(0,axisId,0,&pos);
    return pos;
}

uint64_t DmcNetControl::getAxisStatus(uint16_t axisId)
{
    unsigned long int motionStatus;
    _DMC_01_motion_status(m_carNum,axisId,0,&motionStatus);
    return motionStatus;
}

///
/// \brief DmcNetControl::relactiveMove
/// \param axisId
/// \param dir = 0 负方向  =1 正方向
///
void DmcNetControl::relactiveMove(uint16_t axisId, int dir)
{
    int ret = 0;
    ret  &= servoONOFF(axisId,0,1);//-------------------slotID 默认= 0---------------------
    if(ret != 0)
        return ;//轴没有励磁，励磁失败
    int distance = 200000;
    if(dir == 0)
        distance = -200000;                     //dis   Tacc Tdec
    _DMC_01_start_tr_move(0,axisId,0,distance,0,80000,1,5);
}

int DmcNetControl::gettimeofday(timeval *tp, void *tzp)
{
    Q_UNUSED(tzp)
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year   = wtm.wYear - 1900;
    tm.tm_mon   = wtm.wMonth - 1;
    tm.tm_mday   = wtm.wDay;
    tm.tm_hour   = wtm.wHour;
    tm.tm_min   = wtm.wMinute;
    tm.tm_sec   = wtm.wSecond;
    tm. tm_isdst  = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
