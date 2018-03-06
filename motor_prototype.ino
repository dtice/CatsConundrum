/**
 * Title: Cat's Conundrum 
 * Version: a1.0.0
 * Author: Dillon Tice
 * Description: Basic control for the vehicle. Provides support for moving forward, backward, and turning.  Uses pins 4-7
 */

//right side motor control
int ctrl_IN1 = 7;
int ctrl_IN2 = 6;
int ctrl_ENABLE1 = 3; //enable right
//left side motor control
int ctrl_IN3 = 5;
int ctrl_IN4 = 4;
int ctrl_ENABLE2 = 2; //enable left
int powered = 0;
int flag = 0;


//TODO: Write a function that when spacebar is pressed, the car turns on/off

void setup(){
  pinMode(ctrl_IN1, OUTPUT);
  pinMode(ctrl_IN2, OUTPUT);
  pinMode(ctrl_IN3, OUTPUT);
  pinMode(ctrl_IN4, OUTPUT);
  pinMode(ctrl_ENABLE1, OUTPUT);
  pinMode(ctrl_ENABLE2, OUTPUT);
  Serial.begin(9600);
}

void testLoop(){
  digitalWrite(ctrl_ENABLE1, HIGH);
  digitalWrite(ctrl_ENABLE2, HIGH);
  startCar();
  delay(1000);
  stopCar();
  delay(1000);
  leftTurn();
  delay(1000);
  rightTurn();
  delay(1000);
}

void startCar(){
  digitalWrite(ctrl_IN1, HIGH); //7,6,5,4
  digitalWrite(ctrl_IN2, LOW);
  digitalWrite(ctrl_IN3, HIGH);
  digitalWrite(ctrl_IN4, LOW);
}
void stopCar(){
  digitalWrite(ctrl_IN1, LOW);
  digitalWrite(ctrl_IN2, LOW);
  digitalWrite(ctrl_IN3, LOW);
  digitalWrite(ctrl_IN4, LOW);
}
void leftTurn(){
  digitalWrite(ctrl_IN1, LOW);
  digitalWrite(ctrl_IN2, HIGH);
  digitalWrite(ctrl_IN3, HIGH);
  digitalWrite(ctrl_IN4, LOW);
}
void rightTurn(){
  digitalWrite(ctrl_IN1, HIGH);
  digitalWrite(ctrl_IN2, LOW);
  digitalWrite(ctrl_IN3, LOW);
  digitalWrite(ctrl_IN4, HIGH);
}

void loop(){
  if(Serial.available() > 0){
    powered = Serial.read();
    Serial.println(powered);
  }
  switch(powered){
    case 'w':
      startCar();  
      Serial.println("Start");
      break;
    case 'a':
      leftTurn();
      Serial.println("Stop");
      break;
    case 's':
      stopCar();
      Serial.println("Left");
      break;
    case 'd':
      rightTurn();
      Serial.println("Right");
      break;
    default:
      stopCar();
      Serial.println("Stopped");
      break;
  }
}
