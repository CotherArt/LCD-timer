// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int relay = 8, pot = 0;
int seviche_pin = 10;
int seviche = 0;
boolean reset = false;
const int buttonPin = 9;
int buttonState = 0;
int flag = 0;

int val = 0;
int time;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// LCD dimentions
const int xlen = 16, ylen = 2;

int incomingByte = 0; // for incoming serial data
String incomingString = "";

void centerMsg(String msg, byte pos){
  int center = xlen / 2 - msg.length() / 2 - 1;
  lcd.setCursor(center,pos);
  lcd.print(msg);
}

void selectTime(){
  centerMsg("---Tiempo---", 0);
  time = map(analogRead(pot), 0, 1023, 0, 300);
  centerMsg((String)time+"s", 1);
  delay(100);
  reset = true;
}

void timerMode(int time){
  digitalWrite(relay, HIGH);
  do{
    lcd.clear();
    centerMsg("Cofee time wuuu!!",0);
    centerMsg((String)time+"s",1);
    delay(1000);
    time--;
  }while(time > -1);
  lcd.clear();
  centerMsg("Listo K listo!",0);
  digitalWrite(relay, LOW);
  reset = false;
  delay(2000);
}

void ini_msg(){
  centerMsg("Welcome to", 0);
  centerMsg("Coffee timer uwu", 1);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(xlen, ylen);
  pinMode(relay, OUTPUT);
  pinMode(seviche_pin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  
  ini_msg();
  delay(1000);
}

void loop() {


  lcd.clear();
  seviche = digitalRead(seviche_pin);
  
  if(seviche == HIGH){
    selectTime();
    buttonState = digitalRead(buttonPin);
  }else{
    if(reset == true){
      Serial.println("timer mode");
      timerMode(time);
    }
    ini_msg();
  }
  
  
  delay(200);
//  digitalWrite(relay, HIGH);
}
