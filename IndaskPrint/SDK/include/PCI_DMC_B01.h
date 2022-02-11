#include "Type_def.h"



#if defined __cplusplus
extern "C" {
#endif

I16 PASCAL _DMC_01_set_compare_channel_position(U16 CardNo, U16 compare_channel, I32 position);
I16 PASCAL _DMC_01_get_compare_channel_position(U16 CardNo, U16 compare_channel, I32 *position);
I16 PASCAL _DMC_01_set_compare_ipulser_mode(U16 CardNo, U16 mode); //0:AB phase  1:CW/CCW
I16 PASCAL _DMC_01_set_compare_channel_direction(U16 CardNo, U16 compare_channel, U16 dir); //0:Normal  1:Inverse
I16 PASCAL _DMC_01_set_compare_channel_trigger_time(U16 CardNo, U16 compare_channel, U32 time_us);
I16 PASCAL _DMC_01_set_compare_channel_one_shot(U16 CardNo, U16 compare_channel);
I16 PASCAL _DMC_01_set_compare_channel_source(U16 CardNo, U16 compare_channel,U16 source);
I16 PASCAL _DMC_01_channel0_position_cmp(U16 CardNo,I32 start,U16 dir,U16 interval,U32 trigger_cnt);//Dir=1:----..Dir=0:++++ trigger_cnt=0:infinity trigger
I16 PASCAL _DMC_01_channel0_position_cmp_by_gpio(U16 CardNo, U16 dir, U16 interval, I32 trigger_cnt);//Dir=1:----..Dir=0:++++ trigger_cnt=0:infinity trigger
I16 PASCAL _DMC_01_channel1_output_enable(U16 CardNo, U16 on_off);//打開channel1 硬體compare的功能
I16 PASCAL _DMC_01_channel1_output_mode(U16 CardNo, U16 mode);
I16 PASCAL _DMC_01_channel1_get_io_status(U16 CardNo, U16* io_status);
I16 PASCAL _DMC_01_channel1_set_gpio_out(U16 CardNo, U16 on_off);
I16 PASCAL _DMC_01_channel1_get_fifo_status(U16 CardNo, U16* fifo_status);
I16 PASCAL _DMC_01_channel1_get_fifo_counter(U16 CardNo, U16* fifo_cnt);
I16 PASCAL _DMC_01_channel1_position_compare_table(U16 CardNo, I32* pos_table, U32 table_size);
I16 PASCAL _DMC_01_channel1_position_compare_table_level(U16 CardNo, I32* pos_table, U32* level_table, U32 table_size);
I16 PASCAL _DMC_01_channel1_position_compare_table_cnt(U16 CardNo, U32* cnt);
I16 PASCAL _DMC_01_set_compare_channel_polarity(U16 CardNo, U16 inverse); //0:Normal  1:Inverse
I16 PASCAL _DMC_01_channel1_position_re_compare_table(U16 CardNo);
I16 PASCAL _DMC_01_channel1_position_re_compare_table_level(U16 CardNo);
I16 PASCAL _DMC_01_set_compare_channel_enable(U16 CardNo, U16 compare_channel,U16 enable);//接受由compare count的值發compare,而非軟體的on_off
I16 PASCAL _DMC_01_get_compare_channel_direction(U16 CardNo, U16 compare_channel, U16 *dir) ;//0:Normal  1:Inverse



#if defined __cplusplus
}
#endif