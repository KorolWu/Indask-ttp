#include "sharedata.h"

ShareData * ShareData::m_Instance = new ShareData();
QMutex ShareData::m_mutex;
ShareData::ShareData()
{

}

ShareData *ShareData::getInstance()
{
    if(m_Instance == nullptr)
    {
        QMutexLocker mutexLocker(&m_mutex);
         if(m_Instance == nullptr)
        {
            m_Instance = new ShareData();
        }

    }
    return m_Instance;
}

void ShareData::deleteInstance()
{
    if(m_Instance != nullptr)
    {
        m_axisParameterMap.clear();
        m_Instance = nullptr;
        delete m_Instance;
    }
}
