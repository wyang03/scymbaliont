#include <DmxSimple.h>

//-----------analogue pins--ldr0-4---------------
int ldr0 = A0, ldr0Val = 0;
int ldr1 = A1, ldr1Val = 0;
int ldr2 = A2, ldr2Val = 0;
int ldr3 = A3, ldr3Val = 0;
int ldr4 = A4, ldr4Val = 0;

//-----------multiplexer pins--ldr5-19---------
int s0 = 7, s1 = 8, s2 = 12, s3 = 13, SIG_pin = A5;  //connection for multiplexer on uno board
int ldr5 = 1, ldr5Val = 0, ldr6 = 2, ldr6Val = 0, ldr7 = 3, ldr7Val = 0, ldr8 = 4, ldr8Val = 0, ldr9 = 5, ldr9Val = 0;
int ldr10 = 6, ldr10Val = 0, ldr11 = 7, ldr11Val = 0, ldr12 = 8, ldr12Val = 0, ldr13 = 9, ldr13Val = 0, ldr14 = 10, ldr14Val = 0;
int ldr15 = 11, ldr15Val = 0, ldr16 = 12, ldr16Val = 0, ldr17 = 13, ldr17Val = 0, ldr18 = 14, ldr18Val = 0, ldr19 = 15, ldr19Val = 0;

//------------ lights ----------------
int light = 3, brightness0 = 0, brightness1 = 0, brightness2 = 0, brightness3 = 0, brightness4 = 0;
//int thresh0 = 300, thresh1 = 450, thresh2 = 400, thresh3 = 400;
int thresh0 = 200, thresh1 = 150, thresh2 = 150, thresh3 = 150, thresh4 = 70; //try use ldr12, ldr1, ldr17, ldr6
//float w0 = 1.0, w1 = 0.2, w2 = 0.1, w3 = 0.2, w4 = 0.3;  //weight for each ldr sensor values

//--------------vibration motors--pwm pins----------------
int vib0 = 5, vib0Val = 0; //vib motor 0 -> pin 5
int vib1 = 6, vib1Val = 0; //vib motor 1 -> pin 6
int vib2 = 9, vib2Val = 0; //vib motor 2 -> pin 9
int vib3 = 10, vib3Val = 0; //vib motor 3 -> pin 10
int vib4 = 11, vib4Val = 0; //vib motor 4 -> pin 11

//-----------------------------------
void setup() {
  //set up the multiplexer
  pinMode(s0, OUTPUT); pinMode(s1, OUTPUT); pinMode(s2, OUTPUT); pinMode(s3, OUTPUT);
  digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW);

  //set up the lights
  pinMode(light, OUTPUT);
  DmxSimple.usePin(light);
  DmxSimple.write(2, 255); DmxSimple.write(3, 255); DmxSimple.write(4, 255),  DmxSimple.write(5, 0); DmxSimple.write(6, 0); // light 1 (6 channels), r, b, g max values
  DmxSimple.write(8, 255); DmxSimple.write(9, 255); DmxSimple.write(10, 255),  DmxSimple.write(11, 0); DmxSimple.write(12, 0);// light 2 (6 channels), r, b, g max values
  DmxSimple.write(14, 255); DmxSimple.write(15, 255); DmxSimple.write(16, 255),  DmxSimple.write(17, 0); DmxSimple.write(18, 0);// light 3 (6 channels), r, b, g max values
  DmxSimple.write(20, 255); DmxSimple.write(21, 255); DmxSimple.write(22, 255),  DmxSimple.write(23, 0); DmxSimple.write(24, 0);// light 4 (6 channels), r, b, g max values

  //set up vibration motors
 pinMode(vib0, OUTPUT);
  pinMode(vib1, OUTPUT);
  pinMode(vib2, OUTPUT);
  pinMode(vib3, OUTPUT);
  pinMode(vib4, OUTPUT);

  //begin serial communication
  Serial.begin(9600);
}

void loop() {
  //set random number to be added to brightnesses
  float w0 = 1.0, w1 = 0.2, w2 = 0.1, w3 = 0.2, w4 = 0.3;  //weight for each ldr sensor values

  // Read ldr sensor values from analog pins
  ldr0Val = analogRead(ldr0); ldr1Val = analogRead(ldr1); ldr2Val = analogRead(ldr2); ldr3Val = analogRead(ldr3); ldr4Val = analogRead(ldr4);

  // Read ldr sensor values from multiplexer pins
  ldr5Val = readMux(ldr5); ldr6Val = readMux(ldr6); ldr7Val = readMux(ldr7); ldr8Val = readMux(ldr8); ldr9Val = readMux(ldr9);
  ldr10Val = readMux(ldr10); ldr11Val = readMux(ldr11); ldr12Val = readMux(ldr12); ldr13Val = readMux(ldr13); ldr14Val = readMux(ldr14);
  ldr15Val = readMux(ldr15); ldr16Val = readMux(ldr16); ldr17Val = readMux(ldr17); ldr18Val = readMux(ldr18); ldr19Val = readMux(ldr19);

  // Mapping sensor values with vibration motor intensity and light brightness  
  if (ldr0Val < thresh0) {
    brightness0 = (ldr0Val + ldr1Val + ldr2Val + ldr3Val + ldr4Val) / 5.0;
    brightness0 = map(brightness0, 0, 80, 0, 255); //scale the brightness;
  }
   vib0Val = map(ldr0Val, 0, thresh0, 150, 20);
  } else {
   vib0Val = 0;
  }

  if (ldr1Val < thresh1) {
    brightness1 = (ldr5Val + ldr6Val + ldr7Val + ldr8Val + ldr9Val) / 5.0;
    brightness1 = map(brightness1, 0, 150, 0, 255); //scale the brightness;
    vib1Val = map(ldr1Val, 0, thresh1,150, 20);
  } else {
    vib1Val = 0;
  }


  if (ldr2Val < thresh2) {
    brightness2 = (ldr10Val + ldr11Val + ldr12Val + ldr13Val + ldr14Val) / 5.0;
    brightness2 = map(brightness2, 0, 200, 0, 255); //scale the brightness;
    w2 = brightness2 / 100;
    vib2Val = map(ldr2Val, 0, thresh2, 150, 20);
  } else {
    vib2Val = 0;
  }


  if (ldr3Val < thresh3) {
    brightness3 = (ldr15Val + ldr16Val + ldr17Val + ldr18Val + ldr19Val) / 5.0;
    brightness3 = map(brightness3, 30, 200, 0, 255); //scale the brightness;
    //    w3 = brightness1 / 100;
    vib3Val = map(ldr3Val, 0, thresh3, 150, 20);
  } else {
    vib3Val = 0;
  }

  if (ldr4Val < thresh4) {
    vib4Val = map(ldr4Val, 0, thresh4, 150, 20);
    analogWrite(vib4, vib4Val);
  } else {
    analogWrite(vib4, 0);
  }

  // Print the ldr sensor values, seperate by alphabetical marker
  Serial.print(ldr0Val); Serial.print('a');
  Serial.print(ldr1Val); Serial.print('b');
  Serial.print(ldr2Val); Serial.print('c');
  Serial.print(ldr3Val); Serial.print('d');
  Serial.print(ldr4Val); Serial.print('e');
  Serial.print(ldr5Val); Serial.print('f');
  Serial.print(ldr6Val); Serial.print('g');
  Serial.print(ldr7Val); Serial.print('h');
  Serial.print(ldr8Val); Serial.print('i');
  Serial.print(ldr9Val); Serial.print('j');
  Serial.print(ldr10Val); Serial.print('k');
  Serial.print(ldr11Val); Serial.print('l');
  Serial.print(ldr12Val); Serial.print('m');
  Serial.print(ldr13Val); Serial.print('n');
  Serial.print(ldr14Val); Serial.print('o');
  Serial.print(ldr15Val); Serial.print('p');
  Serial.print(ldr16Val); Serial.print('q');
  Serial.print(ldr17Val); Serial.print('r');
  Serial.print(ldr18Val); Serial.print('s');
  Serial.print(ldr19Val); Serial.println('t');


  //write brightness to the lights
  DmxSimple.write(1, brightness0); //write brightness to light 1
  DmxSimple.write(7, brightness1); //write brightness to light 2
  DmxSimple.write(13, brightness2); //write brightness to light 3
  DmxSimple.write(19, brightness3); //write brightness to light 4

  //write vibVals to the vibs 
  analogWrite(vib0, vib0Val); 
  analogWrite(vib1, vib1Val);  analogWrite(vib2, vib2Val);
  analogWrite(vib3, vib3Val); analogWrite(vib4, vib4Val);

  delayMicroseconds(10);
}

// Function to read values from multiplexer
int readMux(int channel) {
  int controlPin[] = {s0, s1, s2, s3};
  int muxChannel[16][4] = {
    {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, //channel 0 - 3
    {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {1, 1, 1, 0}, //channel 4 - 7
    {0, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, //channel 8 - 11
    {0, 0, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1} //channel 12 - 15
  };

  //loop through the 4 sig
  for (int i = 0; i < 4; i++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  int val = analogRead(SIG_pin);
  return val;
}
