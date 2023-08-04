#include <SPI.h>


#include <RF24.h>
RF24 radio(10, 9);
const uint64_t pipe1 = 0xF0F0F0F0AA;
struct sensor
{
  float x;
  float y;
  byte Num;
};
sensor trans;
void setup()
{
  Wire.begin();
  radio.begin();
  radio.openWritingPipe(pipe1);
  radio.setPALevel(RF24_PA_LOW  );
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  trans.Num = 1;
}
void loop()
{
  delay(2000);
  trans.x = analogRead(A0);
  // trans.y = random(14,16);
  radio.write(&trans, sizeof(trans));
  Serial.print(trans.x);
}