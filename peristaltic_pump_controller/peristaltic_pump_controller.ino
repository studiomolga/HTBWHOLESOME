#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "statemachine.h"

#define PWM_FREQ 10               // do not change
#define WIRE_CLOCK 100000         // do not change

//#define USE_SERIAL
#define NUM_PUMPS 4               // set the number of pumps connected, should typically be 4
#define FADE_PERIOD 3000          // sets the time it takes to reverse direction in milliseconds
#define WAIT_PERIOD 25000         // sets the time it remains in a single direction in milliseconds

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
StateMachine stateMachine = StateMachine();
StateType previousState = LEFT;

void setup() {
  #ifdef USE_SERIAL
    Serial.begin(9600);
  #endif

  // initialize the pwm controller
  pwm.begin();
  pwm.setPWMFreq(PWM_FREQ); 
  Wire.setClock(WIRE_CLOCK);

  stateMachine.addState(LEFT, &leftLoop, &leftInit);
  stateMachine.addState(RIGHT, &rightLoop, &rightInit);
  stateMachine.addState(WAIT, &waitLoop, &waitInit);
  stateMachine.setState(LEFT);
}

void loop() {
  stateMachine.update();
}

// ----------------------- inits
void leftInit() {
  #ifdef USE_SERIAL
    Serial.println(F("LEFT STATE"));
  #endif
}

void rightInit() {
  #ifdef USE_SERIAL
    Serial.println(F("RIGHT STATE"));
  #endif
}

void waitInit() {
  #ifdef USE_SERIAL
    Serial.println(F("WAIT STATE"));
  #endif
}

// ----------------------- loops
void leftLoop() {
  int16_t amount = map(constrain(stateMachine.getStateRunTime(), 0, FADE_PERIOD), 0, FADE_PERIOD, -4095, 4095);
  if(amount < 0){
    updatePumps(0, (uint16_t)abs(amount));  
  } else {
    updatePumps((uint16_t)amount, 0);
  }

  if(amount == 4095){
    previousState = LEFT;
    stateMachine.setState(WAIT);
  }
}

void rightLoop() {
  int16_t amount = map(constrain(stateMachine.getStateRunTime(), 0, FADE_PERIOD), 0, FADE_PERIOD, -4095, 4095);
  if(amount < 0){
    updatePumps((uint16_t)abs(amount), 0);  
  } else {
    updatePumps(0, (uint16_t)amount);
  }

  if(amount == 4095){
    previousState = RIGHT;
    stateMachine.setState(WAIT);
  }
}

void waitLoop() {
  if(stateMachine.getStateRunTime() >= WAIT_PERIOD){
     switch(previousState){
      case LEFT: 
        stateMachine.setState(RIGHT);
        break;
      case RIGHT:
        stateMachine.setState(LEFT);
        break;   
     }
  }
}

void updatePumps(const uint16_t &in1, const uint16_t &in2){
  for(int i = 0; i < NUM_PUMPS * 2; i += 2){
    #ifdef USE_SERIAL
      Serial.print(F("pump: "));
      Serial.print(i);
      Serial.print(F(" | in1: "));
      Serial.print(in1);
      Serial.print(F(" | in2: "));
      Serial.print(in2);
      Serial.println();
    #endif
    
    pwm.setPWM(i, 0, in1);
    pwm.setPWM(i + 1, 0, in2);
  }
}
