#include "l6470duino_definitions.h"
#include <SPI.h>

#ifndef _l6470_duino
#define _l6470_duino

namespace l6470duino
{
	class driver {

	public:
		
		driver();	

		/*=======Preset Methods=======*/
		void init		(int numDevice = 1, bool waitBusy = false);
		void setCS		(int pin);
		void setBusyPin (int pin);
		void resetDriver(int multi = 0x0);
		
		/*=======Drive Methods=======*/
		void waitBusy();

		void Run 		(long speed, bool dir, int multi = 0x0);
		void Goto		(long pos, int multi = 0x0);
		void Move		(long angle, bool dir, int multi = 0x0);
		void SoftStop	(int multi = 0x0);
		void HardStop	(int multi = 0x0);
		void SoftHiz	(int multi = 0x0);
		void HardHiz	(int multi = 0x0);
		/*
			.
			.
			.
		*/

		/*=======Setting Methods=======*/
		void voltage_hold(long volt, int multi = 0x0);
		void voltage_run (long volt, int multi = 0x0);
		void voltage_acc (long volt, int multi = 0x0);
		void voltage_dec (long volt, int multi = 0x0);
		void setMaxSpeed(int speed, int multi = 0x0);
		void setMinSpeed(int speed, int multi = 0x0);
		void setStepMode(int mode, int multi = 0x0);
		/*
			.
			.
			.
		*/

		/*=======Hardware dependences=======*/
		bool isBusy();
		void hardware_init();
		void spi_open();
		void spi_close();
		void spi_send(uint8_t data);

protected:
		int  	numBits[0xFF];
		int 	mCsPin		= 10;
		int 	mBusyPin	= 9;
		int 	mNumDevice	= 1;
		bool 	mWaitBusy	= false;

		//flag = 0x0は一括送信
  public:
		void send(command cmd, long arg, int multi);
	};

};

#endif
