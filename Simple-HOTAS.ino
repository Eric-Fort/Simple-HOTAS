/* 
* Simple-HOTAS by Eric Fort
* 
* Made from a Turnigy9X RC controller and an Adafruit 32u4.
* 
*/ 

#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 32, 0,
  true, true, false, false, false, false,
  true, true, false, false, false);

int rValue;
int pValue;
int yValue;
int tValue;
int var1Value;
int var2Value;
int rAngle;
int pAngle;
int yAngle;
int tAngle;
int var1Angle;
int var2Angle;

/*   32u4 gpio pinout Reference Diagram
 *  R   A0
 *  P   A1
 *  Y   A2
 *  T   A3  13  B1
 *  V1  A4  12  B2
 *  V2  A5  11  B3
 *  S4  15  10  B4
 *  S3  16  9   B5
 *  S2  14  6   B6
 *  S1  0   5   B7
 *  B10 1   3   B8
 *          2   B9
 */

int roll_in = A0;
int pitch_in = A1;
int yaw_in = A2;
int throttle_in = A3;
int var1_in = A4;
int var2_in = A5;

int b1 = 13;
int b2 = 12;
int b3 = 11;
int b4 = 10;
int b5 = 9;
int b6 = 6;
int b7 = 5;
int b8 = 3;
int b9 = 2;
int b10 = 1;
int s1 = 0;
int s2 = 14;
int s3 = 16;
int s4 = 15; 

int b1State = HIGH;
int b2State = HIGH;
int b3State = HIGH;
int b4State = HIGH;
int b5State = HIGH;
int b6State = HIGH;
int b7State = HIGH;
int b8State = HIGH;
int b9State = HIGH;
int b10State = HIGH;
int s1State = HIGH;
int s2State = HIGH;
int s3State = HIGH;
int s4State = HIGH;

int b1PrevState = HIGH;
int b2PrevState = HIGH;
int b3PrevState = HIGH;
int b4PrevState = HIGH;
int b5PrevState = HIGH;
int b6PrevState = HIGH;
int b7PrevState = HIGH;
int b8PrevState = HIGH;
int b9PrevState = HIGH;
int b10PrevState = HIGH;
int s1PrevState = HIGH;
int s2PrevState = HIGH;
int s3PrevState = HIGH;
int s4PrevState = HIGH;
/* ----------------- */
/* Stick Calibration */
/* ----------------- */
/*  For the basic TX the calibration process is manual. 
 *  Uncomment serial debug output section below.
 *  Monitor the serial output and move each stick to its lowest and highest endpoints 
 *  and then write down those numbers.
 *  Enter the lowest and highest numbers below. 
 *  Comment out the serial section when finished.
 */
#define rCalLow 52
#define rCalHigh 1017
#define pCalLow 1
#define pCalHigh 1005
#define yCalLow 226
#define yCalHigh 877
#define tCalLow 195
#define tCalHigh 805
#define var1CalLow 10
#define var1CalHigh 900
#define var2CalLow 10
#define var2CalHigh 900


void setup() {
  Serial.begin(115200);
  delay(5000);

  if (Serial){
    Serial.println("HOTAS");
  }
  
  // Set Range Values
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setRxAxisRange(0, 360);
  Joystick.setRyAxisRange(360, 0);
  Joystick.setRzAxisRange(0, 720);
  Joystick.setThrottleRange(0, 255);
  Joystick.setRudderRange(255, 0);

  Joystick.begin();

  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(b6, INPUT_PULLUP);
  pinMode(b7, INPUT_PULLUP);
  pinMode(b8, INPUT_PULLUP);
  pinMode(b9, INPUT_PULLUP);
  pinMode(b10, INPUT_PULLUP);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  pinMode(s3, INPUT_PULLUP);
  pinMode(s4, INPUT_PULLUP);
}

void loop() {
  rRead();
  pRead();
  yRead();
  tRead();
  bRead();
  //calibrationPrints();
}

void bRead(){
  b1State = digitalRead(b1);
  b2State = digitalRead(b2);
  b3State = digitalRead(b3);
  b4State = digitalRead(b4);
  b5State = digitalRead(b5);
  b6State = digitalRead(b6);
  b7State = digitalRead(b7);
  b8State = digitalRead(b8);
  b9State = digitalRead(b9);
  b10State = digitalRead(b10);
  s1State = digitalRead(s1);
  s2State = digitalRead(s2);
  s3State = digitalRead(s3);
  s4State = digitalRead(s4);

  if (b1State != b1PrevState){
    if (b1State == HIGH) {
      Joystick.releaseButton(0);
    }
    else {
      Joystick.pressButton(0);
    }
    b1PrevState = b1State;
  }


  if (b2State != b2PrevState){
    if (b2State == HIGH) {
      Joystick.releaseButton(1);
    }
    else {
      Joystick.pressButton(1);
    }
    b2PrevState = b2State;
  }
  

  if (b3State != b3PrevState){
    if (b3State == HIGH) {
      Joystick.releaseButton(2);
    }
    else {
      Joystick.pressButton(2);
    }
    b3PrevState = b3State;
  }

  if (b4State != b4PrevState){
    if (b4State == HIGH) {
      Joystick.releaseButton(3);
    }
    else {
      Joystick.pressButton(3);    
    }
    b4PrevState = b4State;
  }
  
  if (b5State != b5PrevState){
    if (b5State == HIGH) {
      Joystick.releaseButton(4);
    }
    else {
      Joystick.pressButton(4);    
    }
    b5PrevState = b5State;
  }
  
  if (b6State != b6PrevState){
    if (b6State == HIGH) {
      Joystick.releaseButton(5);
    }
    else {
      Joystick.pressButton(5);    
    }
    b6PrevState = b6State;
  }
  
  if (b7State != b7PrevState){
    if (b7State == HIGH) {
      Joystick.releaseButton(6);
    }
    else {
      Joystick.pressButton(6);    
    }
    b7PrevState = b7State;
  }
  
  if (b8State != b8PrevState){
    if (b8State == HIGH) {
      Joystick.releaseButton(7);
    }
    else {
      Joystick.pressButton(7);    
    }
    b8PrevState = b8State;
  }
  
  if (b9State != b9PrevState){
    if (b9State == HIGH) {
      Joystick.releaseButton(8);
    }
    else {
      Joystick.pressButton(8);    
    }
    b9PrevState = b9State;
  }
  
  if (b10State != b10PrevState){
    if (b10State == HIGH) {
      Joystick.releaseButton(9);
    }
    else {
      Joystick.pressButton(9);    
    }
    b10PrevState = b10State;
  }
  
  if (s1State != s1PrevState){
    if (s1State == HIGH) {
      Joystick.releaseButton(10);
    }
    else {
      Joystick.pressButton(10);    
    }
    s1PrevState = s1State;
  }
  
  if (s2State != s2PrevState){
    if (s2State == HIGH) {
      Joystick.releaseButton(11);
    }
    else {
      Joystick.pressButton(11);    
    }
    s2PrevState = s2State;
  }
  
  if (s3State != s3PrevState){
    if (s3State == HIGH) {
      Joystick.releaseButton(12);
    }
    else {
      Joystick.pressButton(12);    
    }
    s3PrevState = s3State;
  }
  
  if (s4State != s4PrevState){
    if (s4State == HIGH) {
      Joystick.releaseButton(13);
    }
    else {
      Joystick.pressButton(13);    
    }
    s4PrevState = s4State;
  }
}

void rRead(){
  rValue = analogRead(roll_in);

  if (rValue < rCalLow){
    rValue = rCalLow;
  }
  if (rValue > rCalHigh){
    rValue = rCalHigh;
  }
  rAngle = map(rValue, rCalHigh, rCalLow, -127, 127);
  Joystick.setXAxis(rAngle);
}

void pRead(){
  pValue = analogRead(pitch_in);
  if (pValue < pCalLow){
    pValue = pCalLow;
  }
  if (pValue > pCalHigh){
    pValue = pCalHigh;
  }
  pAngle = map(pValue, pCalHigh, pCalLow, -127, 127);
  Joystick.setYAxis(pAngle);
}
void yRead(){
  yValue = analogRead(yaw_in);
  if (yValue < yCalLow){
    yValue = yCalLow;
  }
  if (yValue > yCalHigh){
    yValue = yCalHigh;
  }
  yAngle = map(yValue, yCalLow, yCalHigh, 255, 0);
  Joystick.setRudder(yAngle);
}

void tRead(){
  tValue = analogRead(throttle_in);
  if (tValue < tCalLow) {
    tValue = tCalLow;
  }
  if (tValue > tCalHigh) {
    tValue = tCalHigh;
  }
  tAngle = map(tValue, tCalLow, tCalHigh, 0, 255);
  Joystick.setThrottle(tAngle);
}

void calibrationPrints(){
  if (Serial) {
    Serial.print("Roll Data: ");Serial.print(rAngle);Serial.print(" ");Serial.println(rValue);
    Serial.print("Pitch: ");Serial.print(pAngle);Serial.print(" ");Serial.println(pValue);
    Serial.print("Yaw: ");Serial.print(yAngle);Serial.print(" ");Serial.println(yValue);
    Serial.print("Throttle: ");Serial.print(tAngle);Serial.print(" "); Serial.println(tValue);
    delay(1000);
  }
}

