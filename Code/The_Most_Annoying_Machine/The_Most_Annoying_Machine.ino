// The Most Annoying Machine
// Jonathan Jamieson
// www.jonathanjamieson.com

// This is the first version of the code. I knocked it up in an evening and it might (read WILL) be buggy. Oh, and there are few comments and the ones that do exist are probably wrong.


const int buttonPin = 3;     // the number of the pushbutton pinconst int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int accel_flag = 0;
int in_rest = 0;
unsigned long time;
unsigned long  button_switch_time ;
unsigned long  accel_time ;
  unsigned long button_delay ; 

int previous_button_state = 1;

const int ledPin =  8; 
const int buzzerPin =  7; 
const int activateswitchPin =  4; 
const int sirenPin =  10; 
 
#include <math.h>

int xpin;             
int ypin;                 
int zpin;

int state = 1; // 1 = active, 0, inactive where active means the thing is trying to flip the switch;

int x; // Acceleration in the x-direction
int y; // Acceleration in the y-direction
int z; // Acceleration in the z-direction

double magnitude_accelerometer;

// These values are used to scale the acceleration that is read from the accelerometer. This is required because the voltage varies as the Lipo drains down.
int xMin;
int yMin;
int zMin;
int xMax;
int yMax;
int zMax;

  

void setup(void) {
    pinMode(buttonPin, INPUT);  
    pinMode(buzzerPin, OUTPUT);  
    pinMode(activateswitchPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(sirenPin, OUTPUT);
    xpin = A0;
    ypin = A1;
    zpin = A2;
    
    xMin = 270; 
    yMin = 265;
    zMin = 282;
    xMax = 405;
    yMax = 400;
    zMax = 416;

    pinMode(xpin, INPUT);
    pinMode(ypin, INPUT);
    pinMode(zpin, INPUT);
    Serial.begin(57600);
  
 }
 
 void loop(void)
{

  buttonState = digitalRead(buttonPin);
  x = analogRead(xpin); 
  delay(1); 
  y = analogRead(ypin); 
  delay(1); 
  z = analogRead(zpin);
  
  
  if (buttonState == HIGH) {    
    // turn LED on:    
    if (previous_button_state==0) {      
      button_switch_time = millis();
      Serial.println("meow");
    }
   digitalWrite(buzzerPin, HIGH);    
 digitalWrite(ledPin, HIGH);   
 digitalWrite(sirenPin, HIGH);   
   previous_button_state = 1;
   in_rest = 0;
  
   
  } else {
    
    if (in_rest != 1) {
    
    if (previous_button_state == 1) {      
   
  
  button_delay = (millis()-button_switch_time);    
      button_delay = min((button_delay),3000);   
   
   Serial.println(button_delay);   
      previous_button_state = 0;    
      time = millis() + button_delay ;
      delay(30);
      
    }
    
     previous_button_state = 0;
    // turn LED off:
    digitalWrite(buzzerPin, LOW);
    digitalWrite(sirenPin, LOW);
    digitalWrite(ledPin, LOW);
    
    if (millis()>time) {
     digitalWrite(activateswitchPin, HIGH); 
     delay(30);
     digitalWrite(activateswitchPin, LOW); 
     delay(200);
    
    }
    
    }
  }
  
 
  
  
    int xAng = map(x, xMin, xMax, -90, 90);
  int yAng = map(y, yMin, yMax, -90, 90);
  int zAng = map(z, zMin, zMax, -90, 90);

  magnitude_accelerometer = sqrt(pow(xAng,2)+pow(yAng,2)+pow(zAng,2)); // Determine the magnitude of the acceleration
  
  
// Serial.println(magnitude_accelerometer);
 //delay(10);
 
 
 if (millis()>accel_time && accel_flag==1)
  if (magnitude_accelerometer<40) {
  
    digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
   in_rest = 1;
   previous_button_state=0;
  delay(5000);
  accel_flag = 0;
  } else {   
    accel_flag =0;   
  }
    
  if (magnitude_accelerometer<40 && accel_flag==0 && previous_button_state==1) {    
    accel_time = millis()+300;
    accel_flag = 1;  
  }
  

  
}


