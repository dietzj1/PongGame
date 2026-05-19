#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDRESS 0x27
LiquidCrystal_I2C lcd(I2C_ADDRESS, 20, 4);

// Set the LCD address to 0x27 for a 20 chars and 4 line display (check your address if different)

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

  int ballx = random(8,13);
  int bally = random(0,4);
  int directionx = random(0,2)*2-1;
  int directiony = random(0,3)-1;
  int ply = 1;
  int plscore = 0;
  int pry = 1;
  int prscore = 0;
  bool running = true;

 
  void setup() {
    Serial.begin(9600);
    lcd.init();      // Initialize the lcd
    lcd.backlight(); // Turn on the backlight
    randomSeed(analogRead(A0));
    pinMode(7,INPUT);
    pinMode(8,INPUT);
    pinMode(4,INPUT);
    pinMode(2,INPUT);

    // Create the custom character in location 0
    lcd.createChar(0, ball);
    lcd.createChar(1, paddlel);
    lcd.createChar(2, paddler);
    lcd.clear();
    lcd.setCursor(10,2);
    lcd.write(0);
    lcd.setCursor(9,0);
  }
int mod(int input,int modulus){
    for(int i=0; !(input<modulus) || input<0; i++){
      if(input>=modulus){
        input-=modulus;
      }
      if(input<0){
        input+=modulus;
      }
    }
    return input;
  /*int status=lcd.begin(20,4);
    if (status) {
      Serial.println("Lcd Init Error");
    }
*/
  }

  void loop() {
    /*
    Serial.print(digitalRead(8));
    Serial.print(digitalRead(7));
    Serial.print(digitalRead(4));
    Serial.println(digitalRead(2));
    */
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
   
  // Set the cursor to column 0, row 0 (top left)
  // Write the custom character (stored at location 0)
    lcd.clear();
    lcd.setCursor(ballx,bally);
    //lcd.write(0);
    lcd.print("O");
    lcd.setCursor(1,ply);
    //lcd.write(1);
    lcd.print("L");
    lcd.setCursor(18,pry);
    //lcd.write(2);
    lcd.print("R");
    delay(250);

    if(plscore==11){
      lcd.clear();
      lcd.setCursor(1,3);
      lcd.write("Player 1 won!!");
      delay(10000);
      exit(0);
    }
    if(prscore==11){
      lcd.clear();
      lcd.setCursor(1,3);
      lcd.write("Player 2 won!!");
      delay(10000);
      exit(0);
    }
  }
