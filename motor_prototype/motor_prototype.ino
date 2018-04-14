

/**
 * Title: Cat's Conundrum 
 * Version: a1.1.0
 * Author: Dillon Tice
 * Description: Basic control for the vehicle. Provides support for moving forward, backward, and turning.  Uses pins 4-7
 * Usage: Arrow keys:
 *    UP: Both motors on, forward
 *    DOWN: Both motors on, backward
 *    LEFT: Left motor backwards, right motor forwards (0-point turn)
 *    RIGHT: Right motor backwards, left motor forwards (0-point turn)
 *    UP/DOWN+LEFT/RIGHT: One motor is double the speed of the other, but neither are stopped (Rounded turn)
 *    SHIFT+ANY: Double speed
 */

//right side motor control
int IN1 = 7;
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;

//PWM pins
int ENA = 9; //enable right
int ENB = 3; //enable left

String powered;
int flag = 0;
int leftPower = 125;
int rightPower = 125;
int boost = 255;


//TODO: analogWrite(ENA, 0-255)
//TODO: analogWrite(ENB, 0-255)
//digitalWrite(
void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
}

void processData(String input){
  leftPower, rightPower = 125;
  if(input.indexOf(5) == 1){
    leftPower, rightPower = boost;
  }
  int command = input.substring(0,3).toInt();
  
  switch(command){
    case 1000: //forward
      startCar();
      break;
    case 0100: //reverse
      stopCar();
      break;
    case 0010: //0-point left
      leftTurn();
      break;
    case 0001: //0-point right
      rightTurn();
      break;
    case 1010: //Rounded forward left
      leftPower = (rightPower/2);
      rightTurn();
      break;
    case 1001: //Rounded right
      rightPower = (leftPower/2);
      rightTurn();
      break;
    default:
      break;
  }
}

void startCar(){
  analogWrite(ENA, leftPower);
  analogWrite(ENB, rightPower);
  digitalWrite(IN1, HIGH); //7,6,5,4
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stopCar(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void leftTurn(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void rightTurn(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
//Constantly updating speed of either side
void loop(){
  if(Serial.available() > 0){
    powered = Serial.readString();
    Serial.println(powered);
  }
  processData(powered);
}
