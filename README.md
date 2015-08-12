W3W-Bot

A 3-wheeled robot with Wifi interface with a Arduino and a ESP8266. The hardware is described here : http://www.thingiverse.com/thing:965862

To build the arduino firmware, you will need a few libraries :

 * https://github.com/irvined1982/itg3200
 * https://github.com/adafruit/Adafruit-GFX-Library
 * https://github.com/adafruit/Adafruit_SSD1306
 * https://github.com/adafruit/Adafruit_HMC5883_Unified
 * https://github.com/adafruit/Adafruit_Sensor
 
The steps for programming the robot are :

 * first program the ESP8266 with esp8266-telnet (serial to wifi/telnet), don't forget to update your WIFI SSID and password
 * program the arduino with compass-calibration.ino and run with the serial monitor, you will obtain 4 lines to update in config.h of the main program
 * then program the main firmware on the arduino ('robot' folder')

 When powered on, the robot should turn to magnetic north after a few seconds, and stay in this position (try to rotate the robot by hand).

Then you should be able to telnet the robot (no easy way to find the IP yet , use nmap ...) , for now there are a few simple commands (all the angles are in degrees) :

  * H< angle> : change the main heading of the robot
  * A< angle> : set the angle when the robot is moving
  * S< speed> : set the speed of the robot (0 to about 60)
  * B : get the battery status (0% to 100%)
  * E<1 to 3> : get the the distance to the next obstacle for the given sonar (in cm)
