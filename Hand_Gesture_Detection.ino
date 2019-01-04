//MOISES BARBERA RAMOS
//"CODING AND ROBOTICS SOCIETY" VICE-PRESIDENT
//14-06-2018 LIVERPOOL, UK - SHANGHAI, CHINA

#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // TX | RX

//set the three axis of the accelerometre to the different pins on the motherboard
int xInputPin = 1;
int yInputPin = 2;
int zInputPin = 3;

float xRestingValue;
float yRestingValue;
float zRestingValue;

int state = 0;

void setup() {
  //to run code once:
  pinMode(xInputPin, INPUT);
  pinMode(yInputPin, INPUT);
  pinMode(zInputPin, INPUT);

//defining the bluetooth and setting it to allow checking on the Serial Monitor
  Serial.begin(9600);
  BTserial.begin(38400);

  float xSum = 0;
  float ySum = 0;
  float zSum = 0;

  delay(3000);
  
  //Modifying the produced data to be readable
  for(int i = 0; i < 1000; i++) {
    xSum += analogRead(xInputPin);
    ySum += analogRead(yInputPin);
    zSum += analogRead(zInputPin);
  }

  xRestingValue = xSum / 1000;
  yRestingValue = ySum / 1000;
  zRestingValue = zSum / 1000;
}

void loop() {

    int xInput = (int) analogRead(xInputPin) - xRestingValue;
    int yInput = (int) analogRead(yInputPin) - yRestingValue;
    int zInput = (int) analogRead(zInputPin) - zRestingValue;

//Assigning the data produced an action (to send which signal to the receiver - Smart_Car.ino)
  if(BTserial.available()) {
    if(xInput <= 15 && xInput >= -15 && yInput  <= 15 && yInput >= -15) {
    //stationary code 
    BTserial.write('S'); Serial.println("s");
    delay(2);
    
  } else if(yInput > 15 && yInput > xInput && yInput > -xInput) {
    //forward code
    BTserial.write('F'); Serial.println("f");
    delay(2);
    
  } else if(yInput < xInput && yInput < -xInput && yInput < -15) {
    //backward code
    BTserial.write('B'); Serial.println("b");
    delay(2);
   
  } else if (xInput < -15 && xInput < yInput && xInput < -yInput) {
    //right code
    BTserial.write('R'); Serial.println("r");
    delay(2);
    
  } else if(xInput > 15 && xInput > yInput && xInput > -yInput) {
    //left code
    BTserial.write('L'); Serial.println("l");
    delay(2);
  } else {
  }
  }
}
