#include <RotaryEncoder.h>
#include <L298N.h>
#include <Adafruit_NeoPixel.h>


char A_IN1 = 8, A_IN2 = 9, A_EN = 17, A_INT1 = 4, A_INT2 = 5;
char B_IN1 = 10, B_IN2 = 11, B_EN = 16, B_INT1 = 3, B_INT2 = 2;
int AnPin1 = A1;


//dagu wheel radius = 31mm circumfrance 0.19478, 125 encoder ticks per rev

RotaryEncoder encoder_left(A_INT1, A_INT2, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoder_right(B_INT1, B_INT2, RotaryEncoder::LatchMode::TWO03);

L298N left(A_IN1, A_IN2, A_EN);
L298N right(B_IN1, B_IN2, B_EN);

Adafruit_NeoPixel pixels(1, 28, NEO_GRB + NEO_KHZ800);


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

  pixels.begin();

}


void loop(){

  Serial.print("OutputLeft ");
  Serial.println(encoder_left.getPosition());
  Serial.print("OutputRight ");
  Serial.println(encoder_right.getPosition());

  battery_status();

}
