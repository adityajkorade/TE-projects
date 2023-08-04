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
void setup()
{
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
  trans2.x = analogRead(A0);
  trans2.y = analogRead(A1);
  radio.write(&trans2, sizeof(trans2));
}