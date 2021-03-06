/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
uint8_t val = 0;

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  EEPROM.begin(512);
}

void loop()
{
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);

  if(val < 0x10)
  {
    Serial.print("0x0");
  }else{
    Serial.print("0x");
  }
  Serial.print(val, HEX);
  Serial.print(" written to addr ");
  Serial.println(addr);

  // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 0 when we hit 512.
  // save all changes to the flash.
  val++;
  addr = addr + 1;
  if (addr == 512)
  {
    addr = 0;
    EEPROM.commit();
    Serial.println("FINISHED");
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    while(1);
  }

  delay(100);
}
