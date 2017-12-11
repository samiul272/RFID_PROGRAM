
#include <SPI.h>      // FOR RFID 
#include <MFRC522.h>  

byte myCards[] = {0xA3,0x1B,0x63,0x02,          //White Card
                  0x02,0x63,0x1B,0xA3};         //Blue Card 
                  
int successRead;        //if we get a succesful read of the card this variable turn to 1 and if we didn't 0

byte dummy = 0x00;

byte readCard[4];           // Stores scanned ID read from RFID Module

#define SS_PIN 4
#define RST_PIN 3
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.


void setup() {
 
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT); 
  //Initializing everingthing
  
  Serial.begin(9600);	                          // Initialize serial communications with PC
  SPI.begin();                                    // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();                             // Initialize MFRC522 Hardware
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); //Set Antenna Gain to Max- this will increase reading distance

}


void loop () {
  do{
    //Serial.println("Place your card near the module");
    rgb(0,0,1);
    delay(200);
    rgb(0,0,0);
    delay(200);
    successRead = getID();
  } 
 
  
  while (!successRead);    //wait here if we aren't getting a success read of the card
  
  if (readCard[0] == myCards[4] && readCard[1] == myCards[5] 
  && readCard[2] == myCards[6] && readCard[3] == myCards[7])              //checking for blue card
  {   
   
    Serial.println("You can enter Mr Blue");
    
   Success();
   
   for(int i = 0; i<4; i++) dummy = readCard[i];   // removing previous stored value from the readCard variable
   
   successRead = 0;
  }else if(readCard[0] == myCards[0] && readCard[1] == myCards[1] 
  && readCard[2] == myCards[2] && readCard[3] == myCards[3])            //checking for white card
  {
    Serial.println("You can enter Mr White");
    
    Success();      //calling the success function
    
    for(int i = 0; i<4; i++) dummy = readCard[i];  // removing previous stored value from the readCard variable
  }
  else {
  
    Error();      //calling the error function
  }
}

int getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return 0;
  }

  Serial.println("Scanned UID:");
  for (int i = 0; i < 4; i++) {  // 
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

void Success(){
  rgb(0,1,0);
  delay(1000);
  rgb(0,0,0);
  delay(1000);
}

void Error(){
  Serial.println("Go To Hell"); 
  for(int i= 0; i <10;i++){
    rgb(1,0,0);
    delay(100);
    rgb(0,0,0);
    delay(100);
  }
  
}


void rgb(int r , int g , int b)
{
  if(r) digitalWrite(12,LOW);
  else digitalWrite(12,HIGH);
  if(g) digitalWrite(10,LOW);
  else digitalWrite(10,HIGH);
  if(b) digitalWrite(11,LOW);
  else digitalWrite(11,HIGH);
}

