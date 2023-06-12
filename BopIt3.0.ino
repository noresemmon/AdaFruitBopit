#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <time.h>  

const byte interruptSwitch = 7; 
const byte interruptLeftButton = 4;
const byte interruptRightButton = 5;


const uint8_t spIT[]            PROGMEM ={0x2B,0x19,0xC1,0x99,0x3D,0xDE,0xEC,0xE2,0x14,0x2D,0xBA,0x88,0xE5,0xDB,0x55,0xD5,0x9C,0xC6,0xE2,0x4F,0x57,0x9D,0xB2,0x99,0x44,0x5F,0x49,0xAD,0x2D,0x1C,0xB1,0x6D,0xDA,0x0C,0xD1,0x98,0x7A,0xA9,0x66,0x00,0x50,0xC0,0x32,0x1E,0x1E,0x10,0x40,0x72,0x49,0x0F,0x00,0x00};
const uint8_t spPRESS[]         PROGMEM = {0x02,0x28,0x31,0x43,0x03,0x25,0xCB,0xBE,0xDC,0x5D,0xED,0x94,0x22,0x0E,0xCE,0x70,0xC9,0xBD,0xF2,0x9C,0xD5,0xBD,0x24,0xEF,0xC9,0xAB,0x77,0xF5,0x92,0x3E,0x27,0x6B,0xA1,0x25,0xD5,0x56,0xDF,0xEC,0x34,0x5D,0xA7,0x94,0xF9,0xEB,0x3B,0xEC,0x69,0xEE,0x75,0x15,0xC0,0x57,0xC1,0x02,0xF8,0x3D,0x5D,0x02,0x1A,0xD0,0x80,0x04,0x28,0x80,0x81,0xFF,0x07};
const uint8_t spSWITCH[]        PROGMEM = {0x08,0xF8,0x3B,0x93,0x03,0x1A,0xB0,0x80,0x01,0xAE,0xCF,0x54,0x40,0x33,0x99,0x2E,0xF6,0xB2,0x4B,0x9D,0x52,0xA7,0x36,0xF0,0x2E,0x2F,0x70,0xDB,0xCB,0x93,0x75,0xEE,0xA6,0x4B,0x79,0x4F,0x36,0x4C,0x89,0x34,0x77,0xB9,0xF9,0xAA,0x5B,0x08,0x76,0xF5,0xCD,0x73,0xE4,0x13,0x99,0x45,0x28,0x77,0x11,0xD9,0x40,0x80,0x55,0xCB,0x25,0xE0,0x80,0x59,0x2F,0x23,0xE0,0x01,0x0B,0x08,0xA0,0x46,0xB1,0xFF,0x07};
const uint8_t spMOVE[]          PROGMEM = {0x6A,0xD7,0xC2,0xF2,0xD2,0xEC,0xB8,0x39,0x08,0xF6,0x4D,0x4D,0x1A,0xC6,0x24,0x31,0xB2,0xCC,0x69,0x1E,0x56,0x9D,0x85,0x7B,0x15,0xA4,0x3B,0x55,0x23,0x9E,0x3E,0xE0,0x6D,0xE7,0x23,0xAF,0x20,0xC6,0x0A,0xBC,0xCE,0xA2,0x34,0x91,0x6C,0x89,0x43,0xDF,0x3A,0x94,0x31,0x83,0x6E,0x4D,0xE8,0x9A,0x96,0x0C,0x3A,0x63,0x20,0x5B,0xD8,0xAC,0xEC,0xC8,0x20,0x37,0x7E,0xB7,0xA7,0x3D,0xCD,0xD9,0x8A,0x78,0x28,0x2E,0xB5,0x97,0xBD,0xED,0xCD,0x80,0x52,0x32,0x28,0x80,0x81,0xFF,0x07};
const uint8_t spOVER[]          PROGMEM = {0x63,0x6F,0xC4,0x7A,0x1D,0xB5,0xED,0x61,0x37,0xBB,0x6E,0x75,0x62,0xD9,0x2D,0xEC,0xBF,0x56,0xAD,0x09,0xBA,0x32,0x8C,0x13,0xC7,0xD6,0xED,0x4D,0x85,0x86,0x99,0xE3,0x3E,0xB7,0x29,0x86,0x90,0x2C,0x76,0xDB,0xE6,0x98,0x95,0xBB,0x38,0x4F,0x5B,0x72,0x29,0xB4,0x51,0x6F,0x7D,0xAF,0x47,0xB9,0x73,0x71,0x8C,0x31,0x3F,0xE1,0xC9,0xA9,0x50,0xD6,0xFD,0xBA,0x27,0x57,0xC5,0x6E,0xCD,0xFD,0xFF};
const uint8_t spGAMES[]         PROGMEM = {0xAA,0x15,0x24,0x2A,0xD6,0xE4,0xB6,0xB6,0x79,0x13,0xB1,0x5C,0xB2,0xF3,0x93,0x97,0xA4,0x66,0x3E,0x75,0x77,0x3E,0xF2,0x52,0x8D,0xCD,0x26,0xF6,0xCC,0x7B,0xDE,0x8A,0x9A,0x14,0x2D,0xBA,0xD2,0xAC,0x66,0xDD,0xEB,0xDE,0x8E,0xB6,0x7A,0x47,0x0D,0xAF,0x95,0x3A,0x6D,0xB1,0x9A,0xDA,0x8E,0xED,0x6C,0x67,0x3A,0x6E,0xA5,0x46,0x42,0xB1,0xED,0x74,0x27,0x3A,0x62,0x32,0xC2,0x23,0x76,0xEA,0x7F,0x22,0x36,0x11,0xF5,0x06,0x38,0x1C,0xC8,0x00,0xDF,0x29,0x39,0xE0,0x7B,0x56,0x03,0x7C,0xCD,0xCA,0x80,0xCC,0x83,0x1E,0x00,0x00};
const uint8_t spPOINT[]         PROGMEM = {0x0A,0xC8,0x2E,0x8C,0x01,0xD1,0x85,0x95,0x34,0x8B,0xAA,0x74,0x56,0xBD,0xCA,0xE8,0xA6,0xCA,0x29,0xCB,0x2A,0x92,0xEE,0xCA,0xA4,0x36,0x2B,0x2F,0xAA,0x3C,0x43,0x9A,0xAC,0xBC,0x78,0xF3,0xD0,0x68,0xD4,0xB2,0x6A,0x45,0x4A,0x2A,0xA6,0xC9,0x93,0xC4,0x29,0x09,0xC7,0x24,0x8D,0xB1,0xD3,0xCD,0x08,0x21,0x70,0x8A,0x52,0x15,0xAA,0x01,0xE0,0x80,0x63,0xC2,0x14,0x70,0x94,0x19,0x01,0xA6,0x32,0xFB,0x7F};
const uint8_t spONE[]           PROGMEM = {0x66,0x4E,0xA8,0x7A,0x8D,0xED,0xC4,0xB5,0xCD,0x89,0xD4,0xBC,0xA2,0xDB,0xD1,0x27,0xBE,0x33,0x4C,0xD9,0x4F,0x9B,0x4D,0x57,0x8A,0x76,0xBE,0xF5,0xA9,0xAA,0x2E,0x4F,0xD5,0xCD,0xB7,0xD9,0x43,0x5B,0x87,0x13,0x4C,0x0D,0xA7,0x75,0xAB,0x7B,0x3E,0xE3,0x19,0x6F,0x7F,0xA7,0xA7,0xF9,0xD0,0x30,0x5B,0x1D,0x9E,0x9A,0x34,0x44,0xBC,0xB6,0x7D,0xFE,0x1F};
const uint8_t spSAY[]           PROGMEM = {0x08,0x78,0xDE,0x5C,0x03,0x16,0xB0,0x80,0x05,0x2C,0x60,0x01,0x0D,0xAC,0x38,0xE5,0x70,0xD1,0x9A,0x7B,0x93,0x9B,0x9C,0x34,0xD5,0x30,0xD1,0x9A,0x7B,0xB3,0x93,0xD7,0x1C,0xA4,0x1A,0x6F,0x6E,0xBD,0xBA,0x52,0x59,0xD5,0xB7,0x76,0x1F,0xEA,0x90,0x07,0x37,0xE4,0x82,0x9A,0xF1,0x51,0xDC,0x98,0xAD,0x62,0x74,0x07,0x7A};
const uint8_t spLEVEL[]         PROGMEM = {0xA5,0x1E,0x40,0x27,0x84,0xF3,0x94,0xB6,0x03,0x5F,0x65,0x8F,0x9B,0xBA,0x09,0x64,0x1D,0xA3,0xCE,0x6A,0x2B,0xEB,0x34,0xB5,0xC7,0xAB,0xAE,0x62,0x4C,0x23,0x67,0xAF,0xBA,0xE8,0x11,0xF7,0x5C,0xBC,0xEA,0x62,0x4B,0x43,0x63,0xF1,0xAA,0x53,0xF0,0x0A,0xCD,0xD9,0x66,0xCC,0x22,0x2C,0x95,0xDD,0xB8,0xB1,0x09,0x17,0x0B,0xB3,0x1D,0xF6,0x22,0x23,0xD3,0x39,0x96,0x99,0x6D,0xEB,0x10,0x89,0xC5,0x65,0x09,0xFA,0xDA,0x44,0x7A,0xB7,0x2D,0xF1,0x1D,0x17,0xCD,0x52,0xF6,0xC4,0xAE,0x9D,0xA5,0x6F,0x3A,0x12,0xBD,0x76,0x96,0x2C,0xE9,0x8C,0xFC,0xCB,0x59,0xBB,0xB8,0x3B,0xCA,0xED,0x62,0xEE,0xA4,0x1E,0xEF,0x3E,0x9D,0xBC,0xF5,0xFF,0x03};
const uint8_t spTWO[]           PROGMEM = {0x06,0xB8,0x59,0x34,0x00,0x27,0xD6,0x38,0x60,0x58,0xD3,0x91,0x55,0x2D,0xAA,0x65,0x9D,0x4F,0xD1,0xB8,0x39,0x17,0x67,0xBF,0xC5,0xAE,0x5A,0x1D,0xB5,0x7A,0x06,0xF6,0xA9,0x7D,0x9D,0xD2,0x6C,0x55,0xA5,0x26,0x75,0xC9,0x9B,0xDF,0xFC,0x6E,0x0E,0x63,0x3A,0x34,0x70,0xAF,0x3E,0xFF,0x1F};
const uint8_t spTHREE[]         PROGMEM = {0x0C,0xE8,0x2E,0x94,0x01,0x4D,0xBA,0x4A,0x40,0x03,0x16,0x68,0x69,0x36,0x1C,0xE9,0xBA,0xB8,0xE5,0x39,0x70,0x72,0x84,0xDB,0x51,0xA4,0xA8,0x4E,0xA3,0xC9,0x77,0xB1,0xCA,0xD6,0x52,0xA8,0x71,0xED,0x2A,0x7B,0x4B,0xA6,0xE0,0x37,0xB7,0x5A,0xDD,0x48,0x8E,0x94,0xF1,0x64,0xCE,0x6D,0x19,0x55,0x91,0xBC,0x6E,0xD7,0xAD,0x1E,0xF5,0xAA,0x77,0x7A,0xC6,0x70,0x22,0xCD,0xC7,0xF9,0x89,0xCF,0xFF,0x03};
const uint8_t spFOUR[]          PROGMEM = {0xC0,0x00,0x23,0x2D,0x24,0xA0,0x01,0x0B,0x58,0x20,0xC5,0xBC,0xF7,0x11,0x4C,0x9A,0x9A,0xA4,0x84,0xF6,0x39,0x85,0x6E,0x97,0x93,0x98,0x84,0x8C,0xF5,0x5E,0x45,0xCD,0xDE,0x2A,0x91,0x63,0xD2,0x58,0x7D,0x6B,0x55,0xB1,0xF2,0x26,0xED,0xA9,0xE7,0xDB,0xC2,0x4B,0xFC,0xBA,0x49,0x2E,0x89,0x55,0xF4,0xE3,0x66,0xB5,0x95,0xAB,0xCC,0xBB,0x9B,0xED,0x30,0xF6,0x11,0x35,0x76,0x7B,0x00,0x00};
const uint8_t spFIVE[]          PROGMEM = {0x08,0x68,0x4E,0x9D,0x02,0x1C,0x60,0xC0,0x8C,0x69,0x12,0xB0,0xC0,0x28,0xAB,0x8C,0x9C,0xC0,0x2D,0xBB,0x38,0x79,0x31,0x15,0xA3,0xB6,0xE4,0x16,0xB7,0xDC,0xF5,0x6E,0x57,0xDF,0x54,0x5B,0x85,0xBE,0xD9,0xE3,0x5C,0xC6,0xD6,0x6D,0xB1,0xA5,0xBF,0x99,0x5B,0x3B,0x5A,0x30,0x09,0xAF,0x2F,0xED,0xEC,0x31,0xC4,0x5C,0xBE,0xD6,0x33,0xDD,0xAD,0x88,0x87,0xE2,0xD2,0xF2,0xF4,0xE0,0x16,0x2A,0xB2,0xE3,0x63,0x1F,0xF9,0xF0,0xE7,0xFF,0x01};
const uint8_t spSIX[]           PROGMEM = {0x04,0xF8,0xB9,0x55,0x01,0xBF,0xA5,0x1B,0xE0,0x37,0x0F,0x03,0xFC,0x96,0x61,0x80,0xDF,0x3C,0x0C,0xF0,0x93,0xDA,0x4A,0x87,0x49,0x53,0x91,0x37,0x2B,0x6D,0xD2,0x55,0x23,0xDE,0xAC,0xAA,0xB9,0x16,0x09,0xFF,0xB2,0xFA,0x66,0x93,0x3C,0x63,0xF3,0x9C,0x10,0x38,0x45,0xA9,0x0A,0xD5,0x00,0x00,0x02,0x14,0x97,0xAA,0x80,0xAB,0x6B,0x0D,0xF0,0x63,0xA5,0x01,0x7E,0xCB,0x30,0xC0,0x6F,0xE9,0x0A,0xF8,0x25,0x93,0x01,0x3F,0x57,0xFC,0x3F};
const uint8_t spLESS[]          PROGMEM = {0xA6,0x16,0xBA,0xDB,0x43,0x52,0x85,0xD6,0x88,0x2A,0x76,0x6D,0x53,0x5A,0xA7,0xD4,0xC3,0xA8,0x6B,0x6B,0x9C,0x31,0x2F,0x92,0xAE,0xA7,0x8E,0xC9,0x5B,0xAC,0xB6,0xDD,0xFA,0xD6,0xA7,0x4A,0x59,0x47,0xB8,0x52,0xDE,0xEA,0x14,0xB1,0x66,0xA3,0x66,0x92,0x52,0xB8,0x1C,0xCE,0x31,0xA1,0x15,0xF0,0x63,0xB8,0x07,0x0C,0xF0,0x83,0x87,0x07,0x02,0xF0,0x83,0x47,0x00,0x9E,0xC9,0x32,0xC0,0x51,0x96,0x04,0x70,0xB1,0x98,0x00,0x31,0x63,0xC2,0x03,0x00,0x00};
const uint8_t spEND[]           PROGMEM = {0xA3,0xC8,0x4D,0x4D,0x3C,0x63,0x9F,0xA2,0xB4,0x34,0x51,0x5F,0x7B,0xF3,0x93,0xE5,0x96,0xA6,0x9A,0x73,0x4F,0x56,0x4A,0xA9,0x54,0xCD,0x3D,0x59,0xC9,0xA5,0x5A,0x33,0xE7,0xE4,0x25,0x96,0x8A,0xD9,0xEC,0x53,0xE5,0x54,0xAC,0x66,0x53,0x4E,0x9D,0x4A,0x9A,0xA8,0xCE,0x59,0x4D,0xCC,0x65,0x64,0x36,0x6B,0x74,0xC9,0x57,0xA1,0xCB,0xEC,0xD0,0xEB,0xA0,0xA6,0xE6,0xB5,0x5D,0xAF,0x02,0x97,0xD8,0x38,0x70,0xBD,0x0C,0x5C,0xE2,0x1D,0xCB,0xF4,0xD2,0x51,0x9B,0x4E,0x2C,0x35,0x68,0x8B,0x6B,0x36,0x91,0xE4,0xC8,0xA7,0x30,0x15,0xE5,0x22,0x1E,0x1B,0xF4,0x28,0x86,0x14,0x53,0x5D,0xB3,0xD6,0x03};

volatile bool resetFlag = false;

volatile bool gameOver = false;
volatile bool state = false; 
volatile bool switchFlag = false;
volatile bool leftFlag = false;
volatile bool rightFlag = false;
volatile bool gameStart = false;


float X, Y, Z, totalAccel;
int highscore;
int d; 
volatile int points = 0;
int modeControl = 0;
float s = 0;
int levelFlag = 1;



void setup() {
  CircuitPlayground.begin();

  srand(analogRead(A0));
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  attachInterrupt(digitalPinToInterrupt(interruptSwitch), Switch, CHANGE);
   attachInterrupt(digitalPinToInterrupt(interruptLeftButton), leftButton, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptRightButton), rightButton, RISING);
  CircuitPlayground.speaker.set(255);
Serial.begin(9600);
while(!Serial);
}

void loop() {
  delay(100);
  if (gameStart == false){
    Serial.println("Press both buttons to start");
    for (int i = 0; i < 10; i++){
        CircuitPlayground.setPixelColor(i,255,0,0);
        delay(100); }
        for(int i = 11; i >= 0; i--){
          CircuitPlayground.setPixelColor(i,0,255,0);
          delay(100);
  }
}
  if (rightFlag && leftFlag){
    leftFlag = false;
    rightFlag = false;
    gameStart = true;
  }


  if (gameStart == true){
  if (gameOver == false && points < 4){
    resetFlag = false;
    if (levelFlag == 1){
    Serial.println("level 1");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spONE);  
    levelFlag++;
}
  d = 350;
  level(); 
  } 
  if (gameOver == false && points >= 4 && points < 8){
     if (levelFlag == 2){
    Serial.println("level 2");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spTWO);
    levelFlag++;
}
   d = 300;
  level(); 
}
if (gameOver == false && points >= 8 && points < 13){
     if (levelFlag == 3){
       Serial.println("level 3");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spTHREE);  
    levelFlag++;
}
d = 250;
level();
}
if (gameOver == false && points >= 13 && points < 19){
     if (levelFlag == 4){
       Serial.println("level 4");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spFOUR);  
    levelFlag++;
}
d = 200;
level();
}
if (gameOver == false && points >= 19 && points < 26){
     if (levelFlag == 5){
       Serial.println("level 5");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spFIVE);  
    levelFlag++;
}
d = 150;
level();
}
if (gameOver == false && points >= 26 && points < 34){
     if (levelFlag == 6){
       Serial.println("level 6");
    CircuitPlayground.speaker.say(spLEVEL);  
    delay(100);
    CircuitPlayground.speaker.say(spSIX);
    levelFlag++;
}
d = 100;
level();
}
if (gameOver == false && points >= 34){
     if (levelFlag == 7){
    Serial.println("Endless level");
    CircuitPlayground.speaker.say(spEND);  
    delay(50);
    CircuitPlayground.speaker.say(spLESS);  
    delay(100);
    CircuitPlayground.speaker.say(spLEVEL);  
   levelFlag++;
}
d--;
level();
}


 if (gameOver){
      CircuitPlayground.clearPixels();
      for (int i = 0; i < 10; i++){
        CircuitPlayground.setPixelColor(i,255,165,0);
        delay(100); }
        CircuitPlayground.clearPixels();
        delay(10);
        for(int i = 11; i >= 0; i--){
          CircuitPlayground.setPixelColor(i,255,165,0);
          delay(100);
        }
      

      
      if (rightFlag && leftFlag){
      gameOver = false;
      points = 0;
      levelFlag = 1;
      switchFlag = false;
      leftFlag   = false;
      rightFlag  = false;
      }
      if (resetFlag == false){
    Serial.println("GAME OVER");
    delay(1000);
    Serial.print("Total points  ");
    Serial.println(points);
    if (highscore < points){
      Serial.println("NEW HIGHSCORE!!");
      highscore = points;
    }
    Serial.print("Your highscore is ");
    Serial.println(highscore);
    delay(2000);
    Serial.println("Want to play again?");
    Serial.println("Press both buttons!");
    resetFlag = true;
      }
    }
  }
}





void level(){
    if (gameOver == false){
    modeControl = rand() % 4;}
    
  switch(modeControl){
case 0:
delay(100);
  CircuitPlayground.clearPixels();
	CircuitPlayground.speaker.say(spSWITCH);  
    Serial.println("Switch");      
  for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,255,0,0);
      delay(d);
  }
  for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,255,0);
  }


if (switchFlag == true){
  switchFlag = false;
  leftFlag = false;
  rightFlag = false;
  points++;
} 

else {
  CircuitPlayground.speaker.say(spGAMES);
  delay(100);
  CircuitPlayground.speaker.say(spOVER);
  gameOver = true;
}
break; 

case 1:
delay(100);
  CircuitPlayground.clearPixels();
	CircuitPlayground.speaker.say(spPRESS);
  Serial.println("Press");
    for (int i = 10; i > 0; i--){
    CircuitPlayground.setPixelColor(i,255,0,0);
      delay(d);
  }
  for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,255,0);
  }


if (rightFlag && leftFlag){
  switchFlag = false;
  leftFlag = false;
  rightFlag = false;
  points++;
} else {
    CircuitPlayground.speaker.say(spGAMES);
    delay(100);
  CircuitPlayground.speaker.say(spOVER);
  gameOver = true;
}
break;
default:

case 2:
  delay(100);
  CircuitPlayground.clearPixels();
	CircuitPlayground.speaker.say(spMOVE);
  Serial.println("Move");
    for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,255,0,0);
      delay(d);
  }
  for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,255,0);
  }


  X = 0;
  Y = 0;
  Z = 0;
  for (int i=0; i<10; i++) {
    X += CircuitPlayground.motionX();
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;
  totalAccel = sqrt(X*X + Y*Y + Z*Z);

if (totalAccel > 20){
  switchFlag = false;
  leftFlag = false;
  rightFlag = false;
  points++;
} else {
     CircuitPlayground.speaker.say(spGAMES);
     delay(100);
      CircuitPlayground.speaker.say(spOVER);
        gameOver = true;
  }
 break;

case 3:
  delay(100);
  CircuitPlayground.clearPixels();
  CircuitPlayground.speaker.say(spSAY);
  Serial.println("Say");


    for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,255,0,0);
      delay(d);
  }
  for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,255,0);}
     s = CircuitPlayground.mic.soundPressureLevel(90);
    if (s > 70){
    switchFlag = false;
    leftFlag = false;
    rightFlag = false;
    points++;
  } else {
    CircuitPlayground.speaker.say(spGAMES);
     delay(100);
      CircuitPlayground.speaker.say(spOVER);
        gameOver = true;
  }
  break;
  break;
  }
} 
  
  












void Switch(){
  switchFlag = true;
}
void leftButton(){
  leftFlag = true;
}
void rightButton(){
  rightFlag = true;
}
