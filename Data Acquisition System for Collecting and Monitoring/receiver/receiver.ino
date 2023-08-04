#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
RF24 radio(10, 9);
float s1;
float s2;
float s3;
float s4;
const uint64_t pipe1 = 0xF0F0F0F0AA;
const uint64_t pipe2 = 0xF0F0F0F066;
struct sensor
{
  float x;
  float y;
  byte  Num;
};
sensor sensorData;
void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe1);
  radio.openReadingPipe(2, pipe2);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  Serial.println("arduino1,arduino1,arduino2, arduino2");
}
void loop()
{
  if(radio.available())
  {
    radio.read(&sensorData, sizeof(sensorData));
    disp_sensor_data();
  }
  else
  {
    Serial.println("not received");
  }
  delay(2000);
}
void disp_sensor_data()
{
  if(sensorData.Num == 1)
  {
    s1=sensorData.x;
    s2=sensorData.y;
  }
  if(sensorData.Num == 2)
  {
    s3=sensorData.x;
    s4=sensorData.y;
    
  }
  Serial.print(s1);
  Serial.print(" , ");
  // Serial.print(s2);
  // Serial.print(" , ");
  Serial.print(s3);
  // Serial.print(" , ");
  // Serial.print(s4);
 Serial.println("");
}