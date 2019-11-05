#include <MFRC522.h>


#include "ESP8266WiFi.h"
#include <SPI.h>
#include <Servo.h>
//#include "pitches.h"

//Define Component to Arduino Pins
#define SS_PIN 2
#define RST_PIN 0


#define SERVO_PIN 16

#define Red_LED 5
#define Green_LED 4

#define Buzzer 15

const char* MY_SSID = "Asfak";
const char* MY_PWD = "asfak123";

Servo DoorLock;
MFRC522 mfrc522(SS_PIN, RST_PIN );

//Unique ID of RFID Tag, which you want to give access. 
//int My_RFID_Tag[5] = {0x58,0x76,0x17,0x10,0x29};
int My_RFID_Tag[5] = {0x8C,0x49,0xAB,0xA4,0x0};

//variable to hold your Access_card
boolean My_Card = false;  
   
// notes in the melody, taken from:
//File -> Examples -> Digital -> ToneMelody
//int melody[] = {
//  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
//};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
//int noteDurations[] = {
//  4, 8, 8, 4, 4, 4, 4, 4
//};

void setup() 
{
  pinMode(Red_LED,OUTPUT);
  pinMode(Green_LED,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");
  while (WiFi.status() != WL_CONNECTED){
  delay(10000);
  Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");

  
  //Servo Connnected to pin Digital Pin 5
  DoorLock.attach(SERVO_PIN);

  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() 
{

  My_Card = true; 
  DoorLock.write(0); //Servo at 0 Position, Door is Closed.
  
  //Check if any RFID Tags Detected or not?
  if( mfrc522.PICC_IsNewCardPresent() )
  {
      //if RFID Tag is detected, check for the Unique ID,
      //and print it on the Serial Window
      if( mfrc522.PICC_ReadCardSerial() )
      {   
          //Serial.clear();      
          Serial.print("UNIQUE ID is:- ");
          delay(500);          
         
  
      //Unique id is 5 Digit Number.
          //Printing in HEX for better Understanding
          for( int i = 0; i < 5; i++ )
          {
              Serial.print(mfrc522.uid.uidByte[i], HEX);
              Serial.print(" ");              
              Serial.print(mfrc522.uid.uidByte[i],HEX);
              Serial.print(" ");                            
          }  
          delay(500);
          
      //Compare this RFID Tag Unique ID with your My_RFID_Tag's Unique ID
          for(int i = 0; i < 5; i++)
          {   
              //if any one Unique ID Digit is not matching,
              //then make My_Card = false and come out from loop
              //No need to check all the digit!
              if( My_RFID_Tag[i] != mfrc522.uid.uidByte[i] )
              {
                My_Card = false;
                break;                
              }           
          }
          Serial.println(); 
          delay(1000); 

          //If RFID Tag is My_Card then give access to enter into room
          //else dont open the door.
          if(My_Card)
          {
            Serial.println("\nWelcome To Your Room, Robodia!");
            //Serial.clear();
            Serial.print("Welcome to Your");
            //lcd.setCursor(0,1);
            Serial.print("Room, Robodia!");

            //Turn on the Green LED as an indication of permission is given 
            //to access the room.
            digitalWrite(Green_LED,HIGH);
            
            //Buzzer Config, taken from:
            //File -> Examples -> Digital -> ToneMelody
            // iterate over the notes of the melody:
            int i = 0;
            while(i < 2)
            {
              for (int thisNote = 0; thisNote < 12; thisNote++) 
              {          
                //to calculate the note duration, take one second
                // divided by the note type.
                //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
               // int noteDuration = 1000 / noteDurations[thisNote];
                //tone(8, melody[thisNote], noteDuration);                        
                // to distinguish the notes, set a minimum time between them.
                // the note's duration + 30% seems to work well:
               // int pauseBetweenNotes = noteDuration * 1.30;
               // delay(pauseBetweenNotes);              
                // stop the tone playing:
               // noTone(8);
              }
              i =  i + 1;
              delay(500);              
            }
            delay(1000);            

            //Now, Open the Door with the help of Servo Motor
            DoorLock.write(180);            
            delay(200);
            ////Serial.clear();                                    
            Serial.print("Door is Open");
            //lcd.setCursor(0,1);
            Serial.print("Now!");
            delay(2000);
            ////////Serial.clear();

            //Give 10 Sec delay to enter into room
            //After that door will again closed!
            for(int i = 10; i > 0; i--)
            {
              Serial.print("Door will close");
              //lcd.setCursor(0,1);
              Serial.print("in ");
              Serial.print(i);
              Serial.print(" Sec.HurryUp!");
              delay(1000);
              //Serial.clear();
            }

            //Now,Door is closed and Green LED is Turned-Off.
            DoorLock.write(0);
            digitalWrite(Green_LED,LOW);
            delay(200);
            ////Serial.clear();
           Serial.print("Door is Close");
           // lcd.setCursor(0,1);
           Serial.print("Now!");
            delay(2000);                            
          }
          
          // If RFID Tag is not My_Card then
          // Do not open the Door and 
          //Turn-On Red LED and Buzzer as an indication of Warning:
          //Somebody else is trying to enter into your room. 
          else
          {
            Serial.println("\nGet Out of Here !");
            ////Serial.clear();
           Serial.print("Card isNOT FOUND!");
          //Serial.setCursor(0,1);
            Serial.print("Get Out of Here!");

            for(int i = 0; i < 7; i++)
            {
              digitalWrite(Buzzer, HIGH);
              digitalWrite(Red_LED,HIGH);
              delay(500);
              digitalWrite(Buzzer, LOW);
              digitalWrite(Red_LED,LOW);
              delay(500);              
            }
            delay(1000);            
          }                 
      }      
   }
  //Put RFID Reader into Halt, untill it not detects any RFID Tag.
 mfrc522.PICC_HaltA();
}
