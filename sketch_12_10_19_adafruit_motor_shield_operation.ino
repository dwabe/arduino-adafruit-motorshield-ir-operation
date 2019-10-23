#include <IRremote.h>

#define forward_button 6375  // code received from next button
#define backward_button 19125 // code received from previous button
#define turn_left_button 26775
#define turn_right_button 45135
#define rotate_left_button 4335  // code received from left button
#define rotate_right_button 23205 // code received from right button
#define stop_button 14535   // code received from stop button

int receiver_pin = 2;      //output pin of IR receiver to pin 2 of arduino
IRrecv receiver(receiver_pin); //Arduino will take output of IR receiver from pin 2
decode_results output;


#include <AFMotor.h>

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);


void setup() {
  Serial.begin(9600);
  receiver.enableIRIn(); // Start to take the output from IR receiver
}
/*
void loop() {
  goForward();
  delay(3000);
  goBackward();
  delay(3000);
  goStop();
  delay(3000);
}
*/

void goForward() {
  motor1.run(FORWARD);
  motor1.setSpeed(240);
  motor2.run(FORWARD);
  motor2.setSpeed(240);
}

void goBackward() {
  motor1.run(BACKWARD);
  motor1.setSpeed(240);
  motor2.run(BACKWARD);
  motor2.setSpeed(240);
}

void turnRight() {
  motor1.run(FORWARD);
  motor1.setSpeed(240);
  motor2.run(FORWARD);
  motor2.setSpeed(190);
}

void turnLeft() {
  motor1.run(FORWARD);
  motor1.setSpeed(190);
  motor2.run(FORWARD);
  motor2.setSpeed(240);
}

void rotateRight() {
  motor1.run(FORWARD);
  motor1.setSpeed(190);
  motor2.run(BACKWARD);
  motor2.setSpeed(190);
}

void rotateLeft() {
  motor1.run(BACKWARD);
  motor1.setSpeed(190);
  motor2.run(FORWARD);
  motor2.setSpeed(190);
}

void goStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  if (receiver.decode(&output)) {
    unsigned int value = output.value;
    Serial.println(value);
    switch(value) {
      case forward_button:
           goForward();
           break;
      case backward_button:
           goBackward();
           break;
      case turn_left_button:
           turnLeft();
           break;
      case turn_right_button:
           turnRight();
           break;
      case rotate_left_button: 
           rotateLeft();
           break;
      case rotate_right_button:
           rotateRight();
           break;
      case stop_button:
           goStop();
           break;
    }
    receiver.resume();
  }
}
