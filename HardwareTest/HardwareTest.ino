#include <RotaryEncoder.h>
#include <L298N.h>
#include <Adafruit_NeoPixel.h>


char A_IN1 = 8, A_IN2 = 9, A_EN = 17, A_INT1 = 4, A_INT2 = 5;
char B_IN1 = 10, B_IN2 = 11, B_EN = 16, B_INT1 = 3, B_INT2 = 2;
int AnPin1 = A2;

char gpio0 = 0, gpio1 = 1, gpio6 = 6, gpio7 = 7, gpio12 = 12, gpio13 = 13, gpio14 = 14;
char gpio15 = 15, gpio17 = 17, gpio19 = 19, gpio20 = 20, gpio21 = 21, gpio22 = 22;
char gpio23 = 23, gpio24 = 24, gpio25 = 25, gpio26 = 26, gpio27 = 27;


//dagu wheel radius = 31mm circumfrance 0.19478, 125 encoder ticks per rev

RotaryEncoder encoder_left(A_INT1, A_INT2, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoder_right(B_INT1, B_INT2, RotaryEncoder::LatchMode::TWO03);

L298N left(A_IN1, A_IN2, A_EN);
L298N right(B_IN1, B_IN2, B_EN);

Adafruit_NeoPixel pixels(1, 18, NEO_GRB + NEO_KHZ800);


void CheckPositionLeft(){
  encoder_left.tick();
}

void CheckPositionRight(){
  encoder_right.tick();
}

void battery_status(){
  int scaled;
  float ana1;
  ana1 = (float(analogRead(AnPin1))*(3.3/4096.0) * 175550) / 32450;
  Serial.println(ana1);
  scaled = (ana1 - 12) / (4.8 / 255); // 4.8v range
  if(scaled < 0){
    scaled = 0;
  }
  Serial.println(scaled);
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setPixelColor(0, pixels.Color((255-scaled), scaled, 0)); //RGB values
  pixels.show();   // Send the updated pixel colors to the hardware.
}



void setup(){

  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(A_INT1), CheckPositionLeft, CHANGE);
  pinMode(A_INT1, INPUT);
  attachInterrupt(digitalPinToInterrupt(A_INT2), CheckPositionLeft, CHANGE);
  pinMode(A_INT2, INPUT);
  attachInterrupt(digitalPinToInterrupt(B_INT1), CheckPositionRight, CHANGE);
  pinMode(B_INT1, INPUT);
  attachInterrupt(digitalPinToInterrupt(B_INT2), CheckPositionRight, CHANGE);
  pinMode(B_INT2, INPUT);

  pinMode(gpio0, INPUT);
  pinMode(gpio1, INPUT);
  pinMode(gpio6, INPUT);
  pinMode(gpio7, INPUT);
  pinMode(gpio12, INPUT);
  pinMode(gpio13, INPUT);
  pinMode(gpio14, INPUT);
  pinMode(gpio15, INPUT);
  pinMode(gpio17, INPUT);
  pinMode(gpio19, INPUT);
  pinMode(gpio20, INPUT);
  pinMode(gpio21, INPUT);
  pinMode(gpio22, INPUT);
  pinMode(gpio23, INPUT);
  pinMode(gpio24, INPUT);
  pinMode(gpio25, INPUT);
  pinMode(gpio26, INPUT);
  pinMode(gpio27, INPUT);

  pixels.begin();

}


void loop(){

  char val_0, val_1, val_6, val_7, val_12, val_13, val_14, val_15, val_17, val_19, val_20;
  char val_21, val_22, val_23, val_24, val_25, val_26, val_27;

  Serial.print("OutputLeft ");
  Serial.println(encoder_left.getPosition());
  Serial.print("OutputRight ");
  Serial.println(encoder_right.getPosition());

  val_0 = digitalRead(gpio0);
  val_1 = digitalRead(gpio1);
  val_6 = digitalRead(gpio6);
  val_7 = digitalRead(gpio7);
  val_12 = digitalRead(gpio12);
  val_13 = digitalRead(gpio13);
  val_14 = digitalRead(gpio14);
  val_15 = digitalRead(gpio15);
  val_17 = digitalRead(gpio17);
  val_19 = digitalRead(gpio19);
  val_20 = digitalRead(gpio20);
  val_21 = digitalRead(gpio21);
  val_22 = digitalRead(gpio22);
  val_23 = digitalRead(gpio23);
  val_24 = digitalRead(gpio24);
  val_25 = digitalRead(gpio25);
  val_26 = digitalRead(gpio26);
  val_27 = digitalRead(gpio27);
  
  Serial.print("gpio0 = ");
  Serial.println(val_0);
  Serial.print("gpio1 = ");
  Serial.println(val_1);
  Serial.print("gpio6 = ");
  Serial.println(val_6);
  Serial.print("gpio7 = ");
  Serial.println(val_7);
  Serial.print("gpio12 = ");
  Serial.println(val_12);
  Serial.print("gpio13 = ");
  Serial.println(val_13);
  Serial.print("gpio14 = ");
  Serial.println(val_14);
  Serial.print("gpio15 = ");
  Serial.println(val_15);
  Serial.print("gpio17 = ");
  Serial.println(val_17);
  Serial.print("gpio19 = ");
  Serial.println(val_19);
  Serial.print("gpio20 = ");
  Serial.println(val_20);
  Serial.print("gpio21 = ");
  Serial.println(val_21);
  Serial.print("gpio22 = ");
  Serial.println(val_22);
  Serial.print("gpio23 = ");
  Serial.println(val_23);
  Serial.print("gpio24 = ");
  Serial.println(val_24);
  Serial.print("gpio25 = ");
  Serial.println(val_25);
  Serial.print("gpio26 = ");
  Serial.println(val_26);
  Serial.print("gpio27 = ");
  Serial.println(val_27);

  battery_status();

  delay(1000);

}
