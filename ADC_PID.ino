#include <PID_v1.h>
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;
double angle = 0;
//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);  
void setup() 
{
pinMode(A3, INPUT);
Input = analogRead(A3); 
Setpoint = 100;
  // put your setup code here, to run once:

Serial.begin(9600);
 // Serial.print("Setup Complete" );
//Define the aggressive and conservative Tuning Parameters

 //turn the PID on
myPID.SetMode(AUTOMATIC);
}

void loop() 
{
  // Code which takes input and performs PID on: 

  double gap = abs(Setpoint-Input); //distance away from setpoint
  if(gap<10)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }
 Serial.println(Input);  // Prints Input
  myPID.Compute();  // Actual computation of PID
Input = analogRead(A3); //Reads the analog value on pin A3 into Input
Serial.println(Output); // Prints computation 
}
