#include <TEA5767.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
TEA5767 Radio;

unsigned char freqH = 0;
unsigned char freqL = 0;
unsigned int freq1;
double frequency;
int old=0;


void setup()
{
  Wire.begin();
  frequency = 101.0; //starting frequency
  old=frequency;
  Radio.init();
  Radio.set_frequency(frequency);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("RADIO: ");
  lcd.setCursor(0,1);
  lcd.print("FQ: ");
  lcd.print(frequency);
  Serial.begin(9600);
}

void loop()
{
  int reading = analogRead(A2);
  int  btn_read = analogRead(A0);
  if (reading != old ){
    frequency = ((double)reading * (108.0 - 87.5)) / 1024.0 + 87.5;
      frequency = ((int)(frequency * 10)) / 10.0;
    // Radio.set_frequency(frequency);
     lcd.setCursor(4,1);
     lcd.print(frequency);
     Serial.println(frequency);
     delay(1000);
     old=reading;
    }
  else
  {lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);}

  if (btn_read <= 20){
   Radio.set_frequency(frequency);
  }
  
}
