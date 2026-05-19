#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDRESS 0x27
LiquidCrystal_I2C lcd(I2C_ADDRESS, 20, 4);

int mod(int input,int modulus){
  for(int i=0; !(input<modulus) || input<0; i++){
    if(input>=modulus){
      input-=modulus;
    }
    if(input<0){
      input+=modulus;
    }
}
int game = 0;

//PONG
byte ball[] = {
    0b00000,
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00000
  };

  byte paddlel[] = {
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001
  };

  byte paddler[] = {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000
  };
lcd.createChar(0, ball);
lcd.createChar(1, paddlel); 
lcd.createChar(2, paddler); 
int ballx = random(8,13);
int bally = random(0,4);
int directionx = random(0,2)*2-1;
int directiony = random(0,3)-1;
int ply = 1;
int plscore = 0;
int pry = 1;
int prscore = 0;
bool running = true;

int Pong(){
    pry=mod((pry+digitalRead(8)),4);
    pry=mod((pry-digitalRead(7)),4);
    ply=mod((ply-digitalRead(4)),4);
    ply=mod((ply+digitalRead(2)),4);
    
    ballx+=directionx;
    bally+=directiony;
    if(bally == 0) directiony=1;
    if(bally == 3) directiony=-1;
    if(ballx == 19){
      prscore+=1;
      delay(500);
      ballx=random(8,13);
      bally=random(0,4);
      directionx*=-1;
      directiony=random(-1,2);
    }
    if(ballx == 17) {
      if(bally == pry){
        directionx = -1;
        if(bally==0){
          directiony=random(0,2);
        }
        else if(bally==3){
          directiony=random(-1,1);
        }
        else{
          directiony = random(-1,2);
        }
      }
    }
    if(ballx == 2) {
      if(bally == ply){
        directionx = 1;
        directiony = random(-1,2);
        
      }
    }
    if(ballx == 0){
      plscore+=1;
      delay(500);
      ballx=random(8,13);
      bally=random(0,4);
      directionx*=-1;
      directiony=random(-1,2);

    }
    Serial.print("Ball x: ");
    Serial.print(ballx);
    Serial.print("Ball y: ");
    Serial.print(bally);
    lcd.clear();
    lcd.setCursor(ballx,bally);
    lcd.write(0);
    lcd.setCursor(1,ply);
    lcd.write(1);
    lcd.setCursor(18,pry);
    lcd.write(2);
    delay(200);

    if(plscore==11){
      lcd.clear();
      lcd.setCursor(1,3);
      lcd.write("Player 1 won!!");
      delay(10000);
      Main();
    }
    if(prscore==11){
      lcd.clear();
      lcd.setCursor(1,3);
      lcd.write("Player 2 won!!");
      delay(10000);
      Main();
    }
}
//END OF PONG

//RUN MAN
byte player[] = {
  0b01110,
  0b01110,
  0b01110,
  0b00101,
  0b11111,
  0b10100,
  0b00100,
  0b01010
};

byte block[] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
lcd.createChar(3, player);
lcd.createChar(4, block);
int playery = 1;
int hole_y = 1;
int score = 0;
int print = 0;

int RunMan(){
  playery=mod((playery-digitalRead(4)),4);
  playery=mod((playery+digitalRead(2)),4);
  lcd.clear();
  lcd.setCursor(1,playery);
  lcd.write(0);
  hole_y = random(1,4);
  for(unsigned char i = 0; i<4; i++){
    if(print !== hole_y){
      print+=1;
    }
    lcd.setCursor(19,print);
    lcd.write(1);  }
}
//END OF RUN MAN


int BallDash(){

}


int Main(){
  lcd.print("Welcome to Bloxed.");
  lcd.setCursor(0,1)
  lcd.print("1: Pong 2: Run Man");
  lcd.setCursor(0,2)
  lcd.print("3: Ball Dash");
  game += digitalRead(2);
  game += (digitalRead(4))*2;
  game += (digitalRead(2))*3;
  if(game == 1){
    Pong();
  }
  else if(game == 2){
    RunMan();
  }
  else if(game == 3){
    BallDash();
  }
}

void setup() {
  Main();
}