/*0-for_cli-*/
	BIND_PROTO_CMD(61001,sw_get_user_count,Cmessage,sw_get_user_count_out,0x945b505b,1)
	BIND_PROTO_CMD(62001,sw_report_online_info,sw_report_online_info_in,Cmessage,0x9d002133,1)
	BIND_PROTO_CMD(62002,sw_report_user_onoff,sw_report_user_onoff_in,Cmessage,0xa23fe386,1)
	BIND_PROTO_CMD(62004,sw_noti_across_svr,sw_noti_across_svr_in,sw_noti_across_svr_out,0xf55ca111,3)
	BIND_PROTO_CMD(62006,sw_get_recommend_svr_list,Cmessage,sw_get_recommend_svr_list_out,0x4940b505,1)
	BIND_PROTO_CMD(64002,sw_get_ranged_svrlist,sw_get_ranged_svrlist_in,sw_get_ranged_svrlist_out,0xe107fe35,5)
