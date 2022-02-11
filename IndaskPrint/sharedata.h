#ifndef SHAREDATA_H
#define SHAREDATA_H

#include <QMutex>
#include <QMutexLocker>
#include <QMap>
#include "Delta/DataStruct.h"
class ShareData
{
private:
    ShareData();
public:
    static ShareData* m_Instance;
    static QMutex m_mutex;
    static ShareData* getInstance();
    QMap<uint16_t,AxisStruct> m_axisParameterMap;
    QMap<uint32_t,PccStatus> m_pccStatusMap;
    uint32_t m_headCount = 1; //head count


    int m_width;
    int m_heitht;
    void deleteInstance();

};

#endif // SHAREDATA_H
