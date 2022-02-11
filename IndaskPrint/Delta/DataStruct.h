#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QString>
#include <QObject>
#include <QMap>
#include "Meteor.h"


typedef struct _AxisStrcut
{
    int vMax;
    double acc;
    double dcc;
    uint16_t homeVmax;
    ~_AxisStrcut()
    {

    }

}AxisStruct;
typedef struct _PccStatus
{
    TAppStatus appStatus;
    TAppHeadStatus headerStatus;
    TAppPccStatus pccStatus;
}PccStatus;
#endif // DATASTRUCT_H
