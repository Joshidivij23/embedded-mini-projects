#include <SoftwareSerial.h>
SoftwareSerial mysim(7,8); // connect gsm modem on this pin
String smstext;


int led = 4;  //led connected to pin 4

const int pirsensor = A1;  
int threshold = 250;      

void setup() {
      Serial.begin(9600);
      mysim.begin(9600);
      Serial.println("System is Initializing..");
           
      pinMode (led,OUTPUT);     
      pinMode (pirsensor,INPUT); 
      
      digitalWrite(led, LOW); 
      delay(5000); 
}

void loop() {
      int ppm = analogRead(pirsensor); 
      Serial.println(ppm);                       

      if (ppm > threshold)            
      {
      smstext =  "\nmovement Detected..!";
      sendSMS(smstext); 
      Serial.println(smstext);    
      
      digitalWrite(led,HIGH);    
      delay(5000);
      mysim.println("ATD+YYxxxxxxxxxx;"); 
      updateSerial();
      Serial.println("Calling  ");
      delay(50000); 
      mysim.println("ATH"); 
      updateSerial();
      Serial.println("Hangup Call");

    }
     else
    {
      digitalWrite(led,LOW);   
      
      Serial.println("No movement detected");
    }  
  delay (500);
}

void sendSMS(String message)
{
  mysim.print("AT+CMGF=1\r");                     
  updateSerial();
  delay(1000);
  
  mysim.println("AT+CMGS=\"+YYxxxxxxxxxx\"");  
  updateSerial();
  delay(1000);
  
  mysim.println(message);                        
  updateSerial();
  delay(1000);
  
  mysim.println((char)26);                        
  updateSerial();
  delay(1000); 
  
  mysim.println();
  delay(100);                                     
 
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mysim.write(Serial.read());
  }
  while(mysim.available()) 
  {
    Serial.write(mysim.read());
  }
}
