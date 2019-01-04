 #include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
  
// we define motors pins.
int leftMotorEnable = 10; //ENA
int leftMotorForward = 6; //IN1
int leftMotorBackward = 7; //IN2

int rightMotorEnable = 11; //ENB
int rightMotorForward = 9; //IN4
int rightMotorBackward = 8; //IN3

// initialise functions
void stopMoving();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void spin();

//used for testing
int test = 1; 

//define the ultrasonic sensor pins.
int echoPin = 12;
int triggerPin = 13;

// the speed of sound in air.
const float speedOfSound = 331.2;

//bluetooth setting
int motion;
int call = 0;
int motionStop = 0;

void setup() {
  Serial.begin(9600);  // Debugging only
  BTSerial.begin(9600);

  pinMode(leftMotorEnable, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);

  pinMode(rightMotorEnable, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  
 }


void loop() {
    //if some data is sent, reads it and saves in motion
    if(BTSerial.available() > 0){     
      motion = BTSerial.read();   
      call=0;
    }

    // activate the ultrasonic sensor
    digitalWrite(triggerPin, LOW);
    delay(2);
    digitalWrite(triggerPin, HIGH);
    delay(10);  
    digitalWrite(triggerPin, LOW);

    // Retrive the time take for the pulse to come back to the sensor
    float echoTime = pulseIn(echoPin, HIGH) / 1000000.000;
    // Calculate the distance between the sensor and an obstacle in cm
    float distanceToImpact = echoTime * speedOfSound * 100 / 2;
   // Serial.print("Distance:"); Serial.println(distanceToImpact);

    //int distanceToImpact = 98; //remove this line in china
   
    if (distanceToImpact >= 10){ 
    
    // if the motion is 'F' the DC motor will go forward
    if (motion == 'F') {
          moveForward();
        if(call == 0){
          Serial.println("Moving Forwards");
          call=1;
        }
    }
    
    // if the motion is 'R' the motor will turn Right
    else if (motion == 'R') {
          turnRight();
        if(call == 0){
          Serial.println("Turning Right");
          call=1;
        }
        delay(1500);
        motion=3;
        motionStop=1;
    }
    
    // if the motion is 'S' the motor will Stop
    else if (motion == 'S' || motionStop == 1) {
          stopMoving();
        if(call == 0){
          Serial.println("Stopping");
          call=1;
        }
        motionStop=0;
    }
    // if the motion is 'L' the motor will turn left
    else if (motion == 'L') {
          turnLeft();
        if(call == 0){
          Serial.println("Turning Left");
          call=1;
        }
        delay(1500);
        motion=3;
        motionStop=1;
    }
    // if the motion is 'B' the motor will Reverse
    else if (motion == 'B') {
            moveBackward();
        if(call == 0){
          Serial.println("Reversing");
          call=1;
        }
    }

    }
    else if (distanceToImpact < 10){
      stopMoving();
      moveBackward();
    }
    
    //For debugging purpose
    //Serial.print("motion:");   Serial.println(motion);
    //Serial.print("call:");   Serial.println(call);    
    //Serial.print("motion stop:");   Serial.println(motionStop);  
}

//Function for stoping the car
void stopMoving() {
  digitalWrite(leftMotorEnable, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);

  digitalWrite(rightMotorEnable, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

//Function for moving the car forward
void moveForward() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);

}

//Function for moving the car backward
void moveBackward() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  
  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

//Function for turning the car left
void turnLeft() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);

}

//Function for turning the car right
void turnRight() {

  analogWrite(leftMotorEnable, 255);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 255);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

//Function for spinning the car
void spin(){
  
  analogWrite(leftMotorEnable, 100);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);

  analogWrite(rightMotorEnable, 100);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}
