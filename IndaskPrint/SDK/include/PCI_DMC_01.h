#include "Type_def.h"



#if defined __cplusplus
extern "C" {
#endif



//Initial
I16 PASCAL _DMC_01_open(I16* existcard);
I16 PASCAL _DMC_01_get_CardNo_seq(U16 CardNo_seq,U16 *CardNo);
void PASCAL _DMC_01_close();
I16 PASCAL _DMC_01_pci_initial(U16 CardNo);
I16 PASCAL _DMC_01_get_card_version(U16 CardNo, U16 *ver);
I16 PASCAL _DMC_01_get_fpga_version(U16 CardNo, U16 *ver);
//Card Operate
I16 PASCAL _DMC_01_initial_bus(U16 CardNo);
I16 PASCAL _DMC_01_initial_bus2();
I16 PASCAL _DMC_01_start_ring(U16 CardNo, U8 RingNo);
I16 PASCAL _DMC_01_get_device_table(U16 CardNo, U16* value);
I16 PASCAL _DMC_01_get_node_table(U16 CardNo, U32 *NodeIDTable);
I16 PASCAL _DMC_01_get_cycle_time(U16 CardNo, I32 *time);   //Internal DSP Math calculation time , Should be less then 1000us  
I16 PASCAL _DMC_01_check_card_running(U16 CardNo, U16 *running);
I16 PASCAL _DMC_01_reset_card(U16 CardNo);
I16 PASCAL _DMC_01_check_nodeno(U16 CardNo, U16 NodeID,U16 SlotID,U16 *exist);
I16 PASCAL _DMC_01_get_master_connect_status(U16 CardNo, U16 *Protocal);
I16 PASCAL _DMC_01_get_mailbox_Error(U16 CardNo, U32* error_cnt);
I16 PASCAL _DMC_01_get_mailbox_cnt(U16 CardNo, U32 *PC_cnt,U32 *DSP_cnt);
I16 PASCAL _DMC_01_get_dsp_cnt(U16 CardNo, U32 *int_cnt,U32 *main_cnt);
I16 PASCAL _DMC_01_set_dio_output(U16 CardNo,U16 On_Off);
I16 PASCAL _DMC_01_set_dio_single_output(U16 CardNo, U16 bitno, U16 On_Off);//20160401
I16 PASCAL _DMC_01_get_dio_output(U16 CardNo,U16 *On_Off);
I16 PASCAL _DMC_01_get_dio_single_output(U16 CardNo, U16 bitno, U16 *On_Off);//20160401
I16 PASCAL _DMC_01_get_dio_input(U16 CardNo,U16 *On_Off);
I16 PASCAL _DMC_01_get_dio_single_input(U16 CardNo, U16 bitno, U16 *On_Off);//20160401

///SDO 
I16 PASCAL _DMC_01_check_canopen_lock(U16 CardNo,U16 *lock);
I16 PASCAL _DMC_01_get_canopen_ret(U16 CardNo, U16* COBID, U8* value);
I16 PASCAL _DMC_01_send_message(U16 CardNo, U16 NodeID,U16 SlotID , U16 Index,U16 SubIdx,U16 DataType,U16 Value0,U16 Value1,U16 Value2,U16 Value3);
I16 PASCAL _DMC_01_send_message2(U16 CardNo, U16 NodeID,U16 SlotID , U16 Index,U16 SubIdx,U16 DataType,U16 Value0,U16 Value1,U16 Value2,U16 Value3);
I16 PASCAL _DMC_01_send_message3(U16 CardNo, U16 *Index,U16 *SubIdx,U16* DataType,U16 *Value0,U16 *Value1,U16 *Value2,U16 *Value3);
I16 PASCAL _DMC_01_reset_sdo_choke(U16 CardNo);
I16 PASCAL _DMC_01_get_sdo_retry_history(U16 CardNo, U32 *cnt);
I16 PASCAL _DMC_01_read_message(U16 CardNo, U16 *Cmd,U16 *COBID ,U16 *SubIdx,U16 *Value0,U16 *Value1,U16 *Value2,U16 *Value3);
I16 PASCAL _DMC_01_read_message2(U16 CardNo, U16 NodeID ,U16 *Cmd,U16 *COBID ,U16 *SubIdx,U16 *Value0,U16 *Value1,U16 *Value2,U16 *Value3,U16 *cnt);
I16 PASCAL _DMC_01_get_message(U16 CardNo, U16 NodeID,U16 SlotID,U16 Index,U16 SubIdx, U16 *Cmd,U16 *COBID ,U16 *SubIdx_,U16 *Value0,U16 *Value1,U16 *Value2,U16 *Value3);

//SDO Motion PP mode						   
I16 PASCAL _DMC_01_set_sdo_driver_speed_profile(U16 CardNo, U16 NodeID,U16 SlotID , U32 MaxVel, F64 acc, F64 dec);
I16 PASCAL _DMC_01_start_sdo_driver_r_move(U16 CardNo, U16 NodeID,U16 SlotID , I32 Distance);
I16 PASCAL _DMC_01_start_sdo_driver_a_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Position);
I16 PASCAL _DMC_01_start_sdo_driver_new_position_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Position,U16 abs_rel);

//SDO Motion Home mode
I16 PASCAL _DMC_01_set_home_config(U16 CardNo,U16 NodeID,U16 SlotID ,U16 Mode,I32 offset,U16 lowSpeed,U16 highSpeed,F64 acc);
I16 PASCAL _DMC_01_set_home_move(U16 CardNo,U16 NodeID,U16 SlotID);
I16 PASCAL _DMC_01_escape_home_move(U16 CardNo,U16 NodeID,U16 SlotID);

//Motion PDO Command Control

I16 PASCAL _DMC_01_ipo_set_svon(U16 CardNo, U16 NodeID,U16 SlotID, U16 ON_OFF);

//Motion Single Axis
I16 PASCAL _DMC_01_motion_cnt(U16 CardNo, U16 NodeID, U16 SlotID,U16 *pc_mc_cnt,U16 *dsp_mc_cnt);
I16 PASCAL _DMC_01_start_tr_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

I16 PASCAL _DMC_01_p_change(U16 CardNo, U16 NodeID,U16 SlotID, I32 NewPos);
//20160722
I16 PASCAL _DMC_01_p_change_multi_axes(U16 CardNo,U16 AxisNum ,U16* NodeID, U16* SlotID, I32 *position, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec, I16 Curve_mode);
I16 PASCAL _DMC_01_v_change(U16 CardNo, U16 NodeID,U16 SlotID, I32 NewSpeed, F64 sec);

I16 PASCAL _DMC_01_start_tr_move_2seg(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_move_2seg(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_move_2seg(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_move_2seg(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);

I16 PASCAL _DMC_01_start_tr_move_2seg2(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_move_2seg2(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_move_2seg2(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_move_2seg2(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, F64 Tacc, F64 Tsec, F64 Tdec);


//2 Axes Linear move
I16 PASCAL _DMC_01_start_tr_move_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_move_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_move_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_move_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

//2 Axes Circle Move
//Angle>0:CW..Angle<0:CCW   //Center Point ,Angle
I16 PASCAL _DMC_01_start_tr_arc_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_arc_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_arc_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_arc_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

//Angle>0:CW..Angle<0:CCW   //End Point ,Angle
I16 PASCAL _DMC_01_start_tr_arc2_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 End_X, I32 End_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_arc2_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 End_X, I32 End_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_arc2_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 End_X, I32 End_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_arc2_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 End_X, I32 End_Y, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

//Dir=1:CW..Dir=0:CCW   //End Point ,Center Point
I16 PASCAL _DMC_01_start_tr_arc3_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y,I32 End_X,I32 End_Y, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_arc3_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y,I32 End_X,I32 End_Y, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_arc3_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y,I32 End_X,I32 End_Y, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_arc3_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y,I32 End_X,I32 End_Y, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

//3 Axes Linear move
I16 PASCAL _DMC_01_start_tr_move_xyz(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 DisZ, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_move_xyz(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 DisZ, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_move_xyz(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 DisZ, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_move_xyz(U16 CardNo, U16* NodeID,U16* SlotID, I32 DisX, I32 DisY, I32 DisZ, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

//3 Axes Heli move Dir=1:CW..Dir=0:CCW
I16 PASCAL _DMC_01_start_tr_heli_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sr_heli_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_ta_heli_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _DMC_01_start_sa_heli_xy(U16 CardNo, U16* NodeID,U16* SlotID, I32 Center_X, I32 Center_Y, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec);

///VELOCITY MOVE Dir=1:----..Dir=0:++++
I16 PASCAL _DMC_01_tv_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 StrVel, I32 MaxVel, F64 Tacc,I16 Dir);
I16 PASCAL _DMC_01_sv_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 StrVel, I32 MaxVel, F64 Tacc,I16 Dir);

I16 PASCAL _DMC_01_get_motion_error_code(U16 CardNo, U16 NodeID,U16 SlotID, I16* error_code);
I16 PASCAL _DMC_01_get_motion_error_cnt(U16 CardNo, U16 NodeID,U16 SlotID, I16* error_cnt);

//Motion Stop
I16 PASCAL _DMC_01_emg_stop(U16 CardNo, U16 NodeID,U16 SlotID);
I16 PASCAL _DMC_01_emg_stop2(U16 CardNo, U16 NodeID, U16 SlotID);
I16 PASCAL _DMC_01_sd_stop(U16 CardNo, U16 NodeID,U16 SlotID,F64 Tdec);
I16 PASCAL _DMC_01_sd_abort(U16 CardNo, U16 NodeID,U16 SlotID,F64 Tdec);

//Motion Status
I16 PASCAL _DMC_01_motion_done(U16 CardNo, U16 NodeID,U16 SlotID,U16 *MC_status);
I16 PASCAL _DMC_01_motion_done_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,U16 *MC_status);//20160624

I16 PASCAL _DMC_01_motion_status(U16 CardNo, U16 NodeID,U16 SlotID,U32 *MC_status);
I16 PASCAL _DMC_01_motion_status_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,U32 *MC_status);//20160623

I16 PASCAL _DMC_01_set_interrutp_buffer(U16 CardNo, U16 NodeID,U16 SlotID);
//Motion Counter Operating
I16 PASCAL _DMC_01_get_command(U16 CardNo, U16 NodeID,U16 SlotID, I32 *cmd);
I16 PASCAL _DMC_01_get_command_multi_axes(U16 CardNo,U16 AxisNum, U16 *NodeID,U16 *SlotID, I32 *cmd);//20160623
I16 PASCAL _DMC_01_get_target_pos(U16 CardNo, U16 NodeID,U16 SlotID, I32 *pos);
I16 PASCAL _DMC_01_get_target_pos_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID, I32 *pos);//20160623  

I16 PASCAL _DMC_01_set_target_pos(U16 CardNo, U16 NodeID,U16 SlotID, I32 pos);//20150416
I16 PASCAL _DMC_01_get_current_speed(U16 CardNo, U16 NodeID,U16 SlotID,I32 *speed);
I16 PASCAL _DMC_01_get_current_speed_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,I32 *speed);//20160622

I16 PASCAL _DMC_01_set_position(U16 CardNo,U16 NodeID,U16 SlotID,I32 pos);
I16 PASCAL _DMC_01_set_command(U16 CardNo, U16 NodeID,U16 SlotID, I32 cmd);
I16 PASCAL _DMC_01_get_position(U16 CardNo, U16 NodeID,U16 SlotID, I32* pos);
I16 PASCAL _DMC_01_get_position_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID, I32 *pos);//20160623

I16 PASCAL _DMC_01_get_current_speed_rpm(U16 CardNo, U16 NodeID,U16 SlotID,I32 *rpm);
I16 PASCAL _DMC_01_get_current_speed_rpm_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,I32 *rpm);//20160622

//////Add new 091103
I16 PASCAL _DMC_01_get_buffer_length(U16 CardNo,U16 NodeID,U16 SlotID,U16 *bufferLength);
I16 PASCAL _DMC_01_get_buffer_length_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,U16 *bufferLength);//20160624

I16 PASCAL _DMC_01_set_gear(U16 CardNo, U16 NodeID,U16 SlotID,I16 numerator,I16 denominator,U16 Enable);
I16 PASCAL _DMC_01_set_gear2(U16 CardNo, U16 NodeID,U16 SlotID,F64 numerator,F64 denominator,U16 Enable);

//Torqur Mode
I16 PASCAL _DMC_01_set_torque_mode(U16 CardNo,U16 NodeID,U16 SlotID,U32 slope);
I16 PASCAL _DMC_01_set_torque(U16 CardNo,U16 NodeID,U16 SlotID,I32 ratio);
I16 PASCAL _DMC_01_set_torque_stop(U16 CardNo,U16 NodeID,U16 SlotID,U16 stop);
I16 PASCAL _DMC_01_set_torque_velocity_feed_forward(U16 CardNo,U16 NodeID, U16 SlotID,U32 velocity_feed_forward);
I16 PASCAL _DMC_01_set_torque_velocity_limit(U16 CardNo,U16 NodeID, U16 SlotID,U32 velocity_limit);
//Velocity Mode
I16 PASCAL _DMC_01_set_velocity_mode(U16 CardNo,U16 NodeID,U16 SlotID,F64 Tacc,F64 Tdec);
I16 PASCAL _DMC_01_set_velocity(U16 CardNo,U16 NodeID,U16 SlotID,I32 rpm);
I16 PASCAL _DMC_01_set_velocity_stop(U16 CardNo,U16 NodeID,U16 SlotID,U16 stop);
I16 PASCAL _DMC_01_set_velocity_torque_feed_forward(U16 CardNo,U16 NodeID, U16 SlotID,U32 torque_feed_forward);
I16 PASCAL _DMC_01_set_velocity_torque_limit(U16 CardNo,U16 NodeID, U16 SlotID,U32 torque_limit);
//
I16 PASCAL _DMC_01_get_torque(U16 CardNo,U16 NodeID,U16 SlotID,I16 *torque);
I16 PASCAL _DMC_01_get_torque_multi_axes(U16 CardNo,U16 AxisNum,U16 *NodeID,U16 *SlotID,I16 *torque);//20160621

I16 PASCAL _DMC_01_get_rpm(U16 CardNo,U16 NodeID,U16 SlotID,I16 *rpm);

//read servo parameter
I16 PASCAL _DMC_01_read_servo_parameter(U16 CardNo,U16 NodeID,U16 SlotID,U16 group,U16 idx,U32 *data);

//write sevvo parameter
I16 PASCAL _DMC_01_write_servo_parameter(U16 CardNo,U16 NodeID,U16 SlotID,U16 group,U16 idx,U32 data);

//Reset Alm
I16 PASCAL _DMC_01_set_ralm(U16 CardNo, U16 NodeID, U16 SlotID);
I16 PASCAL _DMC_01_set_ralm_servo_all(U16 CardNo);
I16 PASCAL _DMC_01_get_alm_code(U16 CardNo, U16 NodeID, U16 SlotID,U32 *alm_code);
I16 PASCAL _DMC_01_master_alm_code(U16 CardNo,U16* alm_code);
I16 PASCAL _DMC_01_slave_error(U16 CardNo, U16 NodeID, U16 SlotID, U16* alm_cnt);

//MISC
I16 PASCAL _misc_app_get_circle_endpoint(I32 Start_X, I32 Start_Y ,I32 Center_X, I32 Center_Y, F64 Angle,I32* end_x,I32* end_y);
I16 PASCAL _misc_app_get_circle_center_point(I32 Start_X, I32 Start_Y ,I32 End_x,I32 End_y, F64 Angle,I32 *Center_X, I32 *Center_Y);


I16 PASCAL _misc_set_record_debuging(U16 enable);
I16 PASCAL _misc_open_record_debuging_file(char *file_name, U16 open);

I16 PASCAL _misc_security(U32 OtherWord0,U32 OtherWord1,U32 SyntekWord0,U32 SyntekWord1,U32* Password0,U32* Password1,U32* Password2, U32* Password3 );
I16 PASCAL _misc_slave_get_serialno(U16 CardNo, U16 NodeID, U16 SlotID, U32* SerialNO);
I16 PASCAL _misc_slave_check_verifykey(U16 CardNo, U16 NodeID, U16 SlotID, U32* VerifyKey, U16* Lock_state);
I16 PASCAL _misc_slave_check_userpassword(U16 CardNo, U16 NodeID, U16 SlotID, U32* Password_data, U16* Password_state);
I16 PASCAL _misc_slave_write_userpassword(U16 CardNo, U16 NodeID, U16 SlotID, U32* Password_data);
I16 PASCAL _misc_slave_write_verifykey(U16 CardNo, U16 NodeID, U16 SlotID, U32* VerifyKey);
I16 PASCAL _misc_slave_user_data_buffer_write(U16 CardNo, U16 NodeID, U16 SlotID, U16 Address, U32* Data);
I16 PASCAL _misc_slave_user_data_to_flash(U16 CardNo, U16 NodeID, U16 SlotID);
I16 PASCAL _misc_slave_user_data_buffer_read(U16 CardNo, U16 NodeID, U16 SlotID, U16 Address, U32* Data);

I16 PASCAL _misc_app_get_spiral_endpoint(I32 start_X, I32 start_Y, I32 center_X, I32 center_Y,I32 spiral_interval,I32 spiral_angle,I32* end_x,I32* end_y);



//////////RM IO
I16 PASCAL _DMC_01_get_rm_input_value(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16 *value);
//20160624
I16 PASCAL _DMC_01_get_rm_input_value_multi_axes(U16 CardNo,U16 NodeID,U16 SlotID,U16 *port0,U16 *port1,U16 *port2,U16 *port3);//20160624


I16 PASCAL _DMC_01_set_rm_input_filter(U16 CardNo, U16 NodeID,U16 SlotID ,U16 port,U16 value);
I16 PASCAL _DMC_01_set_rm_input_filter_enable(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16 enable);
I16 PASCAL _DMC_01_get_rm_input_single_value(U16 CardNo, U16 NodeID, U16 SlotID, U16 port, U16 bitno,U16 *value);//20160401

I16 PASCAL _DMC_01_set_rm_output_value(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16 value);
I16 PASCAL _DMC_01_set_rm_output_single_value(U16 CardNo, U16 NodeID, U16 SlotID, U16 port, U16 bitno,U16 value);//20160401
I16 PASCAL _DMC_01_get_rm_output_value(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16* value);
I16 PASCAL _DMC_01_get_rm_output_single_value(U16 CardNo, U16 NodeID, U16 SlotID, U16 port, U16 bitno, U16* value);//20160401
I16 PASCAL _DMC_01_set_rm_output_value_error_handle(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16 value);
I16 PASCAL _DMC_01_get_rm_output_value_error_handle(U16 CardNo, U16 NodeID,U16 SlotID,U16 port,U16* value);
I16 PASCAL _DMC_01_set_rm_output_active(U16 CardNo, U16 NodeID,U16 SlotID,U16 Enable);

																						  
/////////RM64MN MPG 
I16 PASCAL _DMC_01_set_rm_mpg_axes_enable(U16 CardNo,U16 MasterNodeID,U16 MasterSlotID, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop);
I16 PASCAL _DMC_01_set_rm_mpg_axes_enable2(U16 CardNo,U16 MasterNodeID,U16 MasterSlotID, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop,U16 *denominator);
I16 PASCAL _DMC_01_set_rm_jog_axes_enable(U16 CardNo,U16 MasterNodeID,U16 MasterSlotID, U16* NodeID, U16* SlotID,U16 enable,U16 jog_mode,I32 *jog_speed,F64 *sec);
//////////
I16 PASCAL _DMC_01_command_buf_clear(U16 CardNo, U16 NodeID,U16 SlotID);
I16 PASCAL _DMC_01_buf_dwell(U16 CardNo, U16 NodeID,U16 SlotID, I32 dwell_cnt);

//SYNC Move
I16 PASCAL _DMC_01_sync_move(U16 CardNo);
I16 PASCAL _DMC_01_sync_move_config(U16 CardNo, U16 NodeID,U16 SlotID,I16 enable);





////////SOFT LIMIT
I16 PASCAL _DMC_01_set_soft_limit(U16 CardNo, U16 NodeID,U16 SlotID, I32 PLimit, I32 NLimit);
I16 PASCAL _DMC_01_enable_soft_limit(U16 CardNo, U16 NodeID,U16 SlotID, I16 Action);
//Action =1 emg stop
//Action =2 sd stop
I16 PASCAL _DMC_01_disable_soft_limit(U16 CardNo, U16 NodeID,U16 SlotID);
I16 PASCAL _DMC_01_get_soft_limit_status(U16 CardNo, U16 NodeID,U16 SlotID,U16* PLimit_sts,U16* NLimit_sts);



//Get Slave Type
I16 PASCAL _DMC_01_get_devicetype(U16 CardNo, U16 NodeID,U16 SlotID,U32 *DeviceType,U32 *IdentityObject);

//Get Slave version
I16 PASCAL _DMC_01_get_slave_version(U16 CardNo, U16 NodeID,U16 SlotID,U16* version);


//Monitor Parameter
I16 PASCAL _DMC_01_set_monitor(U16 CardNo, U16 NodeID,U16 SlotID, U16 monitorw);
I16 PASCAL _DMC_01_get_monitor(U16 CardNo, U16 NodeID,U16 SlotID, U32 *value);
I16 PASCAL _DMC_01_get_servo_command(U16 CardNo, U16 NodeID,U16 SlotID, U32 *servo_cmd);
I16 PASCAL _DMC_01_get_servo_DI(U16 CardNo, U16 NodeID,U16 SlotID, U16 *servo_DI);
I16 PASCAL _DMC_01_get_servo_DO(U16 CardNo, U16 NodeID,U16 SlotID, U16 *servo_DO);

//DIO Active Buffer
I16 PASCAL _DMC_01_set_trigger_buf_function(U16 CardNo,U16 NodeID,U16 SlotID,U16 enable);

I16 PASCAL _DMC_01_multi_axes_move(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID, I32 *DistArrary, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);  //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs
I16 PASCAL _DMC_01_start_spiral_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y,I32 spiral_interval,I32 spiral_angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_spiral2_xy(U16 CardNo, U16* NodeID, U16* SlotID,I32 center_x, I32 center_y,I32 end_x,I32 end_y,U16 dir,U16 circlenum, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);


//04_PI Special Function

I16 PASCAL _DMC_01_set_rm_04pi_ipulser_mode(U16 CardNo, U16 NodeID,U16 SlotID ,U16 mode);  //mode 0: AB phase 1:CW/CCW
I16 PASCAL _DMC_01_set_rm_04pi_opulser_mode(U16 CardNo, U16 NodeID,U16 SlotID ,U16 mode);  //mode 0: AB phase 1:CW/CCW
I16 PASCAL _DMC_01_set_rm_04pi_svon_polarity(U16 CardNo, U16 NodeID,U16 SlotID ,U16 polarity);  //polarity 0:Normal high  1:Normal low
I16 PASCAL _DMC_01_set_rm_04pi_DO2(U16 CardNo, U16 NodeID,U16 SlotID, U16 ON_OFF);
I16 PASCAL _DMC_01_04pi_set_poweron(U16 CardNo, U16 NodeID,U16 SlotID, U16 ON_OFF);
I16 PASCAL _DMC_01_set_rm_04pi_homing_ratio(U16 CardNo, U16 NodeID,U16 SlotID ,U16 ratio); 

I16 PASCAL _DMC_01_rm_04pi_get_MEL_polarity(U16 CardNo, U16 NodeID, U16 SlotID, U16 *data);
I16 PASCAL _DMC_01_rm_04pi_set_MEL_polarity(U16 CardNo, U16 NodeID, U16 SlotID, U16 inverse);
I16 PASCAL _DMC_01_rm_04pi_get_PEL_polarity(U16 CardNo, U16 NodeID, U16 SlotID, U16 *data);
I16 PASCAL _DMC_01_rm_04pi_set_PEL_polarity(U16 CardNo, U16 NodeID, U16 SlotID, U16 inverse);

//Motion Single Axis

I16 PASCAL _DMC_01_rm_04pi_md1_start_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a); //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs
I16 PASCAL _DMC_01_rm_04pi_md1_v_move(U16 CardNo, U16 NodeID,U16 SlotID, I32 StrVel, I32 MaxVel, F64 Tacc,I16 dir,U16 m_curve);//Dir=1:----..Dir=0:++++
I16 PASCAL _DMC_01_rm_04pi_md1_start_line2(U16 CardNo, U16 NodeID,U16 *SlotID, I32 *Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_arc(U16 CardNo, U16 NodeID,U16* SlotID, I32* Center, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_line3(U16 CardNo, U16 NodeID,U16 *SlotID, I32 *Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_line4(U16 CardNo, U16 NodeID,U16 *SlotID, I32 *Dist, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_arc2(U16 CardNo, U16 NodeID,U16* SlotID, I32* End, F64 Angle, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_arc3(U16 CardNo, U16 NodeID,U16* SlotID,  I32* Center,I32* End, I16 dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_start_heli(U16 CardNo, U16 NodeID,U16* SlotID,  I32* Center,I32 Depth, I32 Pitch, I16 dir, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_rm_04pi_md1_set_gear(U16 CardNo, U16 NodeID,U16 SlotID,I16 numerator,I16 denominator,U16 Enable);
I16 PASCAL _DMC_01_rm_04pi_md1_p_change(U16 CardNo, U16 NodeID,U16 SlotID, I32 NewPos);
I16 PASCAL _DMC_01_rm_04pi_md1_v_change(U16 CardNo, U16 NodeID,U16 SlotID, I32 NewSpeed, F64 sec);
I16 PASCAL _DMC_01_rm_04pi_md1_set_soft_limit(U16 CardNo, U16 NodeID,U16 SlotID, I32 PLimit, I32 NLimit,U16 Enable);
I16 PASCAL _DMC_01_rm_04pi_md1_get_soft_limit_status(U16 CardNo, U16 NodeID,U16 SlotID ,U16* NLimit_status,U16* PLimit_status);
I16 PASCAL _DMC_01_rm_04pi_md1_set_sld(U16 CardNo, U16 NodeID,U16 SlotID, I16 enable, I16 sd_logic,I16 mode);
I16 PASCAL _DMC_01_04pi_md1_get_mc_error_code(U16 CardNo, U16 NodeID,U16 SlotID, U16 *error_code);
I16 PASCAL _DMC_01_set_rm_04pi_ref_counter(U16 CardNo, U16 NodeID,U16 SlotID ,U16 mode);  //mode 0: command 1:position
I16 PASCAL _DMC_01_rm_04PI_get_buffer(U16 CardNo,U16 NodeID, U16 SlotID,U16 *bufferLength);
I16 PASCAL _DMC_01_rm_04pi_md1_get_mc_error_code(U16 CardNo, U16 NodeID,U16 SlotID, U16 *error_code);

I16 PASCAL _DMC_01_link_interrupt(U16 CardNo,void ( __stdcall *callbackAddr)(U16 CardNo,U16 NodeID));
I16 PASCAL _DMC_01_set_int_factor(U16 CardNo,U16 NodeID, U16 int_factor);
I16 PASCAL _DMC_01_int_enable(U16 CardNo,U16 NodeID);
I16 PASCAL _DMC_01_get_int_count(U16 CardNo,U16 NodeID,U16 *count);
I16 PASCAL _DMC_01_int_disable(U16 CardNo,U16 NodeID);
I16 PASCAL _DMC_01_get_int_status(U16 CardNo,U16 NodeID, U16* event_int_status);


I16 PASCAL _DMC_01_read_security(U16 CardNo,U16 page,U16 *array);
I16 PASCAL _DMC_01_read_security_status(U16 CardNo,U16 *status);
I16 PASCAL _DMC_01_write_security_status(U16 CardNo,U16 status);//0:write protect,1:write enable
I16 PASCAL _DMC_01_write_security(U16 CardNo,U16 page,U16 *array);


I16 PASCAL _DMC_01_check_userpassword(U16 CardNo, U32* password_data, U16* password_state);
I16 PASCAL _DMC_01_write_userpassword(U16 CardNo, U32* password_data);
I16 PASCAL _DMC_01_check_verifykey(U16 CardNo, U32* VerifyKey, U16* state);
I16 PASCAL _DMC_01_write_verifykey(U16 CardNo, U32* verifykey);
I16 PASCAL _DMC_01_read_serialno(U16 CardNo, U32* SerialNo);


I16 PASCAL _DMC_01_rm_04da_set_output_value(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 value);
I16 PASCAL _DMC_01_rm_04da_get_return_code(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16* returncode);
I16 PASCAL _DMC_01_rm_04da_set_output_range(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 range);
I16 PASCAL _DMC_01_rm_04da_set_output_enable(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 enable);
I16 PASCAL _DMC_01_rm_04da_set_output_overrange(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 on_off);
I16 PASCAL _DMC_01_rm_04da_set_output_error_clear(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 on_off);
I16 PASCAL _DMC_01_rm_04da_read_control_register(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16* control_register_data);
I16 PASCAL _DMC_01_rm_04da_get_output_value(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, U16 *value);
I16 PASCAL _DMC_01_rm_04da_set_output_error_handle(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 on_off);
I16 PASCAL _DMC_01_rm_04da_set_output_offset_value(U16 CardNo, U16 NodeID,U16 SlotID, U16 channelno, I16 value);
I16 PASCAL _DMC_01_rm_04da_get_output_offset_value(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, I16* value);
I16 PASCAL _DMC_01_rm_04da_read_data(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16* data);

I16 PASCAL _DMC_01_set_04ad_input_range(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 range);
I16 PASCAL _DMC_01_get_04ad_input_range(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 *range);
I16 PASCAL _DMC_01_set_04ad_conversion_time(U16 CardNo, U16 NodeID, U16 SlotID, U16 mode);
I16 PASCAL _DMC_01_get_04ad_conversion_time(U16 CardNo, U16 NodeID, U16 SlotID, U16* mode);
I16 PASCAL _DMC_01_get_04ad_data(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16* value);
I16 PASCAL _DMC_01_get_04ad_data_multi_axes(U16 CardNo,U16 NodeID,U16 SlotID,U16 *value0,U16 *value1,U16 *value2,U16 *value3);//20160701	

I16 PASCAL _DMC_01_set_04ad_average_mode(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 mode);
I16 PASCAL _DMC_01_get_04ad_average_mode(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16* mode);
I16 PASCAL _DMC_01_set_04ad_input_enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 ON_OFF);




I16 PASCAL _DMC_01_set_group(U16 CardNo, U16* NodeID,U16* SlotID,U16 NodeID_Num,U16 enable);


I16 PASCAL _DMC_01_speed_continue(U16 CardNo, U16 NodeID,U16 SlotID,U16 enable);
I16 PASCAL _DMC_01_speed_continue_mode(U16 CardNo, U16 NodeID,U16 SlotID,U16 mode);
I16 PASCAL _DMC_01_speed_continue_combine_ratio(U16 CardNo, U16 NodeID,U16 SlotID,U16 ratio);

//20110628

I16 PASCAL _DMC_01_set_sd_mode(U16 CardNo, U16 NodeID, U16 SlotID,U16 mode);
I16 PASCAL _DMC_01_set_scurve_rate(U16 CardNo, U16 NodeID, U16 SlotID,U16 scurve_rate);


//20110630
I16 PASCAL _DMC_01_enable_dda_mode(U16 CardNo, U16 enable);
I16 PASCAL _DMC_01_set_dda_data(U16 CardNo, U32* abs_pos);
I16 PASCAL _DMC_01_get_dda_cnt(U16 CardNo, U16* dda_cnt);

//20110919



//20111003
I16 PASCAL _DMC_01_start_v3_move(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_move_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 DisX, I32 DisY, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_arc_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_arc2_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 End_X, I32 End_Y, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_arc3_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y,I32 End_x,I32 End_y, I16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_move_xyz(U16 CardNo, U16* NodeID, U16* SlotID, I32 DisX, I32 DisY, I32 DisZ, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_heli_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_multi_axes(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID, I32 *DistArrary, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a); //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs;
I16 PASCAL _DMC_01_start_v3_spiral_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y,I32 spiral_interval,U32 spiral_angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_spiral2_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 center_x, I32 center_y,I32 end_x,I32 end_y,U16 dir,U16 circlenum, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);

I16 PASCAL _DMC_01_get_fifo_cnt(U16 CardNo, U16* fifo_cnt);


I16 PASCAL _DMC_01_liner_speed_master(U16 CardNo, U16 NodeID, U16 SlotID,U16 Mode);


I16 PASCAL _DMC_01_enable_record_mode(U16 CardNo, U16 enable,U16 mode);
I16 PASCAL _DMC_01_get_record_data(U16 CardNo, U32* record_data);
I16 PASCAL _DMC_01_get_record_cnt(U16 CardNo, U16* record_cnt);

//20111206
I16 PASCAL _DMC_01_set_dec_acceleration(U16 CardNo, U16 NodeID, U16 SlotID, F64 pss);
I16 PASCAL _DMC_01_set_sd_time(U16 CardNo, U16 NodeID, U16 SlotID, F64 sd_dec);

I16 PASCAL _DMC_01_get_DLL_path(char *lpFilePath, U32 nSize, U32 *nLength);
I16 PASCAL _DMC_01_get_DLL_version(char *lpBuf, U32 nSize, U32 *nLength);

//20111220
I16 PASCAL _DMC_01_enable_switch_buffer(U16 CardNo, U16 enable);

//20120322
I16 PASCAL _DMC_01_save_device_info(char *path);
I16 PASCAL _DMC_01_compare_device_info(char *path, char *pathLog);
I16 PASCAL _DMC_01_set_sld_stop(U16 CardNo, U16 NodeID, U16 SlotID, U16 enable);
I16 PASCAL _DMC_01_set_sld_mode(U16 CardNo, U16 NodeID, U16 SlotID, U16 mode);  //mode0:1 -> emg stop  //mode2: sd stop  //mode 3 velocity change to start velocity
I16 PASCAL _DMC_01_pdo_Rx_error(U16 CardNo, U16 NodeID,U16 SlotID,U32 *Rx_error1,U32 *Rx_error2,U16 set_get);  //set_get=0 read Rx_error1,Rx_error2 value,set_get=1 write Rx_error1,Rx_error2 value
I16 PASCAL _DMC_01_pdo_Tx_error(U16 CardNo, U16 NodeID,U16 SlotID,U32 *Tx_error,U16 set_get);

//20120328
I16 PASCAL _DMC_01_start_v3_sphere_xyz(U16 CardNo, U16* NodeID, U16* SlotID, I32 pos1_x, I32 pos1_y, I32 pos1_z, I32 pos2_x, I32 pos2_y, I32 pos2_z, I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);

//20120402
I16 PASCAL _DMC_01_set_function_time(U16 CardNo,U32 ms1000); 
//default ms1000=600 , min = 390    max = 800     _DMC_01_set_mc_fifo_mode mode=2,this function will active
I16 PASCAL _DMC_01_set_mc_fifo_mode(U16 CardNo, U16 mode);

I16 PASCAL _DMC_01_enable_axis_mode(U16 CardNo, U16 enable);

//20120507
I16 PASCAL _DMC_01_clear_dda_data(U16 CardNo);

//20120515
I16 PASCAL _DMC_01_set_cam_pitch(U16 CardNo, U16 NodeID, U16 SlotID,I32 pitch);
I16 PASCAL _DMC_01_set_cam_org(U16 CardNo, U16 NodeID, U16 SlotID, I16 Dir, I32 orgpos);
I16 PASCAL _DMC_01_set_cam_enable(U16 CardNo, U16 NodeID, U16 SlotID,U16 on_off);
I16 PASCAL _DMC_01_set_cam_mode(U16 CardNo, U16 NodeID, U16 SlotID,U16 Mode);//Mode 0:Pitch_Bi Direction,Mode 1:Pitch one Direction 
I16 PASCAL _DMC_01_set_cam_table(U16 CardNo, U16 NodeID, U16 SlotID, I16 Dir, I32* table);
I16 PASCAL _DMC_01_set_cam_table2(U16 CardNo, U16 NodeID, U16 SlotID, I16 Dir, I32* table,I32 Num);

//20120626
I16 PASCAL _DMC_01_set_dmc_mode(U16 CardNo, U16 NodeID, U16 SlotID);

//20120731
I16 PASCAL _DMC_01_set_backlash(U16 CardNo, U16 NodeID, U16 SlotID,I16 enable);
I16 PASCAL _DMC_01_set_backlash_info(U16 CardNo, U16 NodeID, U16 SlotID, I16 backlash,U16 accstep,U16 contstep,U16 decstep);

//20120801
I16 PASCAL _DMC_01_enable_electcam(U16 CardNo, U16 NodeID, U16 SlotID, U16 enable,U16 axisbit,U16 mode);
//ref from 0:command,1:position,3:compare position 

//2020-10-30
I16 PASCAL _DMC_01_Get_electcam_status(U16 CardNo, U16 NodeID, U16 SlotID, U16* enable,U16* axisbit,U16* mode);



//20120823
//I16 PASCAL _DMC_01_set_cv_mode(I16 CardNo, U16 NodeID, U16 SlotID, U16 flag_const_v, U16 flag_dec_c);//flag_const_v=1,???t?q ???t????,flag_dec_c=1,?[???t?q?????@??(??????DDA?P?U?????O???X)
I16 PASCAL _DMC_01_set_cv_mode(I16 CardNo, U16 NodeID, U16 SlotID, U16 flag_const_v);//flag_const_v=1,???t?q ???t????,flag_dec_c=1,?[???t?q?????@??(??????DDA?P?U?????O???X)

//20121002
I16 PASCAL _DMC_01_enable_ex_position(I16 CardNo, U16 NodeID, U16 SlotID, U16 enable);
I16 PASCAL _DMC_01_enable_6x_mode(U16 CardNo, U16 enable);

I16 PASCAL _DMC_01_enable_always_monitorid(U16 CardNo, U16 enable);

//20121112
I16 PASCAL _DMC_01_get_nrline_status(I16 CardNo, U16 NodeID, U16 SlotID, U16 *nrline_sts);

//20121211
I16 PASCAL _DMC_01_get_gear(U16 CardNo, U16 NodeID,U16 SlotID,I16 *numerator,I16 *denominator,U16 *Enable);
I16 PASCAL _DMC_01_get_gear2(U16 CardNo, U16 NodeID,U16 SlotID,F64 *numerator,F64 *denominator,U16 *Enable);

//20130311
I16 PASCAL _DMC_01_set_01ph_alm_polarity(U16 CardNo, U16 NodeID,U16 SlotID ,U16 polarity);
I16 PASCAL _DMC_01_set_01ph_org_polarity(U16 CardNo, U16 NodeID,U16 SlotID ,U16 polarity);


//20130417
I16 PASCAL _DMC_01_set_home_config2(U16 CardNo,U16 NodeID,U16 SlotID ,U16 Mode,I32 offset,U16 lowSpeed,U16 highSpeed,F64 acc);
I16 PASCAL _DMC_01_set_home_config_offset2(U16 CardNo,U16 NodeID ,U16 SlotID ,I32 offset);
I16 PASCAL _DMC_01_set_home_move2(U16 CardNo,U16 NodeID,U16 SlotID,U16 Mode);


//20130826
I16 PASCAL _DMC_01_get_feedrate_overwrite(U16 CardNo, U16 NodeID, U16 SlotID,I32 *New_Speed);
I16 PASCAL _DMC_01_get_v_change(U16 CardNo, U16 NodeID, U16 SlotID,I32 *New_Speed);

//20131007
I16 PASCAL _DMC_01_set_position_ref_source(U16 CardNo, U16 NodeID, U16 SlotID, I16 ref_source);
I16 PASCAL _DMC_01_get_position_ref_source(U16 CardNo, U16 NodeID, U16 SlotID, I16 *ref_source);


I16 PASCAL _DMC_01_set_virtual_command(U16 CardNo, U16 NodeID, U16 SlotID, I32 virtual_command);
I16 PASCAL _DMC_01_set_virtual_position(U16 CardNo, U16 NodeID, U16 SlotID, I32 virtual_Position);
I16 PASCAL _DMC_01_disable_virtual_pos(U16 CardNo, U16 NodeID, U16 SlotID, U16 on_off);
I16 PASCAL _DMC_01_get_virtual_command(U16 CardNo, U16 NodeID, U16 SlotID, I32 *virtual_command);

//20131112

I16 PASCAL _DMC_01_Set_Stepping_Move_rate(U16 CardNo, U16 NodeID, U16 SlotID, U8 MoveRatio);
I16 PASCAL _DMC_01_Get_Stepping_Move_rate(U16 CardNo, U16 NodeID, U16 SlotID, U8 *MoveRatio);
I16 PASCAL _DMC_01_get_gear_rate(I16 CardNo, U16 NodeID, U16 SlotID, F64 *GearRatio);
I16 PASCAL _DMC_01_set_gear_rate(U16 CardNo, U16 NodeID,U16 SlotID,F64 GearRate);
I16 PASCAL _DMC_01_set_04pi_org_polarity(U16 CardNo, U16 NodeID,U16 SlotID ,U16 polarity);

//04-PI mode1: Speed will reduce cw/ccw Max Speed 200k/mratio,AB phase 500k (pps/sec) /mratio,MoveRatio = 1~255
I16 PASCAL _DMC_01_set_feedrate_overwrite_rate(I16 CardNo, U16 NodeID, U16 SlotID, F64 feedrate);  
I16 PASCAL _DMC_01_feedrate_overwrite(U16 CardNo, U16 NodeID, U16 SlotID,U16 Mode,I32 New_Speed,F64 sec);
//mode = 2 ??	New_Speed*feedrate??FeedRate?????????v?? exp: New_Speed=100000,feedrate=0.0001,SPD=5000,->???????G NEW_SPD = SPD*New_Speed*feedrate=50000

I16 PASCAL _DMC_01_set_mc_buffer(U16 CardNo,U16 status);   //buffer always enable 

I16 PASCAL _DMC_01_start_v3_multi_axes_arc(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID,I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a); //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs;

//????_DMC_01_start_v3_ellipse_xy ???}?????? 2016-12-16

//20131129 ECAM repeat
I16 PASCAL _DMC_01_set_ecam_repeat(U16 CardNo, U16 NodeID,U16 SlotID,I32 start_pos,I32 end_pos,U16 enable);

//20131230
I16 PASCAL _misc_app_get_ellipse_para(F64 x0,F64 y0,F64 x1,F64 y1,F64 x2,F64 y2,F64 *center_x,F64 *center_y,F64 *radius);

//20140120
I16 PASCAL _DMC_01_set_acc_dec_2_slop(U16 CardNo,U16 time_slop_enable);

//20140313
I16 PASCAL _DMC_01_set_limit_auto_ralm(U16 CardNo,U16 enable);

//20140331
I16 PASCAL _DMC_01_set_01_ph_inposition(U16 CardNo, U16 NodeID,U16 SlotID ,U16 poswindow_time,U32 poswindow);
I16 PASCAL _DMC_01_get_01_ph_inposition(U16 CardNo, U16 NodeID,U16 SlotID ,U16 *poswindow_time,U32 *poswindow);

//20140408
I16 PASCAL _DMC_01_set_node_actmotion(I16 CardNo, U16 *NodeID,U16 num);

//20140428
I16 PASCAL _DMC_01_get_module_mode(I16 CardNo, U16 NodeID, U16 SlotID, U32* MC_Mode);

//20140508
I16 PASCAL _DMC_01_set_ref_counter(U16 CardNo, U16 NodeID,U16 SlotID ,U16 mode);  //mode 0: command 1:position 

//20140530
I16 PASCAL _DMC_01_multi_table_V3_move(U16 CardNo, U16 MotionNum, U16 NodeID, U16 SlotID, I32 *Dist,I32 StrVel, I32 *ConstVel, I32 EndVel , F64 *Tphase, F64 Tdec, U16 m_curve, U16 m_r_a);

//20141120
void PASCAL _misc_Out_Debuging_String(char *FmtMessage, ...);

//20141205
I16 PASCAL _DMC_01_get_watchdog_cnt(U16 CardNo, U32 *watchdog_cnt);
I16 PASCAL _DMC_01_set_watchdog_cnt(U16 CardNo, U32 watchdog_cnt);
I16 PASCAL _DMC_01_get_watchdog_value(U16 CardNo, U32 *watchdog_value);
I16 PASCAL _DMC_01_set_watchdog_value(U16 CardNo, U32 watchdog_value);

//20150120
I16 PASCAL _DMC_01_set_rm_04pi_md2_feedback_mode(U16 CardNo, U16 NodeID,U16 SlotID ,U16 mode);  //mode 0:With feedback 1:Without feedback

//20150306
void PASCAL _DMC_01_close_assign(U16 CardNo);
I16 PASCAL _DMC_01_open_assign(U16 PCI_CardNo, I16* existcard);

//20150306 for DRA 
I16 PASCAL _DMC_01_start_rline_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 pos1_x, I32 pos1_y, I32 pos2_x, I32 pos2_y, U16 mode ,F64 param, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_rline_xyz(U16 CardNo, U16* NodeID, U16* SlotID, I32 pos1_x, I32 pos1_y, I32 pos1_z, I32 pos2_x, I32 pos2_y, I32 pos2_z, U16 mode ,F64 param, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_rline_xy(U16 CardNo, U16* NodeID, U16* SlotID, I32 pos1_x, I32 pos1_y, I32 pos2_x, I32 pos2_y, U16 mode ,F64 param, I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_rline_xyz(U16 CardNo, U16* NodeID, U16* SlotID, I32 pos1_x, I32 pos1_y, I32 pos1_z, I32 pos2_x, I32 pos2_y, I32 pos2_z, U16 mode ,F64 param, I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);
I16 PASCAL _DMC_01_start_v3_msbrline_move(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID,U16 ArcNodeBit, I32 *DistArrary, I32 *DistArrary2,U16 Mode, F64 Parameter, F64 SpdRatio, F64 Angle1, F64 Angle2, I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a) ;

//20150319
I16 PASCAL _DMC_01_get_dsp_intext4cnt(U16 CardNo, U32 *int_t1,U32 *int_t2, U32 *int_t3,U32 *int_t4);

//20150407
I16 PASCAL _DMC_01_set_rm_04pi_home_config_Tdec(U16 CardNo,U16 NodeID ,U16 SlotID ,U32 Tdec, U32 enable);
I16 PASCAL _DMC_01_set_rm_04pi_Home_counter_Delay_time(U16 CardNo, U16 NodeID,U16 SlotID ,U16 Delay_time);

//20150522
I16 PASCAL _DMC_01_get_rm_04pi_home_config_Tdec(U16 CardNo,U16 NodeID ,U16 SlotID ,U16* Tdec, U16* enable);

//20150429
I16 PASCAL _DMC_01_set_dio_output_DW(U16 CardNo,U32 On_Off);
I16 PASCAL _DMC_01_set_dio_single_output_DW(U16 CardNo, U16 bitno, U32 On_Off);//20160401
I16 PASCAL _DMC_01_get_dio_output_DW(U16 CardNo,U32 *On_Off);
I16 PASCAL _DMC_01_get_dio_single_output_DW(U16 CardNo, U16 bitno, U32 *On_Off);//20160401
I16 PASCAL _DMC_01_get_dio_input_DW(U16 CardNo,U32 *On_Off);
I16 PASCAL _DMC_01_get_dio_single_input_DW(U16 CardNo, U16 bitno, U32 *On_Off);//20160401
I16 PASCAL _DMC_01_set_dio_output_DW_error_handle(U16 CardNo,U16 value);//20160511
I16 PASCAL _DMC_01_get_dio_output_DW_error_handle(U16 CardNo,U16 *value);//20160518






//20150506
I16 PASCAL _DMC_01_set_slave_error_value(U16 CardNo,U16 times);
I16 PASCAL _DMC_01_set_adjoint_status(U16 CardNo, U32 adjoint_status);
I16 PASCAL _DMC_01_get_adjoint_status(U16 CardNo, U32 *adjoint_status);

//20150529
I16 PASCAL _DMC_01_sd_buffer_link(U16 CardNo, U16 NodeID, U16 SlotID,F64 Tdec);//????speed continue ??,?i?H???_???e?B?????O,?????bbuffer???s?????O 

//20150601

I16 PASCAL _DMC_01_Start_PVTComplete(U16 CardNo, U16 NodeID, U16 SlotID,F64 *Position,F64 *Time, F64 Str_Vel, F64 End_Vel, I32 MotionCnt,U16 m_r_a);
I16 PASCAL _DMC_01_Start_PVT(U16 CardNo, U16 NodeID, U16 SlotID,F64 *Position,F64 *Time, F64 *Velocity,I32 MotionCnt,U16 m_r_a);
I16 PASCAL _DMC_01_get_PVT_cnt(U16 CardNo, U16 NodeID, U16 SlotID,U32 *count);

//2018-10-16
I16 PASCAL _DMC_01_Start_PVT_Enable(U16 CardNo, U16 AxisNum, U16 *AxisArray);


//20150709
I16 PASCAL _DMC_01_start_prov_multi_axes_arc(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID,I32 Center_X, I32 Center_Y, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a);	//m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs;

//20150710
I16 PASCAL _DMC_01_get_last_error_node_no(U16 CardNo, U16* ErrorNode);
I16 PASCAL _DMC_01_ssss(U16 CardNo, U16 ErrorNode);


//20150727
I16 PASCAL _DMC_01_set_connect_alm_reset(U16 CardNo, U16 Enable);


//20150728
I16 PASCAL _DMC_01_set_ralm_retry(U16 CardNo, U16 NodeID, U16 SlotID,U16 retryCount);

//20151027  A02?s?\??
I16 PASCAL _DMC_01_set_digital_filter(U16 CardNo,U16 port,U16 value);   //value [0] 50 u (sec)	[1] 500 u (sec) [2] 1m (sec)	[3] 2m (sec)
I16 PASCAL _DMC_01_get_digital_filter(U16 CardNo,U16 port,U16 *value);  //value [0] 50 u (sec)	[1] 500 u (sec) [2] 1m (sec)	[3] 2m (sec)


//20151110
I16 PASCAL _DMC_A02_mpg_get_poisition(U16 CardNo, I32* nValue);  //get ??????counter
I16 PASCAL _DMC_A02_mpg_fsm_get_lock_state(U16 CardNo, U8* nState);   // nState: [0]Unlock  [1]Lock  a02??????counter?P??
I16 PASCAL _DMC_A02_mpg_get_io_state_enable(U16 CardNo, U8* nState);  // nState: [0]Disable  [1]Active ????????pulse input ????????
I16 PASCAL _DMC_A02_mpg_axis_get_io_state(U16 CardNo, U8* nState);
// nState: [0]None  [1]Axis#0  [2]Axis#1  [3]Axis#2  [4]Axis#3  ?????b????
I16 PASCAL _DMC_A02_mpg_axis_get_ratio_state(U16 CardNo, U8* nState);
// nState: [0]None  [1]x1  [2]x10  [3]x100   ???????v????
I16 PASCAL _DMC_A02_mpg_clear_poisition(U16 CardNo);//20160715


//20151117
I16 PASCAL _DMC_A02_set_mpg_axes_enable(U16 CardNo, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop,U16 *denominator);
I16 PASCAL _DMC_A02_set_jog_axes_enable(U16 CardNo, U16* NodeID, U16* SlotID,U16 enable,U16 jog_mode,I32 *jog_speed,F64 *sec);  //jog_mode0->6button ????,1->?????????b,xbutton????jog???V
I16 PASCAL _DMC_A02_get_jog_io_state(U16 CardNo, U16* nState);  //Bit0: X+,Bit1: X-,Bit2: Y+,Bit3: Y-,Bit4: Z+,Bit5: Z-


//2017-10-02
I16 PASCAL _DMC_A02_set_mpg_axes_enable2(U16 CardNo, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop,U16 *denominator);


//2017-10-17
I16 PASCAL _DMC_A02_get_mpg_axes_enable2(U16 CardNo, U16* Enable);

//2017-10-16
I16 PASCAL _DMC_A02_set_mpg_axes_extend(U16 CardNo,U16 AxisExtend);

//2017-10-17
I16 PASCAL _DMC_A02_get_mpg_axes_extend(U16 CardNo,U16* AxisNum);

//2017-10-17
I16 PASCAL _DMC_A02_mpg_axis_get_io_state2(U16 CardNo, U8* nState);
// nState: [0]None  [1]Axis#0  [2]Axis#1  [3]Axis#2  [4]Axis#3 ...[10]Axis#9  ?????b????

//2017-10-17
I16 PASCAL _DMC_A02_mpg_axis_get_ratio_state2(U16 CardNo, U8* nState);
// nState: [0]None  [1]x1  [2]x10  [3]x100   ???????v????


//2017-11-27 MP1-A12D ?n?????? B01
I16 PASCAL _DMC_Qep_set_mpg_axis_enable(U16 CardNo, U16 CompareChannel, U16 NodeID, U16 SlotID, U16 enable, U16 pulser_ratio, U32 ratio, U32 slop, U16 denominator);

//2017-11-30
I16 PASCAL _DMC_Qep_get_mpg_axis_enable(U16 CardNo, U16* CompareChannel, U16* NodeID, U16* SlotID, U16* enable, U16* pulser_ratio, U32* ratio, U32* slop, U16* denominator);

//2017-11-30
I16 PASCAL _DMC_Qep_get_mpg_axis_cnt(U16 CardNo, U16 compare_channel, I32* cnt);//B01 QEP

//2017-11-30
I16 PASCAL _DMC_Qep_set_mpg_clear(U16 CardNo ,U16 compare_channel);//B01 QEP clear



//20151215
I16 PASCAL _DMC_01_set_axis_normalamf_enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 filterTime, U16 enable);
I16 PASCAL _DMC_01_set_normalamf_enable(U16 CardNo, U16 afteramf_Num, U16 enable);

//20151208
//_Path_Start_TankHeli_XY(I16 CardNo, I16* AxisArray, I32 *Point1, I32 *Point2,I32 *Point3,I32 *Point4, F64 Depth, F64 Pitch,I32 MaxVel, F64 Tacc_Tdec, U16 AMFNum)

I16 PASCAL _DMC_01_start_tablemotion(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData,I32 DataSize,I16 AxisNum,I32 MaxVel, F64 Tacc_Tdec, U16 AMFNum, U16 cycle, U32 *Motion_No, I32 *IOCtl);//2017-01-05 U16 Tacc_Tdec //2017-01-17 U32 *Motion_No
I16 PASCAL _DMC_01_start_tablemotion_buffer(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData,I32 DataSize,I16 AxisNum,I32 MaxVel, F64 Tacc_Tdec,U16 Single_Step_Enable, U32 *Motion_No, U16 AMFNum, I32 *IOCtl);//2017-01-17 U16 Single_Step_Enable, U32 *Motion_No

//2017-01-05
I16 PASCAL _DMC_01_start_tablemotion2(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData,I32 *MaxVelocity,I32 DataSize,I16 AxisNum, F64 Tacc_Tdec, U16 AMFNum, U16 cycle, U32 *Motion_No, I32 *IOCtl);//2017-01-05 U16 Tacc_Tdec //2017-01-17 U32 *Motion_No
//2017-01-05
I16 PASCAL _DMC_01_start_tablemotion_buffer2(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData,I32 *MaxVelocity,I32 DataSize,I16 AxisNum, F64 Tacc_Tdec, U16 Single_Step_Enable, U32 *Motion_No,U16 AMFNum, I32 *IOCtl);//2017-01-17 U16 Single_Step_Enable, U32 *Motion_No

I16 PASCAL _DMC_01_start_tablemotion_cyclemode(U16 CardNo,I16 TableNo);
I16 PASCAL _DMC_01_get_tablemotion_length(U16 CardNo,I16 TableNo,I32 *cnt);
I16 PASCAL _DMC_01_get_tablemotion_cycle(U16 CardNo,I16 TableNo,I32 *cycle);
I16 PASCAL _DMC_01_tablemotion_feedrate_overwrite(U16 CardNo,I16 TableNo, I32 ratio,F64 sec); //0: tablemotion 1:profile planning
I16 PASCAL _DMC_01_tablemotion_feedhold(U16 CardNo,I16 TableNo, U16 On_Off,F64 sec);
I16 PASCAL _DMC_01_get_tablemotion_current_speed(U16 CardNo,I16 TableNo, I32 *CurrentSpeed);

I16 PASCAL _DMC_01_get_tablemotion_feedrate(U16 CardNo,I16 TableNo,I16 *feedrate);
I16 PASCAL _DMC_01_get_tablemotion_vector_speed(U16 CardNo,I16 TableNo,F64 *vectorspeed);
I16 PASCAL _DMC_01_set_tablemotion_blending_ratio(U16 CardNo,I16 TableNo,  U32 Ratio);

//20160104
I16 PASCAL _DMC_01_set_dmc_cycle_int_count(U16 CardNo,U16 count);


//20160108
I16 PASCAL _DMC_01_start_tablemotion_profile_planning(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *AccDec, I32 *PositionData,I32 DataSize,I16 AxisNum, I32 *MaxVel, F64 InitialVel_Ratio, I32 *IOCtl,U32 *Motion_No);//2016-10-25 F64 InitialVel_Ratio 2017-01-17 U32 *Motion_No
I16 PASCAL _DMC_01_start_tablemotion_profile_planning_para(U16 CardNo,I16 TableNo,I32 NanoSmoothDecectionLength,I32 RefTurnOnSpd ,I16 CurveDecectionFlag, I32 CurveDecectionLength, F64 CurveDecectionAngle, I32 ArcRefSpeed, I32 ArcRefRadius);
I16 PASCAL _DMC_01_start_tablemotion_profilemode(U16 CardNo,I16 TableNo);

//20160114
I16 PASCAL _DMC_01_set_tablemotion_ioctl_mapping(U16 CardNo,I16 TableNo,U16 ionum ,U16 NodeID, U16 SlotID,U16 iobit);//ionum :io mapping 0~3 , iobit: which Node output bit 



//
//20160119
I16 PASCAL _DMC_01_enable_dda_mode_group(U16 CardNo,U16 GroupNo, U16 enable);  //enable : assign Bit0~11 means nodeid  
I16 PASCAL _DMC_01_set_dda_data_group(U16 CardNo,U16 GroupNo, U32* abs_pos);   //abs_pos : 12??
I16 PASCAL _DMC_01_get_dda_cnt_group(U16 CardNo,U16 GroupNo, U16* dda_cnt);    //remain dda cnt
I16 PASCAL _DMC_01_clear_dda_data_group(U16 CardNo,U16 GroupNo);



//20160129
// Motion Home mode by torque 
I16 PASCAL _DMC_01_set_home_config_by_torque_limit(U16 CardNo,U16 NodeID,U16 SlotID ,U16 Mode,I32 offset,U16 lowSpeed,U16 highSpeed,F64 acc,U16 torque_ratio,U16 qualified_ms,U16 max_torque_ratio);
//torque_ratio P1-87 ?k?s???x (1~300) ???? %
//qualified_ms P1-88 ???x???F?T?{???? (2~2000) ???? ms qualified 
//max_torque_ratio P2-42 ???j?B?????x (0~10) ???? %


//20160317
I16 PASCAL _DMC_01_start_v3_heli_multi_axes_move(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID, I32 Center_X, I32 Center_Y,I32 *Dist, I32 Depth, I32 Pitch, I16 Dir, I32 StrVel, I32 MaxVel,I32 EndVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);  //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs

//20160823
I16 PASCAL _DMC_01_Set_PID_Parameters(I16 CardNo,I16 PIDNo, F64 Proportional_Gain, F64 Integrat_Gain, F64 Dervative_Gain, F64 IntegratMax, F64 IntegratMin, F64 Command_Max, F64 Command_Min, F64 Feedback_Max, F64 Feedback_Min,I32 cycleTime);//20161014 add ,I32 cycleTime
//20160906
I16 PASCAL _DMC_01_PID_Set_Source_Target_Info(U16 CardNo, U16 PIDNo, U16 OutputNodeNo, U16 OutputSlotNo, U16 OutputChannelNo ,U16 FeedbackNodeNo, U16 FeedbackSlotNo, U16 FeedbackChannelNo, U16 Enable);
//20160824
I16 PASCAL _DMC_01_get_04da_Output_range(U16 CardNo, U16 NodeID, U16 SlotID, U16 channelno, U16 *range);

I16 PASCAL _DMC_01_get_dda_error_global(U16 CardNo, U32* error_global);

//20160922
I16 PASCAL _DMC_01_PID_Set_DA_Vaule(U16 CardNo, U16 PIDNo ,F64 DA_Value);

//20161021
I16 PASCAL _DMC_01_pdo_write_servo_parameter(U16 CardNo, U16 NodeID, U16 SlotID, U16 Group, U16 Index, U32 Data);

//20161025
I16 PASCAL _DMC_01_set_fr_DWdata(U16 CardNo, U16 NodeID, U32 data);

//20161026
I16 PASCAL _DMC_01_pdo_check_servo_status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);

//2016-11-07 for M-R
I16 PASCAL _DMC_01_set_pdo_Wdata(U16 CardNo, U16 NodeID, U16 slot, U16 Value0, U16 Value1, U16 Value2, U16 Value3);

//2016-11-07 for M-R
I16 PASCAL _DMC_01_get_pdo_Wdata(U16 CardNo, U16 NodeID, U16 slot, U16* Value0, U16* Value1, U16* Value2, U16* Value3);

//2016-11-08 for M-R Dword
I16 PASCAL _DMC_01_set_pdo_DWdata(U16 CardNo, U16 NodeID, U16 slot, U32 Value0, U32 Value1);

//2016-11-08 for M-R Dword
I16 PASCAL _DMC_01_get_pdo_DWdata(U16 CardNo, U16 NodeID, U16 slot, U32* Value0, U32* Value1);

//2016-11-22 
I16 PASCAL _DMC_01_start_multiarc(U16 CardNo, U16 AxesNum, U16* NodeID, U16* SlotID, U16 ArcBit, U16 HelixBit, U16 ArcMode, I32 *CenterPoint, I32 *EndPoint, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Curve_mode, U16 AbsMode);

//2016-12-06
I16 PASCAL _DMC_01_set_command_mapping(U16 CardNo, U16 NodeID, U16 SlotID);

//2017-01-17
I16 PASCAL _DMC_01_Execute_Single_Step(U16 CardNo,I16 TableNo);//2017-01-19 

//2017-01-17
I16 PASCAL _DMC_01_Get_TableMotion_Now_MotionNo(U16 CardNo,I16 TableNo, U32 *MotionNo);

//2017-01-20
I16 PASCAL _DMC_01_TableMotion_Single_Step(U16 CardNo,I16 TableNo, U16 Enable);

//2017-02-10
I16 PASCAL _DMC_01_set_dio_input_trigger_mode(U16 CardNo, U16 trigger_mode);
//2017-02-10
I16 PASCAL _DMC_01_set_dio_input_int_enable(U16 CardNo, U16 Enable);
//2017-02-22
I16 PASCAL _DMC_01_set_dio_input_int_flag_clear(U16 CardNo);//RD Debug???A???}???C
//2017-02-22
I16 PASCAL _DMC_01_get_dio_input_int_flag(U16 CardNo, U16* DI_int_flag);//RD Debug???A???}???C
//2017-02-24
I16 PASCAL _DMC_01_get_dio_input_int_counter(U16 CardNo, U16* counter); 
//2017-02-24
I16 PASCAL _DMC_01_set_dio_input_int_counter_clear(U16 CardNo); 
//2017-03-01
I16 PASCAL _DMC_01_get_dio_input_int_status(U16 CardNo, U16* status);


//2017-02-14
I16 PASCAL _DMC_01_set_dio_input_level_emg(U16 CardNo, U16 Enable);
//2017-02-17
I16 PASCAL _DMC_01_set_dio_input_trigger_level(U16 CardNo, U16 level_mode);
//2017-02-17
I16 PASCAL _DMC_01_set_dio_input_level_emg_clear(U16 CardNo);
//2017-02-20
I16 PASCAL _DMC_01_get_dio_input_level_emg_status(U16 CardNo, U16* status);


//2017-03-07
I16 PASCAL _DMC_01_buffer_correlation_master(I16 CardNo,U16 NodeID,U16 SlotID,I16 Enable);

//2017-03-07
I16 PASCAL _DMC_01_buffer_correlation(I16 CardNo,U16 NodeID,U16 SlotID,I16 Enable);

//2017-03-10
I16 PASCAL _DMC_01_buffer_correlation_master_slave(I16 CardNo,U16 Slave_Node_Num,U16 Master_NodeID,U16* Slave_NodeID,U16 Slave_SlotID,I16 Enable);

//2017-03-13
I16 PCI_DMC_01_API _DMC_01_buffer_correlation_status(I16 CardNo,U16* Master_NodeID,U16* correlation_NodeID,U16* correlation_enable);

//2017-03-31
I16 PASCAL _DMC_A02_mpg_info(U16 CardNo, I32 *Pos1, I32 *Pos2);

//2017-06-01
I16 PASCAL _DMC_01_start_tablemotion3(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData, I32 *Ref_Absolute_Pos,I32 *MaxVelocity,I32 DataSize,I16 AxisNum, F64 Tacc_Tdec, U16 AMFNum, U16 cycle,U32 *ArcBit, U32 *Motion_No, F64* Delay_CycleCount, U16 Abs_Mode,I32 *IOCtl);//2017-06-01

//2017-06-02
I16 PASCAL _DMC_01_start_tablemotion_buffer3(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *PositionData, I32 *Ref_Absolute_Pos,I32 *MaxVelocity,I32 DataSize,I16 AxisNum, F64 Tacc_Tdec, U16 Single_Step_Enable, U32 *ArcBit, U32 *Motion_No, F64* Delay_CycleCount,U16 AMFNum, U16 Abs_Mode,I32 *IOCtl);//2017-05-31 I32* Ref_Absolute_Pos, U16 Abs_Mode

//2017-06-07
I16 PASCAL _DMC_01_start_tablemotion_profile_planning2(U16 CardNo, U16 *NodeID, U16 *SlotID,I16 TableNo, I32 *AccDec, I32 *PositionData, I32 *Ref_Absolute_Pos, I32 DataSize,I16 AxisNum, I32 *MaxVel, F64 InitialVel_Ratio, I32 *IOCtl, U32 *ArcBit, U32 *Motion_No, F64 *Delay_CycleCount, U16 Abs_Mode);//2017-06-07  I32 *Ref_Absolute_Pos , U32 *ArcBit, U16 Abs_Mode

//2018-08-28
I16 PASCAL _DMC_01_start_tableMotion_profileMode_data_flying_photography(U16 CardNo, I16 TableNo, I32 *PositionData, I32 DataSize, U16 *AxisArray, U16 *SlotArray, I32 *MaxVel, I32 *AccDecLimit, I32 Remain_Dist, I32 Stage2_Velocity, F64 InitialVel_Ratio, I32 *IOControl);

//2018-09-10
I16 PASCAL _DMC_01_start_tableMotion_profileMode_data_flying_position(U16 CardNo, I16 TableNo, I32* DataSize , I32* PositionData); 



//2017-06-12
I16 PCI_DMC_01_API _DMC_01_set_dio_single_output_DW_trigger_time(U16 CardNo, U32 bitno, F64 time_s, U16 Enable);

//2017-06-12
I16 PCI_DMC_01_API _DMC_01_set_dio_single_output_DW_one_shot(U16 CardNo);

//2017-06-13
I16 PCI_DMC_01_API _DMC_01_get_dio_single_output_DW_trigger_status(U16 CardNo, U16* bitno, F64* time_s, U16* trigger_flag, U16* Enable);

//2018-11-12
I16 PCI_DMC_01_API _DMC_01_set_dio_single_output_DW_trigger_cycle(U16 CardNo, U32 bitno, U16 On_time, U16 Off_time, U16 times, U16 trigger_mode);

//2018-11-12
I16 PCI_DMC_01_API _DMC_01_set_dio_single_output_DW_trigger_enable(U16 CardNo,U16 enable);




//2017-06-13
I16 PCI_DMC_01_API _DMC_01_set_dio_single_input_DW_trigger_mode(U16 CardNo, U16 DI_bitno, U16 DO_bitno, U16 DO_polarity, U16 trigger_mode, U16 Enable);

//2017-06-16
I16 PCI_DMC_01_API _DMC_01_get_dio_single_input_DW_trigger_mode(U16 CardNo, U16* DI_bitno, U16* DO_bitno, U16* DO_polarity, U16* trigger_mode, U16* Enable);

//2017-06-16
I16 PCI_DMC_01_API _DMC_01_get_dio_single_input_DW_trigger_flag(U16 CardNo, U16* DI_trigger_flag);









//2017-09-05
I16 PCI_DMC_01_API _DMC_01_Set_MPG_AMF(U16 CardNo, I16 AMFNo, I16 AMFNum, U16 FilterNum, U16 Enable);

//2017-11-16
I16 PASCAL _DMC_01_Start_Move_Spiral_Circle(U16 CardNo, U16* NodeID, U16* SlotID, I32 center_x, I32 center_y, I32 spiral_interval, U32 spiral_angle ,I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec, I16 Curve_mode, I16 m_r_a);

//2017-11-21
I16 PASCAL _DMC_01_Start_Move_Spiral2_Circle(U16 CardNo, U16* NodeID, U16* SlotID, I32 center_x, I32 center_y, I32 end_x, I32 end_y, U16 dir, U16 circlenum, I32 StrVel, I32 MaxVel, I32 EndVel, F64 Tacc, F64 Tdec, I16 Curve_mode, I16 m_r_a);

//2017-11-21
I16 PCI_DMC_01_API _DMC_01_get_passed_count(U16 CardNo, U16 NodeID, U16 SlotID, F64* passed_count_);

//2017-12-08
I16 PASCAL _DMC_01_ROUNDING(U16 CardNo, U16 Enable);//?B??Cycle?????@?B<1, ?b???????G?B?N?p?????????? 


//MotionBuffer

//2017-12-11 
I16 PASCAL _DMC_01_MotionBuf_Set_Crd_Parameters(U16 CardNo, U16 TableNo, U16 AxisNum, U16 *AxisArray, I32 SycMaxVel, I32 SycMaxAcc, U16 S_Curve_Time, U16 Max_IO_Advance_Time, U16 SetOriginFlag, I32 *OriginPos);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_Crd_Parameters(U16 CardNo, U16 TableNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 SycMaxVel, I32 SycMaxAcc, U16 S_Curve_Time, U16 Max_IO_Advance_Time, U16 SetOriginFlag, I32 *OriginPos);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Get_Crd_Parameters(U16 CardNo, U16 TableNo, U16 *AxisNum, U16 *AxisArray, I32 *SycMaxVel, I32 *SycMaxAcc, U16 *S_Curve_Time, U16 *Max_IO_Advance_Time, U16 *SetOriginFlag, I32 *OriginPos);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Crd_Parameters(U16 CardNo, U16 TableNo, U16 *AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *SycMaxVel, I32 *SycMaxAcc, U16 *S_Curve_Time, U16 *Max_IO_Advance_Time, U16 *SetOriginFlag, I32 *OriginPos);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Line_MultiAxis(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Line_MultiAxis(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Line_MultiAxis_G00(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Line_MultiAxis_G00(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);

//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Arc_Radius(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *Arc_TargetPosition, I32 Radius, U16 CircleDir ,I32 SynTargetVel , I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Arc_Radius(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *TargetPosition, I32 Radius, U16 CircleDir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Arc_CenterPos(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *TargetPosition, I32 *CenterPos, U16 CircleDir ,I32 SynTargetVel , I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Arc_CenterPos(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *TargetPosition, I32 *CenterPos, U16 CircleDir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Set_LookAhead_Parameters(U16 CardNo, U16 TableNo, I32 RefSwerveSpd, U16 ArcSpdModify, I32 ArcRefSpeed, I32 ArcRefRadius, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_LookAhead_Parameters(U16 CardNo, U16 TableNo, I32 RefSwerveSpd, U16 ArcSpdModify, I32 ArcRefSpeed, I32 ArcRefRadius, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Start(U16 CardNo, U16 TableNo , U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Start(U16 CardNo, U16 TableNo, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Stop(U16 CardNo, U16 TableNo , U16 FifoNo, U16 Mode);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Stop(U16 CardNo, U16 TableNo, U16 FifoNo, U16 Mode);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Get_Position(U16 CardNo, U16 TableNo ,I32 *Now_Position ,I32 *Now_Position_org);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Position(U16 CardNo, U16 TableNo, I32 *Now_Position, I32 *Now_Position_Org);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Get_Velocity(U16 CardNo, U16 TableNo ,I32 *CurrentSpeed);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Velocity(U16 CardNo, U16 TableNo, I32 *CurrentSpeed);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Feedrate_Override(U16 CardNo, U16 TableNo ,F64 SynVelRatio);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Feedrate_Override(U16 CardNo, U16 TableNo, F64 SynVelRatio);

//2020-07-02
I16 PASCAL _DMC_01_MotionBuf_Get_Feedrate_Override(U16 CardNo, U16 TableNo ,F64* SynVelRatio);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Get_Motion_Status(U16 CardNo, U16 TableNo , U16 *Status,I32 *MD_BlockNum, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Motion_Status(U16 CardNo, U16 TableNo, U16 *Status, I32 *BlockNum, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Set_Stop_Deceleration(U16 CardNo, U16 TableNo ,I32 DecSmoothStop, I32 DecAbruptStop);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_Stop_Deceleration(U16 CardNo, U16 TableNo, I32 DecSmoothStop, I32 DecAbruptStop);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Get_Stop_Deceleration(U16 CardNo, U16 TableNo ,I32 *DecSmoothStop, I32 *DecAbruptStop);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Stop_Deceleration(U16 CardNo, U16 TableNo, I32 *DecSmoothStop, I32 *DecAbruptStop);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_SetUserSegNum(U16 CardNo, U16 TableNo ,I32 SegNum, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_UserSegNum(U16 CardNo, U16 TableNo, I32 SegNum, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_GetUserSegNum(U16 CardNo, U16 TableNo ,I32 *SegNum, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_UserSegNum(U16 CardNo, U16 TableNo, I32 *SegNum, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Clear_Buffer(U16 CardNo, U16 TableNo , U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Clear_Buffer(U16 CardNo, U16 TableNo, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Single_Step(U16 CardNo, U16 TableNo , U16 FifoNo, U16 Enable);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Single_Step(U16 CardNo, U16 TableNo, U16 FifoNo, U16 Enable);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_BufGear(U16 CardNo, U16 TableNo ,U16 GearAxisNo, I32 Distance, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_BufGear(U16 CardNo, U16 TableNo, U16 AxisNo, U16 SlotNo, I32 Distance, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_BufMove(U16 CardNo, U16 TableNo ,U16 AxisNo, I32 Distance, I32 TargetVel , I32 Acceleration, U16 AbsMode, U16 BufMove_Mode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_BufMove(U16 CardNo, U16 TableNo, U16 AxisNo, U16 SlotNo, I32 Distance, I32 TargetVel, I32 Acceleration, U16 AbsMode, U16 BufMove_Mode, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_IOControl(U16 CardNo, U16 TableNo , U16 IO_Control_Num , IO_Set* IO_Array, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_IOControl(U16 CardNo, U16 TableNo, U16 IO_Control_Num, MOTION_BUFFER_IO_Set* IO_Array, U16 FifoNo);


//2017-12-11
I16 PASCAL _DMC_01_MotionBuf_Advanced_IOControl(U16 CardNo, U16 TableNo , U16 IO_Control_Num , IO_Set* IO_Array, U16 Time, U16 Mode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Advanced_IOControl(U16 CardNo, U16 TableNo, U16 IO_Control_Num, MOTION_BUFFER_IO_Set* IO_Array, U16 Time, U16 Mode, U16 FifoNo);


//2017-12-14
I16 PASCAL _DMC_01_MotionBuf_Delay(U16 CardNo, U16 TableNo ,F64 DelayTime, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Delay(U16 CardNo, U16 TableNo, F64 DelayTime, U16 FifoNo);


//2017-12-14
I16 PASCAL _DMC_01_MotionBuf_Get_Remain_Buffer_Size(U16 CardNo, U16 TableNo ,I32 *RemainBufSize, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Remain_Buffer_Size(U16 CardNo, U16 TableNo, I32 *RemainBufSize, U16 FifoNo);


//2017-12-14
I16 PASCAL _DMC_01_MotionBuf_SoftLimit_On(U16 CardNo, U16 TableNo, U16 CD_AxisNo, I16 LimitType, U16 Mode, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_SoftLimit_On(U16 CardNo, U16 TableNo, U16 AxisNo, I16 LimitType, U16 Mode, U16 FifoNo);


//2017-12-14
I16 PASCAL _DMC_01_MotionBuf_SoftLimit_Off(U16 CardNo, U16 TableNo, U16 CD_AxisNo, I16 LimitType, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_SoftLimit_Off(U16 CardNo, U16 TableNo, U16 AxisNo, I16 LimitType, U16 FifoNo);


//2018-01-15
I16 PASCAL _DMC_01_MotionBuf_IOControl_Status(U16 CardNo, U16* IO_Control_Num, IO_Set* IO_Array);

//2018-03-01
I16 PASCAL _DMC_01_MotionBuf_Clear_Crd(U16 CardNo, U16 TableNo, U16 FifoNo);

//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Clear_Crd(U16 u16_CardNo, U16 u16_TableNo, U16 u16_FifoNo);  // 2018-02-26

//2018-03-27
I16 PASCAL _DMC_01_MotionBuf_Disable(U16 CardNo, U16 TableNo, U16 FifoNo);
//U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Disable(U16 u16_CardNo, U16 u16_TableNo, U16 u16_FifoNo);


//2018-05-04
I16 PASCAL _DMC_01_MotionBuf_Helix(U16 CardNo, U16 TableNo, U16 *Helix_Axis, I32 *CenterPos, I32 Depth, I32 Pitch, I16 HelixDir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2018-05-04
I16 PASCAL _DMC_01_MotionBuf_TargetPos(U16 CardNo, U16 TableNo,I32* Target_Position, U16 FifoNo);

//2018-05-29
I16 PASCAL _DMC_01_MotionBuf_Line_MultiAxis2(U16 CardNo, U16 TableNo, U16 AxisNum, U16 *Line_Axis, I32 *TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2018-05-29
I16 PASCAL _DMC_01_MotionBuf_Line_MultiAxis2_G00(U16 CardNo, U16 TableNo, U16 AxisNum, U16 *Line_Axis, I32 *TargetPosition, I32 SynTargetVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);

//2018-06-04
I16 PASCAL _DMC_01_MotionBuf_Arc_MidPos(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *Arc_TargetPosition, I32 *Arc_MidTargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);

//2018-06-04
I16 PASCAL _DMC_01_MotionBuf_MultiAxis_Arc1(U16 CardNo, U16 TableNo, U16 FollowAxisNum, U16 *Axis_Array, I32 *CenterPos, F64 Angle,	U16 CircleDir, I32 *Follow_TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 SpeedMode, U16 AbsMode, U16 FifoNo);

//2018-06-04
I16 PASCAL _DMC_01_MotionBuf_MultiAxis_Arc2(U16 CardNo, U16 TableNo, U16 FollowAxisNum, U16 *Axis_Array, I32 *Arc_TargetPosition, F64 Angle, U16 CircleDir, I32 *Follow_TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 SpeedMode, U16 AbsMode, U16 FifoNo);

//2018-06-04
I16 PASCAL _DMC_01_MotionBuf_MultiAxis_Arc3(U16 CardNo, U16 TableNo, U16 FollowAxisNum, U16 *Axis_Array, I32 *Arc_TargetPosition, I32 *CenterPos, U16 CircleDir, I32 *Follow_TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 SpeedMode, U16 AbsMode, U16 FifoNo);

//2018-06-04
I16 PASCAL _DMC_01_MotionBuf_MultiAxis_Arc4(U16 CardNo, U16 TableNo, U16 FollowAxisNum, U16 *Axis_Array, I32 *Arc_TargetPosition, I32 *Arc_MidPosition, I32 *Follow_TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 SpeedMode, U16 AbsMode, U16 FifoNo);


//2018-07-10
I16 PASCAL _DMC_01_MotionBuf_Arc_follow(U16 CardNo, U16 TableNo, U16 AxesNum, U16 *AxisArray, U16 ArcMode, U16 *Arc_Axis_index, U16 master_axis_index, I32 *CenterPoint, I32 *EndPoint, F64 Angle, U16 Dir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);


//2018-08-27
I16 PASCAL _DMC_01_MotionBuf_Set_G00_Check(U16 CardNo, U16 TableNo, U16 Check_Time, I32* Error_Range, U16 Enable);

//2018-08-28
I16 PASCAL _DMC_01_MotionBuf_Get_G00_Check(U16 CardNo, U16 TableNo, U16* Check_Time, I32* Error_Range, U16* Enable);

//2018-08-28
I16 PASCAL _DMC_01_MotionBuf_Get_G00_Check_Flag(U16 CardNo, U16 TableNo, U16* Check_G00_Flag);

//2018-08-29
I16 PASCAL _DMC_01_MotionBuf_Get_G00_Check_match(U16 CardNo, U16 TableNo, I32* feedback);





//2017-12-13
I16 PASCAL _DMC_01_feedrate_overwrite_read(U16 CardNo, U16 NodeID, U16 SlotID,U16* Mode, I32* New_Speed, F64* sec);

//2018-01-22
I16 PASCAL _DMC_01_get_monitor_I32(U16 CardNo, U16 NodeID,U16 SlotID, I32 *value);

//2018-04-03
I16 PASCAL _DMC_01_set_rm_mpg_axes_enable3(U16 CardNo,U16 MasterNodeID,U16 MasterSlotID, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop,U32 *denominator);




//2018-06-01 MP1 ?????l??????
I16 PASCAL _DMC_MP1_set_mpg_axis_enable(U16 CardNo, U16* NodeID, U16* SlotID, U16 enable, U16 pulser_ratio, U32* ratio, U32* slop, U32* denominator);

//2018-06-11 MP1 ?????l??????
I16 PASCAL _DMC_MP1_get_mpg_axis_cnt(U16 CardNo, I32* cnt);//MP1 B01 QEP

//2018-06-11 MP1 ?????l??????
I16 PASCAL _DMC_MP1_set_mpg_axis_clear(U16 CardNo);//MP1 B01 QEP clear

//2018-06-08 MP1 ?????l??????
I16 PASCAL _DMC_01_get_mp1_dio_input(U16 CardNo,U16 *On_Off);

//2018-06-08 MP1 ?????l??????
I16 PASCAL _DMC_01_get_mp1_dio_single_input(U16 CardNo, U16 bitno, U16 *On_Off);

//2018-06-11 MP1 ?????l??????
I16 PASCAL _DMC_MP1_get_mpg_axis_enable(U16 CardNo, U16* NodeID, U16* SlotID, U16* enable, U16* pulser_ratio, U32* ratio, U32* slop, U32* denominator);


//2018-07-16 
I16 PASCAL _DMC_MP1_mpg_axis_get_io_state(U16 CardNo, U8* nState);


//2018-07-16
I16 PASCAL _DMC_MP1_mpg_axis_get_ratio_state(U16 CardNo, U8* nState);



//2018-09-13
I16 PASCAL _DMC_A02_set_mpg_axes_enable3(U16 CardNo, U16* NodeID, U16* SlotID, U16 enable, U16 pulser_ratio, U32 *ratio, U32 *slop, U32 *denominator);


//2018-07-03
I16 PASCAL _DMC_01_Start_Multi_Arc(U16 CardNo, U16 AxesNum, U16 *AxisArray, U16* SlotID, I32* DistArray, U16 SpeedMode, U16 ArcMode, U16 *Axis_index, I32 *CenterPoint, I32 *EndPoint, F64 Angle, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Curve_mode, U16 AbsMode);


//2018-07-06
I16 PASCAL _DMC_01_Start_Arc_follow(U16 CardNo, U16 AxesNum, U16 *AxisArray,U16* SlotID, U16 ArcMode, U16 *Arc_Axis_index, U16 master_axis_index , I32 *CenterPoint, I32 *EndPoint, F64 Angle, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Curve_mode, U16 AbsMode);


//2019-03-28
I16 PASCAL _DMC_01_start_g31(U16 CardNo, U16 u16_Group, U16 AxisNum, U16* NodeID, U16* SlotID, I32 *DistArrary, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tphase1, F64 Tphase2,U16 m_curve,U16 m_r_a); //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs;
//I16 PASCAL _DMC_01_multi_axes_move(U16 CardNo,U16 AxisNum, U16* NodeID, U16* SlotID, I32 *DistArrary, I32 StrVel, I32 MaxVel, F64 Tacc, F64 Tdec,U16 m_curve,U16 m_r_a);  //m_curve1: T-Curve,2: S-Curve m_r_a0:rel 1:abs 

//2019-04-02
I16 PASCAL _DMC_01_G31_Set_Info(U16 CardNo, U16 u16_Group, U16 NodeID, U16 SlotID, U16 u16_DiPolarity, U16 u16_DiBitNo, F64 f64_McDec, U16 enable);
 
//2019-04-02
I16 PASCAL _DMC_01_G31_Get_Fbk(U16 CardNo, U16 u16_Group, U16 *pu16_State, I32 *pi32_Fbk, U16* enable);

//2019-04-01
I16 PASCAL _DMC_01_get_enable_record_mode(U16 CardNo, U16* enable,U16* mode);



//2019-05-16		
//========DI Motion Home========= 
I16 PASCAL _DMC_01_Remote_Limit_Config(U16 CardNo, U16 LimitNo, U16 AxisNodeID, U16 AxisSlotID, U16 DINodeID, U16 DISlotID, U16 PELBitNo, U16 NELBitNo, U16 ORGBitNo);
I16 PASCAL _DMC_01_Remote_Limit_Edge_Trigger_Level(U16 CardNo, U16 LimitNo, U16 PositiveLimt, U16 NegativeLimit, U16 HomeSensor);
I16 PASCAL _DMC_01_Remote_Limit_Enable(U16 CardNo, U16 LimitNo, U16 Enable);
I16 PASCAL _DMC_01_Remote_Limit_Status(U16 CardNo, U16 LimitNo, U16* PEL_Trigger_sts, U16* NEL_Trigger_sts, U16* ORG_Trigger_sts, I16* Motion_Dir, U16* Limit_Status);


I16 PASCAL _DMC_01_Home_Axis_Config(U16 CardNo, U16 HomeNo, U16 NodeID, U16 SlotID, U16 Mode, I32 Offset, U32 FirstVel, U32 SecondVel, F64 Tacc, U16 Dir, I32 Shift);
I16 PASCAL _DMC_01_Home_Move(U16 CardNo, U16 HomeNo, U16 u16_LimitNo, U16 Enable);
I16 PASCAL _DMC_01_Home_Status(U16 CardNo, U16 HomeNo, U16 *Status);

//2019-05-24
I16 PASCAL _DMC_01_feedrate_overwrite2(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode, I32 New_Speed);

//2018-06-04
I16 PASCAL _DMC_01_set_rm_mpg_axes_amf_enable(U16 CardNo, U16 MasterNodeID, U16 MasterSlotID, U16* NodeID, U16* SlotID,U16 enable,U16 pulser_ratio,U32 *ratio,U32 *slop,U32 *denominator);

//2019-06-14
I16 PASCAL _DMC_01_set_tl(U16 CardNo,U16 NodeID,U16 SlotID, U16 Enable);


//2019-06-20
I16 PASCAL _DMC_01_change_pos_and_vel(U16 CardNo, U16 NodeID, U16 SlotID, I32 i32_TargetPos, I32 i32_TargetVel, F64 f64_TransTime); 


//2020-04-15
//I16 PASCAL _DMC_Qep_set_axis_command_enable(U16 CardNo, U16* CompareChannel, U16* NodeID, U16* SlotID, U16* enable, U16 pulser_ratio, U32* ratio, U32* slop, U32* denominator);
I16 PASCAL _DMC_Qep_set_axis_command_enable(U16 CardNo, U16 CompareChannel, U16 NodeID, U16 SlotID, U16 enable, U16 pulser_ratio, U32 ratio, U32 slop, U32 denominator);

//2020-04-17
I16 PASCAL _DMC_Qep_get_axis_command_enable(U16 CardNo, U16* CompareChannel, U16* NodeID, U16* SlotID, U16* enable, U16* pulser_ratio, U32* ratio, U32* slop, U32* denominator);


//_DMC_MP1_set_mpg_axis_enable(U16 CardNo, U16* NodeID, U16* SlotID, U16 enable, U16 pulser_ratio, U32* ratio, U32* slop, U32* denominator);
	
I16 PASCAL _DMC_01_get_position_without_Compensation(U16 CardNo, U16 NodeID,U16 SlotID, I32* pos);






/*

//2017-11-27  ????KDT (?????M??)

I16 PASCAL _DMC_Qep_set_mpg_axis_enable(U16 CardNo, U16 CompareChannel, U16 NodeID, U16 SlotID, U16 enable, U16 pulser_ratio, U32 ratio, U32 slop, U16 denominator);

//2017-11-30
I16 PASCAL _DMC_Qep_get_mpg_axis_enable(U16 CardNo, U16* CompareChannel, U16* NodeID, U16* SlotID, U16* enable, U16* pulser_ratio, U32* ratio, U32* slop, U16* denominator);

//2017-11-30
I16 PASCAL _DMC_Qep_get_mpg_axis_cnt(U16 CardNo, U16 compare_channel, I32* cnt);//B01 QEP

//2017-11-30
I16 PASCAL _DMC_Qep_set_mpg_clear(U16 CardNo ,U16 compare_channel);//B01 QEP clear


*/




#if defined __cplusplus
}
#endif
