#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define SIGNAL_TIMEOUT 500  // This is signal timeout in milli seconds. We will reset the data if no signal

const uint64_t pipeIn = 0xF9E8F0F0E1LL;
RF24 radio(8, 9); 
unsigned long lastRecvTime = 0;

struct PacketData
{
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;  
  byte switch1Value;
  byte switch2Value;
  byte switch3Value; 
};
PacketData receiverData;

Servo esc1;
Servo esc2;     //Pin D3
Servo servo3;     //Pin D4
Servo servo4;     //Pin D5



int   led1 = A0;
int   led2 = A1;
int   led3 = A2;
int   led4 = A3;

//Assign default input received values
void setInputDefaultValues()
{
  // The middle position for joystick. (254/2=127)
  receiverData.lxAxisValue = 127;
  receiverData.lyAxisValue = 127;
  receiverData.rxAxisValue = 127;
  receiverData.ryAxisValue = 127;  
  receiverData.switch1Value = LOW;
  receiverData.switch2Value = LOW;
  receiverData.switch3Value = LOW;
}

void mapAndWriteValues()
{
  esc1.writeMicroseconds(map(receiverData.lxAxisValue, 0, 254, 1000, 2000));
  esc2.writeMicroseconds(map(receiverData.rxAxisValue, 0, 254, 1000, 2000));
  servo3.write(map(receiverData.lyAxisValue, 0, 254, 0, 180));
  servo4.write(map(receiverData.ryAxisValue, 0, 254, 0, 90));
  
  digitalWrite(led1, receiverData.switch1Value);
  digitalWrite(led2, receiverData.switch2Value);
  digitalWrite(led3, receiverData.switch3Value);
}

void setup()
{
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening(); //start the radio receiver 

  esc1.attach(7);
  esc2.attach(6);
  servo3.attach(5);
  servo4.attach(4);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  setInputDefaultValues();
  mapAndWriteValues();
}

void loop()
{
  // Check if RF is connected and packet is available 
  if(radio.isChipConnected() && radio.available())
  {
    radio.read(&receiverData, sizeof(PacketData)); 
    lastRecvTime = millis(); 
  }
  else
  {
    //Check Signal lost.
    unsigned long now = millis();
    if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
    {
      setInputDefaultValues();
    }
  }
  mapAndWriteValues();         
}