#include "l6470duino.h"

using namespace l6470duino;

void driver::init(int numDevice, bool waitBusy)
{
	hardware_init();

	mNumDevice	= numDevice;
	mWaitBusy	= waitBusy;
 
	resetDriver(0x0);
}

void driver::setCS(int pin) {mCsPin = pin;}
void driver::setBusyPin(int pin) {mBusyPin = pin;}
	
void driver::resetDriver(int multi)
{
	for (int i = 0;i < 4;i++) send(CMD_NULL , 0, multi);
	send(CMD_RESET, 0, multi);
}

/*================Drive Methods================*/

void driver::Run(long speed, bool dir, int multi)
	{send(dir ? CMD_RUN_FWR : CMD_RUN_RVS, speed, multi);}

void driver::Goto(long pos, int multi)
	{send(CMD_GOTO, pos, multi);}

void driver::Move(long angle, bool dir, int multi)
	{send(dir ? CMD_MOVE_FWR : CMD_MOVE_RVS, angle, multi);}

void driver::SoftStop(int multi){send(CMD_STOP_SOFT, 0, multi);}
void driver::HardStop(int multi){send(CMD_STOP_HARD, 0, multi);}
void driver::SoftHiz (int multi){send(CMD_STOP_SHIZ, 0, multi);}
void driver::HardHiz (int multi){send(CMD_STOP_HHIZ, 0, multi);}
void driver::goHome	 (int multi){send(CMD_GO_HOME, 0, multi);}
void driver::goMark  (int multi){send(CMD_GO_MARK, 0, multi);}
void driver::resetPos(int multi){send(CMD_RESET_POS, 0, multi);}


/*================Setting Methods================*/

void driver::voltage_hold(long volt, int multi) {send(CMD_KVAL_HOLD, volt, multi);}
void driver::voltage_run (long volt, int multi) {send(CMD_KVAL_RUN, volt, multi);}
void driver::voltage_acc (long volt, int multi) {send(CMD_KVAL_ACC, volt, multi);}
void driver::voltage_dec (long volt, int multi) {send(CMD_KVAL_DEC, volt, multi);}
void driver::setAcc(long acc, int multi = 0x0){send(CMD_ACCEL, acc, multi);}
void driver::setDec(long dec, int multi = 0x0) { send(CMD_DECEL, dec, multi); }
void driver::setMaxSpeed(int speed, int multi) {send(CMD_MAXSPD, speed, multi);}
void driver::setMinSpeed(int speed, int multi) {send(CMD_MINSPD, speed, multi);}
void driver::setStepMode(int mode, int multi) {send(CMD_STEPMODE, mode, multi);}
void driver::waitBusy(){if (mWaitBusy) while (isBusy()){}}

/*================Protected================*/
void driver::send(command cmd, long arg, int multi)
{
	int c = (int)cmd;

	waitBusy();
	if (numBits[c] == 0xFF)
	{
		//Undefined Command
	}
	else
	{
		int  numByte  = 1 + int(numBits[c] / 8) + ((numBits[c] % 8 == 0) ? 0 : 1);

		//Make data
		uint8_t data[numByte];
		data[0] = c;
		for (int i = 1;i < numByte;i++)
			data[i] = (arg >> (8 * (numByte - 1 - i))) & 0xFF;

		for (int sigId = 0;sigId < numByte;sigId++)
		{
			spi_open();
			for (int devId = 0;devId < mNumDevice;devId++)
			{ 
        if (multi == 0x0)                   spi_send(data[sigId]);
        else if (((multi >> devId) & 0x1) == 1)  spi_send(data[sigId]);
        else spi_send(0x0);
			}
			spi_close();
		}
	
	}
}

driver::driver()
{
	for (int i = 0;i < 255;i++) numBits[i] = 0xFF;

	numBits[CMD_MOVE_FWR]	= 22;
	numBits[CMD_MOVE_RVS]	= 22;
	numBits[CMD_RUN_FWR]	= 20;
	numBits[CMD_RUN_RVS]	= 20;
	numBits[CMD_GOTO]		= 22;
	numBits[CMD_GOTO_FWR]	= 22;
	numBits[CMD_GOTO_RVS]	= 22;
	numBits[CMD_STOP_SOFT]	= 0;
	numBits[CMD_STOP_HARD]	= 0;
	numBits[CMD_STOP_SHIZ]	= 0;
	numBits[CMD_STOP_HHIZ]	= 0;
	numBits[CMD_GO_HOME]	= 0;
	numBits[CMD_GO_MARK]	= 0;
	numBits[CMD_RESET_POS]	= 0;
 	numBits[CMD_RESET] = 0;
 	numBits[CMD_NULL] = 0;

	numBits[CMD_ABSPOS] 	= 22;
	numBits[CMD_EL_POS] 	= 9;
	numBits[CMD_MARK]		= 22;
	numBits[CMD_SPEED]		= 20;
	numBits[CMD_ACCEL]		= 12;
	numBits[CMD_DECEL]		= 12;
	numBits[CMD_MAXSPD]		= 10;
	numBits[CMD_MINSPD] 	= 13;
	numBits[CMD_FS_SPEED]	= 10;
	numBits[CMD_STEPMODE]	= 8;
	numBits[CMD_ALARM_EN]	= 8;

	numBits[CMD_KVAL_HOLD]	= 8;
	numBits[CMD_KVAL_RUN]	= 8;
	numBits[CMD_KVAL_DEC]	= 8;
	numBits[CMD_KVAL_ACC]	= 8;
	numBits[CMD_OCD_TH]		= 4;
	numBits[CMD_STALL_TH]	= 7;
}

/*===========Hardware dependences===========*/
bool driver::isBusy()	{return !digitalRead(mBusyPin);}
void driver::spi_open()	
{
  digitalWrite(mCsPin, LOW);
}
void driver::spi_close()
{
  digitalWrite(mCsPin, HIGH);
}
void driver::spi_send(uint8_t data)
{
  SPI.transfer(data);
}
void driver::hardware_init()
{
  #define USE_UNO 
  
  //for ESP8266 set
  #ifdef USE_ESP8266
  #define SPI_SCK 14
  #define SPI_MOSI 13
  #define SPI_MISO 12
  #define SPI_CS 15
  #endif
  
  //Arduino Uno
  #ifdef USE_UNO
  #define SPI_SCK 13
  #define SPI_MOSI 12
  #define SPI_MISO 11
  #define SPI_CS 10
  #endif
  
  pinMode(SPI_CS  , OUTPUT);
  pinMode(SPI_SCK , OUTPUT);
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_MISO, INPUT);
  mCsPin = SPI_CS;

	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setBitOrder(MSBFIRST);
}
