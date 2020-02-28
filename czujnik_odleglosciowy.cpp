#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float odleglosc(int trigger, int echo); //deklaruje funkcje
LiquidCrystal_I2C lcd(0x3F, 16, 2); //inicjalizuje wyswietlacz



int trig1=2; //prypisuje piny czujnikow 
int trig2=10;
int echo1=3;
int echo2=11;
int buzzer=4;
int led=5; 
float czujnik1, czujnik2;



void setup() {

lcd.begin();
pinMode(trig1,OUTPUT);
pinMode(trig2,OUTPUT);
pinMode(echo1,INPUT);
pinMode(echo2,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(led,OUTPUT);

}



void loop() {

  czujnik1=odleglosc(trig1,echo1);
  czujnik2=odleglosc(trig2,echo2);

  if(czujnik1 <= 7 || czujnik2 < 7){
    digitalWrite(led,LOW);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Zaraz");
    lcd.setCursor(4,1);
    lcd.print("uderzysz");

    digitalWrite(led, HIGH);
    tone(buzzer, 450); // przyjmuje pin oraz przyjmuje liczbe Hz ktore ma wygenerowac dzwiek
    delay(200);
    noTone(buzzer);
    delay(200);
  }

  else if((7 < czujnik1 && czujnik1 < 15)||(7 < czujnik2 && czujnik2 < 15)){
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Uwaga");
    lcd.setCursor(3,1);
    lcd.print("jest blisko");
    digitalWrite(led, HIGH);
    delay(500);


  }

  else
  {
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dis1: ");
    lcd.setCursor(0,1);
    lcd.print(czujnik1);
    
    lcd.setCursor(9,0);
    lcd.print("Dis2: ");
    lcd.setCursor(9,1);
    lcd.print(czujnik2);
    delay(1000);
  }
  

}
float odleglosc(int trigger, int echo){
  long czas_trasmisji;
  float dystans;
  
  digitalWrite(trigger,LOW);  //ustawiam wartosc triggera na stan niski,upewniam sie ze jest na stane niskim, czyli wylanczam czujnik
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);// aby czujnik zaczol liczyc odleglosc stan wysoki musi znajowac sie prze 10ms 
  delayMicroseconds(10);
  digitalWrite(trigger,LOW); //wylanczam czujnik

  
  czas_trasmisji = pulseIn(echo,HIGH); //przyjmuje dwa parametry numer pinu, drugie jakiego impulsu chcemy zmiezyc, czyli jak dlugo pin echo bedzie w stanie wysokim
  dystans = czas_trasmisji/58.f;

  return dystans; 
}
