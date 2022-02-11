#include "pccwork.h"
#include "sharedata.h"
#include <QDebug>

PccWork::PccWork(QObject *parent) : QObject(parent)
{

}

///
/// \brief PccWork::work ¸üÐÂpcc 1 µÄ×´Ì¬
///
void PccWork::work()
{

    while(m_StopFlag == true)
    {
        for(uint32_t i = 1; i < ShareData::getInstance()->m_headCount+2; i++)
        {
            TAppStatus *appStatus = PiGetPrnStatus();
            TAppHeadStatus* headerStatus  = PiGetHeadStatus(1, i);
            TAppPccStatus* pccStatus = PiGetPccStatus(1);

            if(appStatus != nullptr && (headerStatus != nullptr) && pccStatus != nullptr)
            {
                PccStatus pcc;
                pcc.appStatus = *appStatus;
                pcc.headerStatus = *headerStatus;
                pcc.pccStatus = *pccStatus;
                ShareData::getInstance()->m_pccStatusMap.insert(i,pcc);
               // qDebug()<<i;
            }

        }

        delay_msc(500);
    }
}

void PccWork::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}
