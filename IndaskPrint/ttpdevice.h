#ifndef TTPDEVICE_H
#define TTPDEVICE_H


// Standard libraries
#include <stdio.h>
#include <time.h>
// Meteor specific includes
#include "PrinterInterface.h"	// Contains definitions for all the Meteor library functions
#include "Meteor.h"				// Definition of common datatypes and constants
#include <QDebug>

#include "tchar.h"
#include "typedef.h"

typedef unsigned long       DWORD;


///
/// \brief The TtpDevice class  ttp°å¿¨¿ØÖÆÇý¶¯
///
class TtpDevice
{
public:
    TtpDevice();


    bool openDevice();
    void SendAbort();
    bool InitialisePrinter(int scanning);

    bool StartJob(DWORD jobid, DWORD jobtype, DWORD res, DWORD docwidth);
    void Start(int scanning, DWORD jobtype, DWORD ncopies, DWORD docid);
    void SendImage(uint32* buffer);
    void ScanSendDoc(uint32* SecondBuffer);
    void EndDoc();

    void EndJob(void);
};

#endif // TTPDEVICE_H
