#include "LeadDynamic.h"

LeadDynamic::LeadDynamic(char * host, uint16_t port)
{
  _host = host;
  _port = port;
}

LeadDynamic::LeadDynamic(char * host)
{
  _host = host;
  _port = DEF_TCP_PORT;
}

void LeadDynamic::LeadOnOff(bool OnOff)
{
  if(OnOff)
  {
    OnOffState = true;
    Command[0] = 0x02;
    Command[1] = 0x12;
    Value = 0xAB;
  }else
  {
    OnOffState = false;
    Command[0] = 0x02;
    Command[1] = 0x12;
    Value = 0xA9;
  }  
  SendCommand();
}

void LeadDynamic::setBrightness(uint Val)
{
  Command[0] = 0x08;
  Command[1] = 0x33;
  Brightness = Val;
  Value = (Val / 4);

  SendCommand();
}

void LeadDynamic::setColorTemp(uint Val)
{
  Command[0] = 0x08;
  Command[1] = 0x36;
  ColorTemp = Val;
  Value = (Val / 8);

  SendCommand();
}

void LeadDynamic::CalculateChecksum(void)
{
  int WW = PostPrefix[0];
  int ww = PostPrefix[1];

  int XX = Command[0];
  int xx = Command[1];

  int YY = Value;
  
  CheckSum = WW + ww + XX + xx + YY & 0xff;
}

void LeadDynamic::SendCommand(void)
{
  CalculateChecksum();

  //const uint16_t port = 8899;
  //const char * host = "192.168.0.44";  //Change to whatever your LED Controller IP is
  WiFiClient client;

  if (client.connect(_host, _port)) //Try to connect to TCP Server
  {
    Serial.println("Connected...");
    char command[14];

    for(int i = 0; i < 4; i++)  //0..3
    {
      command[i] = Prefix[i];
    }

    for(int i = 0; i < 2; i++)  //4..5
    {
      command[4 + i] = PostPrefix[i];
    }

    for(int i = 0; i < 2; i++)  //6..7
    {
      command[6 + i] = Command[i];
    }

      command[8] = Value;

      command[9] = CheckSum;

    for(int i = 0; i < 4; i++)
    {
      command[10 + i] = Postfix[i];
    }    

    //client.write((uint8_t *)command, sizeof(command));
    client.write(command, 12);
    delay(2000);
    client.stop();
    Serial.println("disconnected ... ");    
  }
}