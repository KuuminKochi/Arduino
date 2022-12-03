#include <Servo.h>
#include <IRremote.h>

#define DECODE_NEC 1
#define IR_PIN 3

Servo lightSwitchServo;

int lightSwitchServoPin = 2;
int defaultPos = 60;
int lightON = 90;
int lightOFF = 30;
int lightDelay = 200;
bool lightSwitch = true;

int IRreceivepin = 22;

void setup() {
  Serial.begin(9600);   
  
  lightSwitchServo.attach(lightSwitchServoPin); 
  IrReceiver.begin(IRreceivepin, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (IrReceiver.decode()) {
    Serial.print("COMMAND is ");
    Serial.println(IrReceiver.decodedIRData.command);
    IrReceiver.resume();

  }

  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command) {
    case (22): {
      lightSwitchServo.write(lightOFF); 
      delay(lightDelay);
      lightSwitchServo.write(defaultPos); 
      delay(lightDelay);
      lightSwitch = false;
      break;
    }
    case (12): {
      lightSwitchServo.write(lightON);              
      delay(lightDelay);
      lightSwitchServo.write(defaultPos); 
      delay(lightDelay);
      
      lightSwitch = true;
      break;
    }

    case (21): {
      if (lightSwitch == true) {
        lightSwitchServo.write(lightON); 
        delay(lightDelay);
        lightSwitchServo.write(defaultPos); 
        delay(lightDelay);
        lightSwitch = false;
        break;
      }
      if (lightSwitch == false) {
        lightSwitchServo.write(lightOFF); 
        delay(lightDelay);
        lightSwitchServo.write(defaultPos); 
        delay(lightDelay);
        lightSwitch = true;
        break;
      }
    }
    Serial.println(lightSwitch);
    IrReceiver.resume();
    }
  }
}
