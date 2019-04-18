//Reads up to 100 values
const unsigned int numReadings = 1000;
unsigned int analogVals[numReadings];
unsigned int i = 0;

void setup()
{
  pinMode(A3, INPUT);
  Serial.begin(115200);
}
// Establish Input Pin and Rate of OutPut
void loop()
// Code to fill array, output it, and restart
{
    analogVals[i] = analogRead(A3);
    i++;
    if (i>= numReadings)
    {
      for (int j = 0; j < i; j++) {
      Serial.println(analogVals[j]);
      }  
     
      i = 0; //reset to beginning of array, so you don't try to save readings outside of the bounds of the array
    }
  }
