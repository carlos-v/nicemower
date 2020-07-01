#include <SoftwareSerial.h>
#include <stdio.h>


//cambio para pin 13 por defecto
int ledONE = 13;
//int ledONE = 9;
int ledTWO = 5;
int ledTHREE = 6;


int bluetoothTX = 3 ;
int bluetoothRX = 2 ;
char receivedValue ;

SoftwareSerial bluetooth ( bluetoothTX, bluetoothRX );

void setup()
{
  delay(200);
  Serial.begin(9600);
  while (!Serial) ;  // wait for Arduino Serial Monitor

  Serial.println("console> ");
  
  pinMode(ledONE, OUTPUT);
  pinMode(ledTWO, OUTPUT);
  pinMode(ledTHREE, OUTPUT);
 
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

}


void loop()
{
int brightness = 0;
int led = 0;
signed int data = 0;

 if( bluetooth.available() )
  {
    data = (int) bluetooth.read();
    Serial.println( data );                 // for debugging, show received data

      if(data == 26) 
      {
        allDown() ;
      }else if(data == 89)
      {
        allUp() ;
      }else{
        
      led = data / 100;                     // which led to select ?
      brightness = data % 100 ;             // 0 - 25 , LED brightness ( * 10 ) for actual value
           
    switch(led)                             // Now, let's select the right led.
    {
      
      case 0  : setLEDthree ( brightness * 10 );  break;
      case 1  : setLEDone ( brightness * 10 );    break;
      case 2  : setLEDtwo ( brightness * 10 );    break;
      default : setLEDthree ( brightness * 10 );  break;       // DO NOT know what to do ? must be led 3
      
    }
      }

    bluetooth.flush();                       // IMPORTANT clean bluetooth stream, flush stuck data

  }

}


// SHUT DOWN all leds
void allDown()
{
    digitalWrite(ledONE,  LOW ) ; 
     digitalWrite(ledTWO,  LOW ) ; 
      digitalWrite(ledTHREE,  LOW ) ; 
}

// ALL up now :)

void allUp()
{
    digitalWrite(ledONE,  HIGH) ; 
     digitalWrite(ledTWO,  HIGH ) ; 
     digitalWrite(ledTHREE,  HIGH ) ; 
}


void setLEDone(int brighteness)
{
 analogWrite(ledONE,  brighteness ) ; 
}

void setLEDtwo(int brighteness)
{
 analogWrite(ledTWO,  brighteness ) ; 
}

void setLEDthree(int brighteness)
{
 analogWrite(ledTHREE,  brighteness ) ; 
}

