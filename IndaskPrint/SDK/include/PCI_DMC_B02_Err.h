#if !defined(__PCI_DMC_B02_ERROR_H__)
    #define __PCI_DMC_B02_ERROR_H__

enum EPCI_DMC_B02_ERROR
{
    ERR_B02_NO_ERROR = 0,           // <-- Replace with original error code#0

    // New error code below
    // EEPROM
    ERR_B02_EEPROM_READ,
    ERR_B02_EEPROM_WRITE,
    // QEP
    ERR_QEP_INDEX,
    // GPIO
    ERR_GPIO_OUTPUT_SIZE,
    // IPCMP
    ERR_IPCMP_INDEX,
    ERR_IPCMP_MPC_DATA_TYPE,        // It will never happened (internal use)
    // TPCMP
    ERR_TPCMP_FIFO_INDEX,
    ERR_TPCMP_QEP_SOURCE,
    ERR_TPCMP_TABLE_NO_DATA,        // Input table empty
    ERR_TPCMP_TABLE_OUT_OF_RANGE,   // Input table size is large than TPCMP max. size
    ERR_TPCMP_TABLE_OVERFLOW,       // Input table size is large than TPCMP FIFO remainder size
    // EXT. IO
    ERR_EXTIO_RANGE,
    ERR_EXTIO_LATCH_TYPE,           // It will never happened (internal use)
    // Latch FIFO
    ERR_LATCH_FIFO_EMPTY,
    ERR_LATCH_FIFO_INVALID_DATA
};

#endif