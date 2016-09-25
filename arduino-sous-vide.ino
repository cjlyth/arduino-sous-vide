/*
 * http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library#Code.2FLibrary
 * http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 */
 
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3
#define RELAY 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures();
  float tempC = 0;
  for (uint8_t i = 0; i < sensors.getDeviceCount(); i++)
  {
    tempC = tempC + sensors.getTempCByIndex(i);
  }
  tempC = tempC / sensors.getDeviceCount();
  Serial.println(tempC);

  if (Serial.available() > 0) {
    if (1 == Serial.parseInt()) {
      digitalWrite(RELAY, HIGH);
    } else {
      digitalWrite(RELAY, LOW);
    }
  }
}

