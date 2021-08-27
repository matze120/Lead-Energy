# Lead-Energy
Lead Energy (Lead-Dynamic) was a German Startup wich made some great WiFi controllable lamps.  
unfortunately they are not loger with us.  
But, the lamps were only controlled from the local Network and not thru a server on the other side of the planet.  
So it is possible to control the Lamps with any other Device. Like an ESP32 or an ESP8266.  

This is an Arduino Library which makes this possible.  
You can build your own light switch or SMART Home controller of some sort. 

This library supports only the "White" lamps at the moment. 
This comes down to the reason that I don't have a RGB Panel to test the other functions.  
Feel free to add support for the RGB version. You're welcome to contribute.

Want to see the whole project documetation?  
Visit my Hompage [Fornacon.net](http://fornacon.net/index.php/projekte/5-lead-energy-steuerung)

## Installing the Library
1. Download the Repository as a ZIP 
2. Go to the Arduino Library Manager and click "Add ZIP Library"
3. Then select the Downloaded ZIP File and click open
4. Ready 

## Using the Library
Just follow the Provided Example.  
This creates an Object from the "Lead-Dynamic" Class and provides the IP of the lamp.  

Then you have the class methods to control the lamps on-off State, the color temperature and the brightness.

Of course you can create more than one object from the class.  
For example you have one lamp in your kitchen, another one in the livingroom and so on.

## Hardware
I've tested the example on a WEMOS LOLIN32 board. This Board contains an ESP32.  
I used it because it has an integrated charger for a Li-Po Battery.  
With this you can create a rechargeable Light switch for those lamps. 
