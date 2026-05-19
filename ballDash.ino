#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDRESS 0x27
LiquidCrystal_I2C lcd(I2C_ADDRESS, 20, 4);

byte player[] = {
  0b11111,
  0b11001,
  0b11111,
  0b11111,
  0b11111,
  0b10101,
  0b10101,
  0b10101
};

byte down_spike[] = {
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b11111,
  0b11111
};

byte up_spike[] = {
  0b11111,
  0b11111,
  0b01110,
  0b01110,
  0b00100,
  0b00100,
  0b00000,
  0b00000
};

void setup() {
  
}

void loop(){

}