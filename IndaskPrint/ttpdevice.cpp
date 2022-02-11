#include "ttpdevice.h"

TtpDevice::TtpDevice()
{

}

bool TtpDevice::openDevice()
{
    eRET retval; // For return values from function calls

    // Connect to the printer first
    retval = PiOpenPrinter();	// Open the printer interface
    // Look out for Monitor log message:  "Application Attached"

    if (RVAL_OK != retval) {
        return false;
//        m_printInited = 0;
//        qDebug()<<"Error, unable to open printer interface...is Monitor.exe running?"<<retval;
    }
    return true;
}

void TtpDevice::SendAbort()
{
    qDebug()<<"Sending Abort";
    eRET retval = PiAbort();
    if (RVAL_OK != retval) {
        qDebug()<<"Error, Abort failed";
    }

    // Now check the printer status, and wait until it is idle
    int starttime = clock();
    bool busy = true;
    while ((clock() - starttime) < 5000) {
        if (!PiIsBusy()) {
            busy = false;
            break;
        }
    }
    if (busy) {
        qDebug()<<"Error, Too long to become idle after abort";
    }
}

bool TtpDevice::InitialisePrinter(int scanning)
{
    eRET retval;

    // Send an abort to clear out any old data
    SendAbort();
    // Look out for Monitor log message: "Rx:Abort"

    // In scanning mode, we need to zero the X-position at the home position.
    // In a real application, the transport would be moved to the home position
    // before calling this command
    if (scanning) {
        qDebug()<<"Setting Home";
        retval = PiSetHome();
        if (RVAL_OK != retval) {
            qDebug()<<"Error, Set Home failed";
        }
        // Look out for Monitor log message: "PCCx X-counters cleared"
        // Note this may cause an error message if the printer is not configured
        // for scanning mode.  Set Scanning = 1 in the config file.
    }


    // Before sending any print commands, turn on the head power
    // A real application should turn off the head power when printing has finished.
    // For simplicity this is ignored here, and the heads are left on.
    qDebug()<<"Turning on head power";
    retval = PiSetHeadPower(1);
    if (RVAL_OK != retval) {
        qDebug()<<"Error, Set Head Power failed";
    }
    // Look out for Monitor log message: "Switching HDC and Head Power ON"
    return true;
}

bool TtpDevice::StartJob(DWORD jobid, DWORD jobtype, DWORD res, DWORD docwidth)
{
    uint32 CommandBuffer[6];
    eRET retval;

    // Setup the command buffer with the STARTJOB command
    CommandBuffer[0] = PCMD_STARTJOB;	// Command ID
    CommandBuffer[1] = 4;				// 4 more parameters for STARTJOB command
    CommandBuffer[2] = jobid;			// Job ID for tracking purposes
    CommandBuffer[3] = jobtype;			// Preload path used
    CommandBuffer[4] = res;				// Print Resolution
    CommandBuffer[5] = docwidth;		// Width of document, only used when printing right-to-left

    qDebug()<<"Sending StartJob";

    //
    // Commands and print data are buffered in several places - in the hardware, in the Print Engine,
    // and in the Printer Interface.
    // If print data is not being consumed by the print heads, eventually these buffers will fill up.
    // When this happens, the application should retry the command.
    // Normally an application would also have a mechanism for breaking out of this loop if it decides
    // to abort the print job; this is not present in this example for simplicity.
    //
    do {
        retval = PiSendCommand(CommandBuffer);		// Send the command to the Printer Interface
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        printf("Error %d (0x%x), StartJob failed\n", retval, retval);
    }

    // Look out for Monitor log message:  "Rx:StartJob"

    return RVAL_OK == retval;
}

void TtpDevice::Start(int scanning, DWORD jobtype, DWORD ncopies, DWORD docid)
{
    uint32 CommandBuffer[6];
    eRET retval;

    // Send the StartDoc or StartScan Command.
    // For scanning printing, we use StartScan.  Otherwise we use a STARTPDOC command or a
    // STARTFDOC command, depending on whether we are using preload or fifo mode.

    //发送StartDoc或StartScan命令。
    //对于扫描打印，我们使用StartScan。否则，我们使用STARTPDOC命令或
    //STARTFDOC命令，这取决于我们使用的是预加载还是fifo mod
    if (scanning) {
        CommandBuffer[0] = PCMD_STARTSCAN;	// Command ID
        CommandBuffer[2] = SD_FWD;			// Print the first swath in the forward direction
    }
    else {
        // Setup the command buffer with the STARTDOC command
        if (JT_PRELOAD == jobtype) {
            CommandBuffer[0] = PCMD_STARTPDOC;	// Command ID
            CommandBuffer[2] = ncopies;			// Number of copies of the document to print
        }
        else {
            CommandBuffer[0] = PCMD_STARTFDOC;	// Command ID
            CommandBuffer[2] = docid;			// ID of this document
        }
    }
    CommandBuffer[1] = 1;				// 1 more parameter for any of these commands

    qDebug()<<"Starting Document";
    do {
        retval = PiSendCommand(CommandBuffer);		// Send the command to the Printer Interface
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        qDebug()<<"Error, StartDoc failed";
    }
    // Look out for Monitor log message:  "Rx:StartPreloadDoc" or "Rx:StartFifoDoc" or "Rx:StartScan"
}

void TtpDevice::SendImage(uint32 *buffer)
{
    eRET retval;

    //
    // Commands and print data are buffered in several places - in the hardware, in the Print Engine,
    // and in the Printer Interface.
    // If print data is not being consumed by the print heads, eventually these buffers will fill up.
    // When this happens, the application should retry the command.
    // Normally an application would also have a mechanism for breaking out of this loop if it decides
    // to abort the print job; this is not present in this example for simplicity.
    //
    do {
        retval = PiSendCommand(buffer);
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        qDebug()<<"Error, Send Image Failed";
    }
    // Look out for Monitor log message:  "Rx:Image"
}

void TtpDevice::ScanSendDoc(uint32 *SecondBuffer)
{
    uint32 CommandBuffer[6];
    eRET retval;

    CommandBuffer[0] = PCMD_STARTSCAN;	// Command ID
    CommandBuffer[1] = 1;				// 1 more parameter for StartScan command
    CommandBuffer[2] = SD_FWD;			// Print the second swath in the reverse direction

    qDebug()<<"Starting Second Swath";
    do {
        retval = PiSendCommand(CommandBuffer);		// Send the command to the Printer Interface
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        qDebug()<<"Error, Start failed";
    }

    // Send the image.
    qDebug()<<"Sending Second Swath";
    SendImage(SecondBuffer);

    // Finished sending images, send the end doc command
    EndDoc();
}

void TtpDevice::EndDoc()
{
    uint32 CommandBuffer[6];
    eRET retval;

    CommandBuffer[0] = PCMD_ENDDOC;		// Command ID
    CommandBuffer[1] = 0;				// No parameters for ENDDOC command

    qDebug()<<"Sending EndDoc";
    do {
        retval = PiSendCommand(CommandBuffer);		// Send the command to the Printer Interface
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        qDebug()<<"Error, EndDoc failed";
    }
    // Look out for Monitor log message:  "Rx:EndDoc"

}

void TtpDevice::EndJob()
{
    uint32 CommandBuffer[6];
    eRET retval;

    CommandBuffer[0] = PCMD_ENDJOB;		// Command ID
    CommandBuffer[1] = 0;				// No parameters for ENDJOB command

    qDebug()<<"Sending EndJob";
    do {
        retval = PiSendCommand(CommandBuffer);		// Send the command to the Printer Interface
    } while (RVAL_FULL == retval);

    if (RVAL_OK != retval) {
        qDebug()<<"Error, EndJob failed";
    }
    // Look out for Monitor log message:  "Rx:EndJob"
}
