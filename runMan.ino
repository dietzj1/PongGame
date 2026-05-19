#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
#define I2C_ADDRESS 0x27
LiquidCrystal_I2C lcd(I2C_ADDRESS, 20, 4);


byte player[] = {
  B11111,
  B10101,
  B11111,
  B00100,
  B11111,
  B10101,
  B00100,
  B01010
};

byte spike[] = {
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011
};
int playery = 1;
//int spike_y = 1;
int spikes_x = 0;
int score = -1;
int spikesb = 0;
int spikes[4] = {0, 0, 0, 0};
float fps = 4;
bool noclip = false;


void setup() {
  lcd.init();      // Initialize the lcd
  lcd.backlight(); // Turn on the backlight
  lcd.createChar(0, player);
  lcd.createChar(1, spike);
  randomSeed(analogRead(A0));
  pinMode(4,INPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);
  lcd.setCursor(0,0);
}



//a%b=a-b*floor(a/b)
int mod(int input,int modulus){
    return input-modulus*floor(input/modulus);
}

void loop() {
  playery=mod((playery-digitalRead(4)),4);
  playery=mod((playery+digitalRead(2)),4);
  lcd.clear();
  lcd.setCursor(1,playery);
  //lcd.print("P");
  lcd.write(0);
  lcd.setCursor(0,0);
  if(spikes_x == -1){
    spikesb = random(1,15);
    for (int i=0; i<4; i++){
      spikes[i] = (spikesb & (1 << i)) >> i; 
    }
    for (int i=0; i<4; i++){
      Serial.print(spikes[i]);
    }
    Serial.println("");
    //spike_y = random(0,4);
    spikes_x = 19;
    score+=1;
    if(mod(score,10)==0){
      Serial.print("Score is now ");
      Serial.print(score);
      Serial.print("; fps is now ");
      Serial.println(fps);
      fps+=1;
    }
  }
  for (int i=0; i<4; i++){
    lcd.setCursor(spikes_x,i);
    if (spikes[i]==1){
      lcd.write(1);
    }
  }
  //lcd.write(1);
  //lcd.print("1");
  spikes_x-=1;
  if((spikes_x == 0) and (spikes[playery] == 1) and not(noclip)){
    lcd.clear();
    lcd.print("You lost");
    lcd.setCursor(0,1);
    lcd.print("Your score: ");
    lcd.print(score);
    delay(3000);
    //Main()
    for (int i=0; score>=0; i++){
      score-=1;
    }
    for (int i=0; fps>4; i++){
      fps-=1;
    }
  }
  delay(1000/fps);
}
