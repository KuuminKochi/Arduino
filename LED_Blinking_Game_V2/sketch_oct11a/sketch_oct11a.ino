#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

// ------------------------------------
// CUSTOM BYTE THINGS

byte cirnoEye[8] = {
  0b00000,
  0b11111,
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


// --------------------------------------

// DETECTS RED BLUE BUTTON ON/OFF 
int redButton = 0;
int blueButton = 0;

// RED BLUE SCORE
int redScore = 0;
int blueScore = 0;

// RED PINS
int redLED1 = 2;
int redLED2 = 3;
int redLED3 = 4;
int redLED4 = 5;

// BLUE PINS
int blueLED1 = 6;
int blueLED2 = 7;
int blueLED3 = 8;
int blueLED4 = 9;

// RED BLUE IN
int redButtonPin = 10;
int blueButtonPin = 11;


// POWER SOURCE
int outPin = 12;

void setup(){
  lcd.init(); // INITIALISE LCD SCREEN
  lcd.backlight(); // ACTIVATE BACKLIGHT

  lcd.createChar(0, cirnoEye); // INITIALIZE CIRNO'S EYES
  lcd.createChar(1, cirnoMouth); // INITIALIZE CIRNO'S MOUTH
  
  lcd.setCursor(0, 0);         // MOVE TO (0, 0)
  lcd.print("'V2 Time!'");  // PRINT TEXT AT (0, 0)
  lcd.setCursor(2, 1);         // MOVE TO (2, 1)
  lcd.print("   -Nitori 1984"); // PRINT TEXT AT (2, 1)

  // DRAW CIRNO FACE
  lcd.setCursor(1, 1);
  lcd.write((byte)0);
  lcd.setCursor(3, 1);
  lcd.write((byte)0);
  lcd.setCursor(2, 1);
  lcd.write((byte)1);

  
  pinMode(redLED1, OUTPUT);
  pinMode(redLED2, OUTPUT);
  pinMode(redLED3, OUTPUT);
  pinMode(redLED4, OUTPUT);

  pinMode(blueLED1, OUTPUT);
  pinMode(blueLED2, OUTPUT);
  pinMode(blueLED3, OUTPUT);
  pinMode(blueLED4, OUTPUT);

  pinMode(redButtonPin, INPUT); // RED
  pinMode(blueButtonPin, INPUT); // BLUE

  pinMode(outPin, OUTPUT); //  RED

  Serial.begin(9600); // open the serial port at 9600 bps:

}

void loop(){

  digitalWrite(7, HIGH);

  delay(500);
  lcd.init();

  lcd.setCursor(0, 0);
  lcd.print("RED: ");
  lcd.setCursor(0, 1);
  lcd.print("BLU: ");
  
  while (true) {
    for (int i = 5; i > 1; i--) {

      redButton = digitalRead(redButtonPin);
      blueButton = digitalRead(blueButtonPin);
      
      digitalWrite(i, HIGH);
      digitalWrite((i + 4), HIGH);

      delay(100);

      redButton = digitalRead(redButtonPin);
      blueButton = digitalRead(blueButtonPin);
      
      digitalWrite(i, LOW);
      digitalWrite((i + 4), LOW);
      
      redButton = digitalRead(redButtonPin);
      blueButton = digitalRead(blueButtonPin);

      if ((i + 4) == 9 && blueButton == LOW){
        blueScore++;
        lcd.setCursor(0, 1);
        lcd.print("BLU: ");
        lcd.print(blueScore);
      }

      if (i + 0 == 5 && redButton == LOW){
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
