/*const int irPin1 = 2; // IR sensor 1 pin
volatile bool irState1 = false;

const int irPin2 = 3; // IR sensor 2 pin
const int irPin2_noint = 25;
volatile bool irState2 = false;

void setup() {
  pinMode(irPin1, INPUT);
  attachInterrupt(digitalPinToInterrupt(irPin1), ir1Isr, CHANGE);

  pinMode(irPin2, INPUT);
  pinMode(irPin2_noint, INPUT);
  attachInterrupt(digitalPinToInterrupt(irPin2), ir2Isr, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // do other stuff
}

void ir1Isr() {
  irState1 = !irState1;
  if (irState1) {
    Serial.print("IR1 edge detected!");
  } else {
    Serial.print("IR1 object detected!");
  }
}

void ir2Isr() {
  irState2 = !irState2;
  if (irState2) {
    Serial.print("IR2 edge detected!");
  } else {
    Serial.print("No edge detected");
  }
}
*/

int pin = 23;

void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(pin) == LOW){
    Serial.println("edge detected");
  }
  else{
    Serial.println("edge not detected");
  }

  delay(5000);
}
