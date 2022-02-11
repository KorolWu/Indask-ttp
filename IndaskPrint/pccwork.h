#ifndef PCCWORK_H
#define PCCWORK_H

#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include "PrinterInterface.h"


///
/// \brief The PccWork class ”√¿¥±£¥ÊpccPrint hdc status
///
///
class PccWork : public QObject
{
    Q_OBJECT
public:
    explicit PccWork(QObject *parent = nullptr);
    void work();
    void delay_msc(int msc);
    bool m_StopFlag = true;

signals:

};

#endif // PCCWORK_H
