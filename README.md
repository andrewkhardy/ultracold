# ultracold
A PHY479 final project to exert power control over a laser cooling system. the system consisted of a chipKIT uC32 and an AD5780 Evaluation Board Digital to Analog converter. 
The two programs, ADC.ino and DACv3.ino serve to do the ADC & PID, followed by the DAC SPI output. The DAC uses these drivers
https://wiki.analog.com/resources/tools-software/uc-drivers/renesas/ad5780

In addition, there is a program to output arrays of ADC values in order to test bandwidth and a Python program to read in these values. Finally there is a simulated PID program developed from the AutoTune PID Arduino library. This can also be read out via the Python output. 
