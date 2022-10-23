#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

byte cirnoEye[8] = {
  0b00000,
  0b11111
  ,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};

byte cirnoMouth[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01010,
  0b00100
};

int redButton = 0;
int blueButton = 0;

int redScore = 0;
int blueScore = 0;
  
void setup(){
  lcd.init(); // initialize the lcd
  lcd.backlight();

  lcd.createChar(0, cirnoEye);
  lcd.createChar(1, cirnoMouth);
  
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("'Funky Time!'");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("   -Cirno 1984"); // print message at (2, 1)

  lcd.setCursor(1, 1);
  lcd.write((byte)0);
  lcd.setCursor(3, 1);
  lcd.write((byte)0);
  lcd.setCursor(2, 1);
  lcd.write((byte)1);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(12, INPUT); // RED
  pinMode(13, INPUT); // BLUE

  pinMode(7, OUTPUT); // RED

  Serial.begin(9600); // open the serial port at 9600 bps:

}

void loop(){

  digitalWrite(7, HIGH);

  delay(1000);
  lcd.init();

  lcd.setCursor(0, 0);
  lcd.print("RED: ");
  lcd.setCursor(0, 1);
  lcd.print("BLU: ");
  
  while (true) {
    for (int i = 6; i > 1; i--) {

      redButton = digitalRead(12);
      blueButton = digitalRead(13);
      
      digitalWrite(i, HIGH);
      
      redButton = digitalRead(12);
      blueButton = digitalRead(13);
      
      digitalWrite((i + 6), HIGH);
      
      redButton = digitalRead(12);
      blueButton = digitalRead(13);
      
      delay(100);
      
      redButton = digitalRead(12);
      blueButton = digitalRead(13);
      
      digitalWrite(i, LOW);
      
      redButton = digitalRead(12);
      blueButton = digitalRead(13);
      digitalWrite((i + 6), LOW);
      
      redButton = digitalRead(12);
      blueButton = digitalRead(13);

      if ((i + 6) == 8 && blueButton == LOW){
        blueScore++;
        lcd.setCursor(0, 1);
        lcd.print("BLU: ");
        lcd.print(blueScore);
      }

      if (i == 2 && redButton == LOW){
        redScore++;
        lcd.setCursor(0, 0);
        lcd.print("RED: ");
        lcd.print(redScore);
      }
      
      if (redScore == 10 && blueScore < 10) {
        lcd.init();
        lcd.print("Red Wins!!! <3");
        lcd.setCursor(0, 1);
        lcd.write((byte)0);
        lcd.setCursor(2, 1);
        lcd.write((byte)0);
        lcd.setCursor(1, 1);
        lcd.write((byte)1);
        lcd.setCursor(0, 1);
        
        break;
        }

      if (blueScore == 10 && redScore < 10) {
        lcd.init();
        lcd.print("Blue wins!!! <3");
        lcd.setCursor(0, 1);
        lcd.write((byte)0);
        lcd.setCursor(2, 1);
        lcd.write((byte)0);
        lcd.setCursor(1, 1);
        lcd.write((byte)1);
        lcd.setCursor(0, 1);
         break;
      }

      if (blueScore >= 10 && redScore >= 10) {
        lcd.init();
        lcd.print("Draw!!! <3");
        lcd.setCursor(0, 1);
        lcd.write((byte)0);
        lcd.setCursor(2, 1);
        lcd.write((byte)0);
        lcd.setCursor(1, 1);
        lcd.write((byte)1);
        lcd.setCursor(0, 1);

         break;
        }
      }
    }    
  }
