#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variables won't change

const int  mayusPin = 6;
const int minusPin = 7;  
const int numbersPin = 8;
const int  enterPin = 9;  
const int trPin=13;
//Arrays

char mayus[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char minus[26] = {'0','1','2','3','4','5','6','7','8','9'};
char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};

// Variables will change:

//Buttons
int enterState;       
int lastEnterState = 0;    
int mayusState;       
int lastMayusState = 0;
int minusState;       
int lastMinusState = 0;
int numbersState;       
int lastNumbersState = 0;
int trState;
int lastTrState=0;
String msj="";
String auxmsj="";
char ms="";
boolean tr=false;
int a = 0; //Cursor

// Contadores
int i = 0;  
int j = 0;  
int k = 0;  

void setup() {

  //Activate pin
   pinMode(mayusPin, INPUT);
   pinMode(minusPin, INPUT);
   pinMode(numbersPin, INPUT);
   pinMode(enterPin, INPUT);
   pinMode(trPin, INPUT);

   trState=digitalRead(trPin);
   mayusState = digitalRead(mayusPin);  
   minusState = digitalRead(minusPin);   
   numbersState = digitalRead(numbersPin);   
   enterState = digitalRead(enterPin);   
   
   lcd.begin(16,2);
   Serial.begin(9600);
   
}


void loop() {

  // Leer estado
   mayusState = digitalRead(mayusPin);  
   minusState = digitalRead(minusPin);   
   numbersState = digitalRead(numbersPin);   
   enterState = digitalRead(enterPin);   
   trState=digitalRead(trPin);

   if (mayusState != lastMayusState) {
      if(mayusState == HIGH){
           if(i<26){
              lcd.setCursor(a,0);
              lcd.print(mayus[i]);
              auxmsj=mayus[i];
              i++;
              
              j=0;
              k=0;
              delay(500);
           }
          else{
            i=0;
            j=0;
            k=0;
          }
      }
  }

     if (minusState != lastMinusState) {
      if(minusState == HIGH){
           if(j<26){
              lcd.setCursor(a,0);
              lcd.print(minus[j]);
              auxmsj=minus[j];
              j++;
              i=0;
            
              k=0;
              delay(500);
           }
          else{
            i=0;
            j=0;
            k=0;
          }
      }
  }

    /* if (numbersState != lastNumbersState) {
      if(numbersState == HIGH){
           if(k<10){
              lcd.setCursor(a,0);
              lcd.print(numbers[k]);
              auxmsj=numbers[k];
              k++;
              i=0;
              j=0;
            
              delay(500);
           }
          else{
            i=0;
            j=0;
            k=0;
          }
      }
  }
*/

if (numbersState != lastNumbersState) {
      if(numbersState == HIGH){
        if(msj!=""){
          Serial.print(msj);
          msj="";
          lcd.clear();
          a=0;
          lcd.print("Mensaje enviado");
          delay(2000);
          lcd.clear();
        }else{
           if(Serial.available()>0){
            lcd.print("Recibiendo...");
            delay(2000);
            lcd.clear();
            String rec= Serial.readString(); 
            lcd.print(rec);
            delay(5000);
            lcd.clear();
           }
        }
      }
}

//   if(Serial.available()>0){
//        lcd.clear();
////        lcd.setCursor(0,2);
////        lcd.print('*');
//        String rec="";
//            rec= Serial.readString(); 
//            lcd.print(rec);
//       }

  /*if (trState != lastTrState) {
      if(numbersState == HIGH){
        if(msj!=""){
          Serial.print(msj);
          msj="";
          lcd.clear();
          lcd.setCursor(0,0);
        }else{
           if(Serial.available()>0){
            String rec= Serial.readString(); 
            lcd.print(rec);
           }
        }
      }
  }*/
  if(enterState != lastEnterState){
    if(enterState == HIGH){
      if(auxmsj==""){
        auxmsj=" ";
      }
        msj=msj+auxmsj;
        a++;
        i=0;
        j=0;
        k=0;
        delay(200);
        auxmsj="";
    }
  }




  //Guardar estados actuales
  lastMayusState = mayusState;
  lastMinusState = minusState;
  lastNumbersState = numbersState;
  lastEnterState = enterState;
  lastTrState=trState;

 
}
