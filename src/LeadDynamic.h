#ifndef LeadDynamic_h
#define LeadDynamic_h

#include <WiFi.h>

#define DEF_TCP_PORT 8899
class LeadDynamic
{
  private:
    const char Prefix[5] = {0x55, 0x99, 0x80, 0xa4};
    const char Postfix[5] = {0xaa, 0xaa, 0xaa, 0xaa};
    const char PostPrefix[3] = {0x02, 0x00};
    char Command[12] = "";
    int Value = 0;
    int Brightness = 0;
    int ColorTemp = 0;
    bool OnOffState = false;
    int CheckSum = 0;
    char CompleteCommand[22] = "";
    char * _host;
    uint16_t _port;

    /*
    * Calculates the Checksum needed for the Command
    */
    void CalculateChecksum(void);

    /*
    * Sends the Command over the defined Interface
    */
    void SendCommand(void);

  public:

    /*
    * Constructor
    * LeadDynamic(char * host = "192.168.0.44", uint16_t port = 8899)
    * host = IP of the controller
    * port = Port to connect to the controller
    */
    LeadDynamic(char * host, uint16_t port);     
    
    /*
    * Constructor
    * LeadDynamic(char * host = "192.168.0.44")
    * host = IP of the controller
    */    
    LeadDynamic(char * host);

    /*
    * Set the ON-OFF state of the Lamp
    * true = ON
    * false = OFF
    * It's not possible to switch on the Lamp if it's switch off with the Dimm command.
    */
    void LeadOnOff(bool OnOff);

    /*
    * Set the Brightness of the Lamp
    * 0-255 in 64 steps
    * it's possible to switch off the lamp with this command. Value 0
    */
    void setBrightness(uint Val);

    /*
    * Set's the Color temp of the lamp in 32 Steps
    * 0-255
    * 0x00 is cold
    * 0xff is warm
    */
    void setColorTemp(uint Val);      
};

#endif

