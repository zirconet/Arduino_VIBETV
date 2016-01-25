//Progetto VI.BE.TV 
//Acquisizione dati da modulo sensore ultrasuoni per gestire sistema allerta e comando IR

//COMPONENTI:
//Arduino Uno
//sensore HC-SR04
//led rosso
//buzzer

//Librerie
#include <IRremote.h> //Libreria controllo IR

//Dichiarazioni
IRsend irsend;
unsigned int powerOn[68] = {4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};
const int triggerPort = 6; //Trigger Ultrasuoni 
const int echoPort = 7; //Echo Ultrasuoni
const int buzzer = 12; //buzzer
const int ledR = 10; //led rosso (1,8V) - utilizzata resistenza 330K
int led = 0; //variabile per controllo led iniziale
int alert = 0; //variabile controllo allarmi
int alt = 0; //variabile controllo riattivazione
int temp = 5000; //variabile controllo delay ultrasuoni
const int Bar0 = 200; //limite MAX ultrasuoni
const int Bar1 = 150; //limite INT ultrasuoni
const int Bar2 = 80;  //limite MIN ultrasuoni

//Inizializzazione 
void setup() 
{
  pinMode(buzzer, OUTPUT);
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(ledR, OUTPUT);
  Serial.begin(9600);
  Serial.println( "Sensore Ultrasuoni :  ");
}

//Programma 
void loop() 
{ 
  if (led == 0) 
    {
     boot (200);
    }
    
  ////////////////LANCIO ECO TRIGGER////////
  /////////////////////////////////////////
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );

  //calcolo distanza
  long durata = pulseIn( echoPort, HIGH );
  long distanza = 0.034 * durata / 2;
 
  //dopo 38ms è fuori dalla portata del sensore
  if( durata > 38000 )
    {
      Serial.println("Fuori portata   ");
    }
    else
    { 
      Serial.print("distanza:    ");
      Serial.print(distanza);
      Serial.println(" cm     ");
    }    
  ////////FINE ECO TRIGGER//////////////////
  /////////////////////////////////////////
  
  if (distanza > Bar0) 
   {
      digitalWrite(ledR, LOW );
      alert = 0;
      temp = 5000;
      if (alt==1)
        {
          beep(100);
          delay(50);
          beep(50);
          alt =0; 
          segnaleIR();  
          delay(10000);
        }
    }

  if (distanza > Bar1 && distanza < Bar0) 
    {
      digitalWrite(ledR, LOW );
      alert = 0; 
      temp = 3000;
      if (alt==1)
        {
          beep(100);
          delay(50);
          beep(50);
          alt =0; 
          segnaleIR();  
          delay(10000);
        }
    }  

  if (distanza > Bar2 && distanza < Bar1) 
    {
      digitalWrite(ledR, LOW );
      alert = 0; 
      temp = 2000;
      if (alt==1)
        {
          beep(100);
          delay(50);
          beep(50);
          alt =0; 
          segnaleIR(); 
          delay(10000); 
        }
    }  

  if (distanza < Bar2) 
    {
      digitalWrite(ledR, HIGH ); 
      alert = alert +1;
      temp = 500;
      if (alt==1) beep(50);
      if (alert>10 & alt==0) 
        {
          beep(250);
          segnaleIR(); 
          alert = 0;
          alt = 1;
          delay(5000);
          digitalWrite(ledR, LOW );
        }  
    }
 

  Serial.print(temp/1000); 
  Serial.println(" s = delay     ");
  Serial.print(led); 
  Serial.println(" = cicli     ");
  Serial.print(alert); 
  Serial.println(" = alarm     ");
  Serial.print(alt); 
  Serial.println("  = alt     ");
  led = led +1;
  delay(temp);

}



void segnaleIR()
  { 
    delay(1000);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    irsend.sendRaw(powerOn,68,38);
    delay(100);
    Serial.println("<---- SEGNALE INFRAROSSO INVIATO");
  }



void beep(unsigned char delayms)
  {
    analogWrite(buzzer, 200);      // Almost any value can be used except 0 and 255
    delay(delayms);          // wait for a delayms ms
    analogWrite(buzzer, 0);       // 0 turns it off
  }  
  
 
  
void boot(unsigned char delayms)
  {
  beep(50);
  delay(delayms);
  beep(100);
  digitalWrite(ledR, HIGH );
  delay(delayms);
  digitalWrite(ledR, LOW );
  delay(delayms-50);
  digitalWrite(ledR, HIGH );
  delay(delayms);
  digitalWrite(ledR, LOW );
  Serial.println( "--> Inizializzato ");
  }
  





