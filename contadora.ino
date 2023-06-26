#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int valor,sementes=0;
bool detectado=false;
int sensibilidade=200;
int normalidade=50;

unsigned long tempo_atual;
int iniciar=8,zerar=9,menos=10,mais=11,parar=12,passo=13;
int total=0,incremento=10;
int distribuidor=15;

void setup(){
  //Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(distribuidor,OUTPUT);
  digitalWrite(distribuidor,HIGH);
  pinMode(iniciar,INPUT_PULLUP);
  pinMode(zerar,INPUT_PULLUP);
  pinMode(mais,INPUT_PULLUP);
  pinMode(menos,INPUT_PULLUP);
  pinMode(parar,INPUT_PULLUP);
  pinMode(passo,INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONTADOR SEMENTE");
  lcd.setCursor(0, 1);
  lcd.print("Contar: 0");
}

void loop(){
  tempo_atual = millis();
  if(!digitalRead(iniciar)){
    if(total>0){
      digitalWrite(distribuidor,LOW);
    }
    delay(300);
  }
  if(!digitalRead(zerar)){
    sementes=0;
    sementeVisor();
    delay(300);
  }
  if(!digitalRead(mais)){
    total+=incremento;
    sementeVisor();
    delay(300);
  }
  if(!digitalRead(menos)){
    if(total-incremento>=0){
      total-=incremento;
      sementeVisor();
      delay(300);
    }
    
  }
  if(!digitalRead(parar)){
    digitalWrite(distribuidor,HIGH);
    delay(300);
  }
  if(!digitalRead(passo)){
    if(incremento==10){
      incremento = 100;
    }else{
      incremento = 10;
    }
    delay(300);
  }
  valor = analogRead(A0);
  //if(valor>sensibilidade){
    //Serial.println(valor);
  //}
  if(valor>sensibilidade && detectado==false){
    detectado = true;
    sementes++;
    sementeVisor();
    if(sementes>=total){
      digitalWrite(distribuidor,HIGH);
    }
    /*Serial.println("");
    Serial.print(sementes);
    Serial.print(" sementes - ");
    Serial.println(valor);*/
  }else if(valor<normalidade){
    /*if(detectado){
      Serial.println("/\\");      
    }*/
    detectado = false;
  }
  /*else{
    Serial.print(valor);
    Serial.print(" - ");
  }*/
}
void sementeVisor(){
  lcd.setCursor(8, 1);
  lcd.print("        ");
  lcd.setCursor(8, 1);
  lcd.print(sementes);
  lcd.print("/");
  lcd.print(total);
}
