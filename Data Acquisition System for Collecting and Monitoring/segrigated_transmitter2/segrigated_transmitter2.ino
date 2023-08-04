#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
const int MQ135_AOUT_PIN = A0;  // Analog output pin
const float ZERO_POINT_VOLTAGE = 1.4;    // Replace with your calibrated zero point voltage
const float VOLTAGE_DIVIDER_RATIO = 10.0;
RF24 radio(10, 9);
const uint64_t pipe2 = 0xF0F0F0F066;
struct sensor
{
  float w;
  float x;
  float y;
  float z;
  byte Num;
};
sensor trans2;
void setup()
{
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
  int sensorValue = analogRead(MQ135_AOUT_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  // Print the analog value to Serial monitor
  // Serial.print("Analog Value: ");
  // Serial.println(sensorValue);
  // Serial.print("Voltage Value: ");
  // Serial.println(voltage);
  voltage = voltage * VOLTAGE_DIVIDER_RATIO;
  // Calculate the gas concentrations using logarithmic approximations
  float coConcentration = pow(10, ((voltage - ZERO_POINT_VOLTAGE) / 0.2));
  float airQuality = pow(10, ((voltage - ZERO_POINT_VOLTAGE) / 0.1));
  float co2Concentration = pow(10, ((voltage - ZERO_POINT_VOLTAGE) / 0.3));
  float nh4Concentration = pow(10, ((voltage - ZERO_POINT_VOLTAGE) / 0.4));
  // Print the gas concentrations to Serial monitor
  // Serial.print("CO Concentration: ");
  Serial.print(coConcentration);
  Serial.print(",");
  // Serial.print("Air Quality: ");
  Serial.print(airQuality);
  Serial.print(",");
  // Serial.print("CO2 Concentration: ");
  Serial.print(co2Concentration);
  Serial.print(",");
  // Serial.print("NH4 Concentration: ");
  Serial.print(nh4Concentration);
  Serial.println("");

  delay(2000);
  trans2.w = coConcentration;
  trans2.x= airQuality;
  trans2.y = co2Concentration;
  trans2.z = nh4Concentration;
  radio.write(&trans2, sizeof(trans2));
  
}