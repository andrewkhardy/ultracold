#include <Arduino.h>
#include <AD5780.h>

void setup() {
  Serial.begin(115200);
  Serial.println("FIRMWARE STARTUP");

  /* same setup as in the RL78G13 driver example's Main.c 
  This Intitializes the DAC
  */
  if (AD5780_Init()) {
    Serial.println("AD5780_Init OK");
  } else {
    Serial.println("AD5780_Init Err");
  }

  /* Resets the device to its power-on state. */
  AD5780_SoftInstruction(AD5780_SOFT_CTRL_RESET);

  /* Enables the DAC output. */
  AD5780_EnableOutput(1);

  /* The DAC register is set to use offset binary coding. */
  AD5780_Setup(AD5780_CTRL_BIN2SC);

  /* Sets the value to which the DAC output is set when CLEAR is enabled. */
  AD5780_SetRegisterValue(AD5780_REG_CLR_CODE, AD5780_CLR_CODE_DATA(0x20000),
      3);

  /* Performs a soft CLEAR operation. */
  AD5780_SoftInstruction(AD5780_SOFT_CTRL_CLR);

  /* Reads and displays the internal registers. */
  /* Read DAC. */
  long result = AD5780_GetRegisterValue(AD5780_REG_DAC, 3);
  result = (result & 0xFFFFC) >> 2;
  Serial.print("DAC REG: ");
  Serial.println(result, HEX);

  /* Read Control. */
  result = AD5780_GetRegisterValue(AD5780_REG_CTRL, 3);
  result = (result & 0x3E);  // Only Bits 5 through 1 are holding information.
  Serial.print("CTRL REG: ");
  Serial.println(result, HEX);

  /* Read ClearCode. */
  result = AD5780_GetRegisterValue(AD5780_REG_CLR_CODE, 3);
  result = (result & 0xFFFFC) >> 2;
  Serial.print("CLEAR CODE: ");
  Serial.println(result, HEX);
}

long dacVal = 0;
long step = 0;

void loop() {
  /* generate a triangle signal.   */
  if (dacVal >= (0x00037000 - step)) {
    step = -256;
  } else if (dacVal <= (0x00000000 - step)) {
    step = 256;
  }
  dacVal += step;

  AD5780_SetDacValue(dacVal);
  delayMicroseconds(1000);
}
