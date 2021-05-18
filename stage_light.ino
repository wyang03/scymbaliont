#include <Servo.h>
#include <DmxSimple.h>

Servo myservo;

int ldr0Val, ldr1Val, ldr2Val, ldr3Val, ldr4Val; //reading from the ldr sensor via xbee
float w0 = 0.1, w1 = 0.2, w2 = 0.1, w3 = 0.2, w4 = 0.3;  //weight for each ldr sensor values
int light = 3, brightness = 0;  //stage light is connected to pin 3, initial brightness is 0
int servo = 9, servoAngle = 0;  //servo motor is connected to pin 9, initial angle is 0. 

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  DmxSimple.usePin(light);
  DmxSimple.write(2, 255); //set red brightness to max
  DmxSimple.write(3, 255); //set blue brightness to max
  DmxSimple.write(4, 255); //set green brightness to max
  myservo.attach(servo);
}

void loop() {
  while (Serial.available() > 0) {
    int ldr0Val = Serial.parseInt();  //read ldr0Val from ldr0 via xbee
    int ldr1Val = Serial.parseInt();  //read ldr1Val from ldr0 via xbee
    int ldr2Val = Serial.parseInt();  //read ldr2Val from ldr0 via xbee
    int ldr3Val = Serial.parseInt();  //read ldr3Val from ldr0 via xbee
    int ldr4Val = Serial.parseInt();  //read ldr4Val from ldr0 via xbee
    
    brightness = (ldr0Val + ldr1Val + ldr2Val + ldr3Val + ldr4Val) / 5; 
    brightness = map(brightness, 0, 150, 0, 255); //scale the brightness
   
    servoAngle = ldr0Val * w0 + ldr1Val * w1 + ldr2Val * w2 + ldr3Val * w3 + ldr4Val * w4;
    servoAngle = map(servoAngle, 0, 90, 0, 30); //scale the servo angle
    
    Serial.print(ldr0Val); Serial.print(" ");
    Serial.print(ldr1Val); Serial.print(" ");
    Serial.print(ldr2Val); Serial.print(" ");
    Serial.print(ldr3Val); Serial.print(" ");
    Serial.print(ldr4Val); Serial.print(" ");
    Serial.print("brightness: "); Serial.print(" "); Serial.print(brightness);
    Serial.print("servoAngle: "); Serial.print(" "); Serial.println(servoAngle);
    
    DmxSimple.write(1, brightness); //write brightness to the led stage light
    myservo.write(servoAngle);  //write rotation angle to the servo motor
  }
}
