#include <LiquidCrystal.h>
#include <DHT.h>
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int esik1= 600;
int esik2= 300;
int esik3= 800;
int buttonfan= A4;
int buttonfanDurum=0;
int buttonled= A3;
int buttonledDurum=0;
int buttonnem= A5;
int buttonnemDurum=0;
int switch1= 11;
int switch1Durum= 0;
int switch2= 12;
int switch2Durum= 0;
int ldr= A2;
int ldrDurum;
int suseviye= A1;
int suveri;
int topraknem= A0;
int toprakveri;
int fan= 9;
int led= 10;
int sumotoru= 13;
int fanhiz=0;
int ledparlaklik=0;
void setup() {
dht.begin();
lcd.begin(16, 2);
pinMode(buttonfan, INPUT);
pinMode(buttonled, INPUT);
pinMode(buttonnem, INPUT);
pinMode(switch1, INPUT);
pinMode(switch2, INPUT);
pinMode(ldr, INPUT);
pinMode(suseviye, INPUT);
pinMode(topraknem, INPUT);
pinMode(fan, OUTPUT);
pinMode(led, OUTPUT);
pinMode(sumotoru, OUTPUT);
pinMode(1, OUTPUT);
}
void loop() {
 int temp = dht.readTemperature();
 int hum = dht.readHumidity();
  
 buttonledDurum=digitalRead(buttonled);
 buttonfanDurum=digitalRead(buttonfan);
 buttonnemDurum=digitalRead(buttonnem);
 switch1Durum=digitalRead(switch1);
 switch2Durum=digitalRead(switch2);
 ldrDurum=analogRead(ldr);
 suveri=analogRead(suseviye);
 toprakveri=analogRead(topraknem);
 //****su deposu****//
 if(suveri>600){
  digitalWrite(1, HIGH);
 
 }
 if(suveri<300){
  digitalWrite(1, LOW);
 }
//********kullanıcı modu ********//
if(switch1Durum == LOW && switch2Durum==LOW){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("temp:");
lcd.print(temp);
lcd.print("c");
lcd.setCursor(9, 0);
lcd.print("Hum:%");
lcd.print(hum);
lcd.setCursor(0, 1);
lcd.print("L:");
lcd.print(ledparlaklik);
lcd.setCursor(5,1);
lcd.print("F:");
lcd.print(fanhiz);
lcd.setCursor(10, 1);
lcd.print("T:");
lcd.print(esik1);
delay(100);
//******** fan hızı ********//
if(buttonfanDurum == HIGH){
  fanhiz= fanhiz +10;
}
if(fanhiz==260){
  fanhiz=0;
}
analogWrite(fan, fanhiz);
//********led parlaklik********//
if(buttonledDurum == HIGH){
  ledparlaklik= ledparlaklik +10;
}
if(ledparlaklik==260){
  ledparlaklik=0;
}
if(ldrDurum> 900){
  analogWrite(led, ledparlaklik);
}
else{
  analogWrite(led, LOW);
}
//********sulama********//
if(buttonnemDurum==HIGH){
  delay(10);
  esik1= esik1+ 100;
}
if (esik1== 1100){
  esik1=600;
}
if(toprakveri> esik1){
digitalWrite(sumotoru, HIGH);
delay(5000);
digitalWrite(sumotoru, LOW);
delay(5000);
  
}
if(toprakveri<esik1){
  digitalWrite(sumotoru, LOW);
}
 }
 //********yağmur ormanları********//
 if(switch1Durum == HIGH && switch2Durum == LOW){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Yagmur ormani");
lcd.setCursor(0,1);
lcd.print("temp:");
lcd.print(temp);
lcd.print("C");
lcd.setCursor(9, 1);
lcd.print("Hum:%");
lcd.print(hum);
delay(100);
analogWrite(fan, 200);
if (ldrDurum> 900){
  analogWrite( led, 50);
}
  else{
    analogWrite(led, LOW);
    
  }
 //********sulama********//
 if(toprakveri> esik2){
  digitalWrite(sumotoru, HIGH);
  delay(5000);
  digitalWrite(sumotoru, LOW);
  delay(500); 
 }
 if(toprakveri<esik2){
  digitalWrite(sumotoru, LOW);
 }
 }
//********Col********//
 if(switch1Durum == HIGH && switch2Durum == HIGH){
lcd.clear();
lcd.setCursor(5,0);
lcd.print("Col");
lcd.setCursor(0,1);
lcd.print("temp:");
lcd.print(temp);
lcd.print("C");
lcd.setCursor(9, 1);
lcd.print("Hum:%");
lcd.print(hum);
delay(100);
analogWrite(fan, 0);
if (ldrDurum> 900){
  analogWrite( led, 250);
}
  else{
    analogWrite(led, LOW);
    
  }
 //********sulama********//
 if(toprakveri> esik3){
  digitalWrite(sumotoru, HIGH);
  delay(5000);
  digitalWrite(sumotoru, LOW);
  delay(500); 
 }
 if(toprakveri<esik3){
  digitalWrite(sumotoru, LOW);
 }
 
 }
}