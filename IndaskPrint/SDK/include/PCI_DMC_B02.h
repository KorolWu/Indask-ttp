#include "Type_def.h"



#if defined __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// QEP information -> nQepIndex:0~2
I16 PASCAL _DMC_B02_qep_set_mode(U16 nCardNo, U8 nQepIndex, U8 nMode);
//  nMode:[0]CW/CCW  [1]A/B Phase
I16 PASCAL _DMC_B02_qep_set_inverse(U16 nCardNo, U8 nQepIndex, Boolean bEnable);
//  nEnable:[0]Normal  [1]Inverse
I16 PASCAL _DMC_B02_qep_get_reload_counter(U16 nCardNo, U8 nQepIndex, I32* nCounter);
I16 PASCAL _DMC_B02_qep_set_reload_counter(U16 nCardNo, U8 nQepIndex, I32 nCounter);
I16 PASCAL _DMC_B02_qep_get_counter(U16 nCardNo, U8 nQepIndex, I32* nCounter);

////////////////////////////////////////////////////////////////////////////////////////////////////
//// QEP information -> GPIO setting
I16 PASCAL _DMC_B02_gpio_software_control_status(U16 nCardNo, U16* nStatus);
// nStatus:bit# -> Pin#
I16 PASCAL _DMC_B02_gpio_software_control_setting(U16 nCardNo, U16 nSetting);
// nSetting:bit# -> Pin#

////////////////////////////////////////////////////////////////////////////////////////////////////
//// IPCMP#(0~3) operation
I16 PASCAL _DMC_B02_ipcmp_initial(U16 nCardNo, U8 nIpcmpIndex, U8 nQepIndex, U8 nGpioPin, Boolean bInverse);  //nIpcmpIndex=0~3組比較器, nQepIndex=0~2, nGpioPin=0~9, Boolean bInverse=準位
I16 PASCAL _DMC_B02_ipcmp_oneshot_time(U16 nCardNo, U8 nIpcmpIndex, U16 nPulseWidth);
//  nPulseWidth -> 0~4095(us)
I16 PASCAL _DMC_B02_ipcmp_software_trigger(U16 nCardNo, U8 nIpcmpIndex);
I16 PASCAL _DMC_B02_ipcmp_compare_position(U16 nCardNo, U8 nIpcmpIndex, I32 nStartPosition, U16 nInterval, U32 nCount, U8 nDir);
//  nDir -> [0]CW  [1]CCW
I16 PASCAL _DMC_B02_ipcmp_compare_trigger_count(U16 nCardNo, U8 nIpcmpIndex, U32* nCount);
I16 PASCAL _DMC_B02_ipcmp_compare_trigger_count_clear(U16 nCardNo, U8 nIpcmpIndex);
////////////////////////////////////////////////////////////////////////////////////////////////////
//// TPCMP#(0~5) operation
I16 PASCAL _DMC_B02_tpcmp_initial(U16 nCardNo, U8 nFifoIndex, U8 nQepIndex, U8 nGpioPin, Boolean bInverse, Boolean bInterrupt);
//  nSource -> QEP#(0~2)
I16 PASCAL _DMC_B02_tpcmp_oneshot_time(U16 nCardNo, U8 nFifoIndex, U16 nPulseWidth);
//  nPulseWidth -> 0~4095(us)
I16 PASCAL _DMC_B02_tpcmp_fifo_size(U16 nCardNo, U8 nFifoIndex, U8* nSize);
I16 PASCAL _DMC_B02_tpcmp_fifo_status(U16 nCardNo, U8 nFifoIndex, U8* nStatus);
//  nStatus -> Bit:[0]Empty  [1]Almost empty  [2]Full
I16 PASCAL _DMC_B02_tpcmp_software_trigger(U16 nCardNo, U8 nFifoIndex);
I16 PASCAL _DMC_B02_tpcmp_software_trigger_level(U16 nDeviceNo, U8 nFifoIndex, Boolean bActive);
I16 PASCAL _DMC_B02_tpcmp_compare_position_table_reset(U16 nCardNo, U8 nFifoIndex);
I16 PASCAL _DMC_B02_tpcmp_compare_position_table(U16 nCardNo, U8 nFifoIndex, I32 nPositionTable[], U32 nTableSize);
I16 PASCAL _DMC_B02_tpcmp_compare_position_table_level(U16 nCardNo, U8 nFifoIndex, I32 nPositionTable[], U8 nLevelTable[], U32 nTableSize);
I16 PASCAL _DMC_B02_tpcmp_compare_trigger_count(U16 nCardNo, U8 nFifoIndex, U32* nCount);
I16 PASCAL _DMC_B02_tpcmp_compare_trigger_count_clear(U16 nCardNo, U8 nFifoIndex);
I16 PASCAL _DMC_B02_tpcmp_compare_data_lock(U16 nCardNo, U8 nFifoIndex, U8* nLock);
////////////////////////////////////////////////////////////////////////////////////////////////////
//// External IO#(0~7) and latch FIFO operation
I16 PASCAL _DMC_B02_ext_io_get_input_value(U16 nCardNo, U8* nState);
I16 PASCAL _DMC_B02_ext_io_get_output_value(U16 nCardNo, U8* nState);
I16 PASCAL _DMC_B02_ext_io_set_output_value(U16 nCardNo, U8 nState);
I16 PASCAL _DMC_B02_ext_io_latch_initial(U16 nCardNo, U8 nExternalIoNo, U8 nSource, U8 nFilter);
// nSource -> [0]TPCMP#0  [1]TPCMP#1  [2]TPCMP#2  [3]TPCMP#3  [4]TPCMP#4  [5]TPCMP#5  [6]Software
// nFilter -> [0]Disable  [1]0.1ms  [2]0.5ms  [3]1ms
I16 PASCAL _DMC_B02_ext_io_latch_function(U16 nCardNo, U8 nExternalIoNo, Boolean bQep0, Boolean bQep1, Boolean bQep2, Boolean bSw, Boolean bH2L, Boolean bL2H);
I16 PASCAL _DMC_B02_ext_io_latch_enable(U16 nCardNo, U8 nExternalIoNo, Boolean bEnable);
I16 PASCAL _DMC_B02_latch_fifo_reset(U16 nCardNo, Boolean bEnable);
I16 PASCAL _DMC_B02_latch_fifo_status(U16 nCardNo, U8* nStatus);
//  nStatus -> Bit:[0]Empty  [1]Full
I16 PASCAL _DMC_B02_latch_fifo_size(U16 nCardNo, U8* nSize);
I16 PASCAL _DMC_B02_latch_fifo_get_qep_counter(U16 nCardNo, I32* nCounter, U8* nIoType, U8* nQepSource);



#if defined __cplusplus
}
#endif