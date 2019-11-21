#include "l6470duino.h"

l6470duino::driver Driver;

void setup() {
  // put your setup code here, to run once:
  Driver.init(1);
  Driver.voltage_acc (0xDF);
  Driver.voltage_dec (0xDF);
  Driver.voltage_run (0xDF);
  Driver.voltage_hold(0x30);

  delay(1000);
  
  Driver.Goto(5000);
  delay(5000);
  
  Driver.Run(1000, false);
  delay(1000);
  
  Driver.SoftStop();
  delay(1000);
  
  Driver.Goto(0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
