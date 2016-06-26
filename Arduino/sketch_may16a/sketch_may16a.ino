#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7
#define SLAVE_ADDRESS 0x04

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

byte data[4];
int message_loop = 4;
void setup() {
  // put your setup code here, to run once
 pinMode(22, OUTPUT);
 digitalWrite(22, HIGH);
 pinMode(24, OUTPUT);
 digitalWrite(24, HIGH);
 pinMode(26, OUTPUT);
 digitalWrite(26, HIGH);
 pinMode(28, OUTPUT);
 digitalWrite(28, HIGH);
 pinMode(30, OUTPUT);
 digitalWrite(30, HIGH);
 pinMode(32, OUTPUT);
 digitalWrite(32, HIGH);
 pinMode(34, OUTPUT);
 digitalWrite(34, HIGH);
 pinMode(36, OUTPUT);
 digitalWrite(36, HIGH);

 //i2c Stuff
    Serial.begin(9600);         // start serial for output
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);

    Serial.println("Ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
// callback for sending data
void sendSensorData(byte sensorMessage[])
{
  Wire.write(sensorMessage,3);
}

void receiveData(int byteCount)
{
    byte index = 0;
while(Wire.available() > 0 && index <= message_loop)
{
  data[index] = Wire.read();
  index++;
}

index = 0;
while(index <= message_loop)
{
  Serial.print("Data recieved: ");
  //Serial.print("0x");
  Serial.print((char)data[index]);
  Serial.println();
  //Read if "R" for relay action is recieved
  if(index == 1 && data[index] == 0x52)
  {
    if(data[index + 2] == 0x01)
    {
      switch_relay(data[index + 1], LOW);
    }
    if(data[index + 2] == 0x00)
    {
      switch_relay(data[index + 1], HIGH); 
    }
  }
  //Send out if "S" for sensor read is recieved
  if(index == 1 && data[index] == 0x53)
  {
      sensors.requestTemperatures();
      byte sensor_value = sensors.getTempCByIndex(0);
      byte sensorMessage[] = {0x16,sensor_value,0x06};
      sendSensorData(sensorMessage);
  }
  
  index++;
}
index = 0;

}

void switch_relay(byte relay_pin, bool on_off)
{
//Relays
  switch(relay_pin){
    case 0x22:
      digitalWrite(22, on_off);
      break;
    case 0x24:
      digitalWrite(24, on_off);
      break;
    case 0x26:
      digitalWrite(26, on_off);
      break;
    case 0x28:
      digitalWrite(28, on_off);
      break;
    case 0x30:
      digitalWrite(30, on_off);
      break;
    case 0x32:
      digitalWrite(32, on_off);
      break;
    case 0x34:
      digitalWrite(34, on_off);
      break;
    case 0x36:
      digitalWrite(36, on_off);
      break;
  }
}

