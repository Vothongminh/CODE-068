//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int stepPin = 4;//clk+
const int dirPin = 3;//cw`+
#include <Keypad.h>
const byte rows = 4;
const byte columns = 4;
int holdDelay = 50;
int n = 3;
int state = 0;
char key = 0;
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'.', '0', '#', 'D'},
};
char Data[7];
int j = 0; // biến cho Data
boolean demphay = 0; // đếm dấu .
int i = 9; // vi tri lcd khi in số
int conlai = 2;//2 chu so thap phan
int m1 = 0; //đơn vị
int m2 = 0; //thập phân 1
int m3 = 0; //thập phân 2
int m4 = 0; //thập phân 3
int m5 = 0; //thập phân 4
int m0 = 0; // số trung gian
int demso = 6; // so < 10 (0 - 6 có 7 giá trị x.xxxx)
float clockstep = 0; //số vòng đk motor
byte rowPins[rows] = {9, 10, 11, 12};
byte columnPins[columns] = {5, 6, 7, 8};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
//.........................................................................
void setup()
{
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("WELLCOME");
  chaychu();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("So vong:        ");
  lcd.setCursor(0, 1);
  lcd.print("Hay nhap so vong");
}
//.........................................................................
void loop()
{
readd:
  char temp = keypad.getKey();
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
      //Serial.println(key);
      if (key == 'D')
      {
done:
        lcd.setCursor(9, 0);
        lcd.print("        ");
        i = 9;
        j = 0;
        demphay = 0;
        demso = 6;
        for (int a = 0; a < 7; a++)
        {
          Data[a] = ' ';
        }
        Serial.println(Data);
        goto readd;
      }
      if (key == 'A')
      {
        Serial.println("chay thuan");
        digitalWrite(dirPin, LOW);
        value();
        chaymotor();
        goto done;
      }
      if (key == 'B')
      {
        Serial.println("chay nghich");
        digitalWrite(dirPin, HIGH);
        value();
        chaymotor();
        goto done;
      }
      if (key == '#')
      {
        goto readd;
      }
      if (key == 'C')
      {
        goto readd;
      }
      if ((( i == 9) && (key == '.')) || ((demphay == 1) && (key == '.')))
      {
        goto readd;
      }
      if (key == '.')
      {
        demphay = 1;
      }
      if (demso == 0)
      {
        goto readd;
      }
      if ((i == 10) && (key != '.'))
      {
        goto readd;
      }
      lcd.setCursor(i, 0);
      lcd.print(key);
      Data[j] = key;
      Serial.println(Data);
      demso--;
      i++;
      j++;
    }
  }
  delay(100);
}
//.........................................................................
void chaychu()
{
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
//.........................................................................
void chaymotor()
{
  Serial.println(clockstep * 3200);
  for (int x = 0; x < clockstep * 3200 ; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1500);
  }
}
//.........................................................................
void value()
{
  for (int b = 0; b < 6; b++)
  {
    if (Data[b] == '1')
    {
      m0 = 1;
    }
    if (Data[b] == '2')
    {
      m0 = 2;
    }
    if (Data[b] == '3')
    {
      m0 = 3;
    }
    if (Data[b] == '4')
    {
      m0 = 4;
    }
    if (Data[b] == '5')
    {
      m0 = 5;
    }
    if (Data[b] == '6')
    {
      m0 = 6;
    }
    if (Data[b] == '7')
    {
      m0 = 7;
    }
    if (Data[b] == '8')
    {
      m0 = 8;
    }
    if (Data[b] == '9')
    {
      m0 = 9;
    }
    if (Data[b] == '0')
    {
      m0 = 0;
    }
    if (b == 0)
    {
      m1 = m0;
    }
    if (b == 2)
    {
      m2 = m0;
    }
    if (b == 3)
    {
      m3 = m0;
    }
    if (b == 4)
    {
      m4 = m0;
    }
    if (b == 5)
    {
      m5 = m0;
    }
    m0 = 0;
  }
  clockstep = m1 + m2 * 0.1 + m3 * 0.01 + m4 * 0.001 + m5 * 0.0001;
  Serial.println(clockstep);
}
