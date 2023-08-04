#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(10, 9);
const uint64_t pipe2 = 0xF0F0F0F066;
struct sensor
{
  float x;
  float y;
  byte Num;
};
sensor trans2;

int ldr = A0;
void setup()
{
  pinMode(ldr, INPUT); //initialize ldr sensor as INPUT
  Serial.begin(9600); 
  radio.begin();
  radio.openWritingPipe(pipe2);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  //------------------------------
  trans2.Num = 2;
}
void loop()
{
  delay(2000);
  trans2.x = 11;
  Serial.println(trans2.x);
  // trans2.y = ;
  radio.write(&trans2, sizeof(trans2));
  Serial.print(trans2.x);
}