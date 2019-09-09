#include "LiquidCrystal.h"
#include "Password.h"
#include "Keypad.h"
#include "Servo.h"
 
Servo myservo;
int LEDhijau = 11;
int Relay    = 12;
int Buzzer   = 13;
int Wipe     = 10;
Password password = Password( "12345" ); //Sandi
LiquidCrystal lcd(19, 18, 17, 16, 15, 14);

const byte baris = 4; //Baris
const byte kolom = 3; //Kolom

char keys[baris][kolom] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte barisPin[baris] = {9,8,7,6};
byte kolomPin[kolom]= {5,4,3};

// Buat objek keypad
Keypad keypad = Keypad( makeKeymap(keys), barisPin, kolomPin, baris, kolom );

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Access Controlv1");
  lcd.setCursor(3,1);
  lcd.print("Dicky B_Mz");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Selamat Datang ");
  lcd.setCursor(0,1);
  lcd.print("------>><<------");
  delay(1000);
  lcd.clear();
  Serial.begin(9600);
  delay(200);
  pinMode(LEDhijau, OUTPUT);  //Indikator Terbuka
  pinMode(Relay,    OUTPUT);  //terhubung ke selenoid
  pinMode(Buzzer,    OUTPUT);  //Terhubung Ke Buzzer
  pinMode(Wipe,     INPUT_PULLUP);
  myservo.attach(2); //Servo pada pin 2
  keypad.addEventListener(keypadEvent);
  
}

void loop(){
  keypad.getKey();
  lcd.setCursor(0,0); 
  lcd.print("Enter Password: ");
  lcd.setCursor(2,1);
  lcd.print("<<======= B_Mz");
  myservo.write(180);
  
  if (digitalRead(Wipe) == LOW) {
    myservo.write(0);
    digitalWrite(Relay, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Akses Diterima!!");
    lcd.setCursor(1,1);
    lcd.print("Silahkan Masuk");
    delay(5000);
    myservo.write(180);
    digitalWrite(Relay, LOW);
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Enter Password: ");
    lcd.setCursor(2,1);
    lcd.print("<<======= B_Mz");
  }
  }
  
  void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Enter Password: ");
  lcd.setCursor(2,1);
  lcd.print("<<======= B_Mz");
  lcd.setCursor(0,1);
  lcd.print(eKey);
  delay(10);
  
 
  Serial.write(254);
 
  switch (eKey){
    case '#': Login(); delay(1); break;
   
    case '*': password.reset(); delay(1); break;
   
     default: password.append(eKey); delay(1);
    }
  }
}

void Login(){
if (password.evaluate()){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Akses Diterima!!");
    lcd.setCursor(1,1);
    lcd.print("Silahkan Masuk");
    myservo.write(0);
    digitalWrite(LEDhijau, HIGH);
    digitalWrite(Relay, HIGH);
    delay(5000);
    myservo.write(180);
    digitalWrite(LEDhijau, LOW);
    digitalWrite(Relay, LOW);
    lcd.clear();
    delay(200);
    lcd.setCursor(0,0); 
    lcd.print("Enter Password: ");
    lcd.setCursor(2,1);
    lcd.print("<<======= B_Mz");
}

else{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Akses Ditolak!");
    lcd.setCursor(0,1);
    lcd.print("Ulangi Password!");
    myservo.write(180);
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Enter Password: ");
    lcd.setCursor(2,1);
    lcd.print("<<======= B_Mz");
  }
}
