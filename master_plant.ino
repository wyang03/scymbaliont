//connect ldr sensors to analogue pins, and vibration motors to pwm pins (using arduino uno board) 
int ldr0 = A0, ldr0Val = 0; //ldr0 -> analogue pin A0
int ldr1 = A1, ldr1Val = 0; //ldr1 -> analogue pin A1
int ldr2 = A2, ldr2Val = 0; //ldr2 -> analogue pin A2
int ldr3 = A3, ldr3Val = 0; //ldr3 -> analogue pin A3
int ldr4 = A4, ldr4Val = 0; //ldr4 -> analogue pin A4

int vib0 = 3, vib0Val = 0; //vib motor 0 -> pin 3
int vib1 = 5, vib1Val = 0; //vib motor 1 -> pin 5
int vib2 = 6, vib2Val = 0; //vib motor 2 -> pin 6
int vib3 = 10, vib3Val = 0; //vib motor 3 -> pin 10
int vib4 = 11, vib4Val = 0; //vib motor 4 -> pin 11

int thresh0 = 10, thresh1 = 10, thresh2 = 10, thresh3 = 10, thresh4 = 10; //threshold for each ldr value


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vib0, OUTPUT);
  pinMode(vib1, OUTPUT);
  pinMode(vib2, OUTPUT);
  pinMode(vib3, OUTPUT);
  pinMode(vib4, OUTPUT);
}

void loop() {
  // Read ldr sensor values from analog pins
  ldr0Val = analogRead(ldr0);
  ldr1Val = analogRead(ldr1);
  ldr2Val = analogRead(ldr2);
  ldr3Val = analogRead(ldr3);
  ldr4Val = analogRead(ldr4);

  // Write scaled ldr snensor values to vibration motor
  if (ldr0Val > thresh0) {
    vib0Val = map(ldr0Val, thresh0, 500, 5, 150);
    analogWrite(vib0, vib0Val);
  } else {
    analogWrite(vib0, 0);
  }

  if (ldr1Val > thresh1) {
    vib1Val = map(ldr1Val, thresh1, 500, 5, 150);
    analogWrite(vib1, vib1Val);
  } else {
    analogWrite(vib1, 0);
  }
  if (ldr2Val > thresh2) {
    vib2Val = map(ldr2Val, thresh2, 500, 5, 150);
    analogWrite(vib2, vib2Val);
  } else {
    analogWrite(vib2, 0);
  }
  if (ldr3Val > thresh3) {
    vib3Val = map(ldr3Val, thresh3, 500, 5, 150);
    analogWrite(vib3, vib3Val);
  } else {
    analogWrite(vib3, 0);
  }

  if (ldr4Val > thresh4) {
    vib4Val = map(ldr4Val, thresh4, 500, 5, 150);
    analogWrite(vib4, vib4Val);
  } else {
    analogWrite(vib4, 0);
  }


  // Print the ldr sensor values, seperate by alphabetical marker
  Serial.print(ldr0Val); Serial.print('a');
  Serial.print(ldr1Val); Serial.print('b');
  Serial.print(ldr2Val); Serial.print('c');
  Serial.print(ldr3Val); Serial.print('d');
  Serial.print(ldr4Val); Serial.println('e');

  delay(10);
}
