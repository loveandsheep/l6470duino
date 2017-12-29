#ifndef _l6470_duino_defs
#define _l6470_duino_defs

namespace l6470duino
{
enum command{
		CMD_NULL		= 0x00,

		//Drives
		CMD_MOVE_FWR	= 0X40,
		CMD_MOVE_RVS	= 0X41,
		CMD_RUN_FWR		= 0x50,
		CMD_RUN_RVS		= 0x51,
		CMD_GOTO		= 0X60,
		CMD_GOTO_FWR	= 0X69,
		CMD_GOTO_RVS	= 0X68,
		CMD_STOP_SOFT	= 0XB0,
		CMD_STOP_HARD	= 0XB8,
		CMD_STOP_SHIZ	= 0XA0,
		CMD_STOP_HHIZ	= 0XA8,
		CMD_GO_HOME		= 0x70,
		CMD_GO_MARK		= 0x78,
		CMD_RESET_POS	= 0xD8,

		//Settings_drive
		CMD_RESET 		= 0xC0,
		CMD_ABSPOS		= 0x01,//W-Stop
		CMD_EL_POS		= 0x02,//W-Stop
		CMD_MARK		= 0x03,//W-Always
		CMD_SPEED		= 0x04,//Read-only
		CMD_ACCEL		= 0x05,//W-Stop
		CMD_DECEL		= 0x06,//W-Stop
		CMD_MAXSPD		= 0x07,//W-Always
		CMD_MINSPD		= 0x08,//W-Stop
		CMD_FS_SPEED	= 0x15,//W-Always
		CMD_STEPMODE	= 0X16,//W-HighImpedance
		CMD_ALARM_EN	= 0x17,//W-Stop

		//Settings_Electric
		CMD_KVAL_HOLD	= 0x09,//W-Always
		CMD_KVAL_RUN	= 0x0A,//W-Always
		CMD_KVAL_ACC	= 0X0B,//W-Always
		CMD_KVAL_DEC	= 0X0C,//W-Always
		CMD_OCD_TH		= 0x13,//W-Always
		CMD_STALL_TH	= 0x14//W-Always

	};
}

#endif
