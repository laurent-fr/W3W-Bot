// W3W-BOT - Wifi 3-wheeled robot
// Copyright (C) 2015 Laurent FRANCOISE - gihtub_at_diygallery_dot_com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

// i2c
#include <Wire.h>

// compass
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// gyro
#include <ITG3200.h>

// display
#include <U8glib.h>

// wifi
#include <SoftwareSerial.h>

// progmem
#include <avr/pgmspace.h>


// robot components
#include "Sonar.h"
#include "Battery.h"
#include "IMU.h"
#include "Wheel.h"
#include "Wireless.h"
#include "Display.h"

// robot objects
Sonar sonar;
Battery battery;
Wheel wheel;
IMU imu;
Wireless wireless;
Display display;


// main loop counter
uint8_t tick=0;

// sonar
uint8_t dist[3];

// battery
uint8_t batt_percent;

// gyro_heading
int16_t gyro_heading;

// displaying
uint8_t is_displaying=0;

// top message
char top_message[16];

void callback() {
  
}

void setup() {
  // put your setup code here, to run once: 

  Serial.begin(9600);
  
  Wire.begin();

  display.begin();


  Serial.print("Gyro calibration ... ");
  imu.initialize();
  Serial.println("done.");

  wireless.begin();

  wheel.useIMU(&imu);

  wheel.setHeading(0);
  wheel.setAngle(0);
  wheel.setSpeed(0);

  strcpy(top_message,"Connecting ...");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  unsigned int t0=micros();
  
  wheel.updateHeading();
  wheel.updateMotors();

  switch(tick) {


    case 8: 
      batt_percent = battery.percent();
      // no break
      
    case 0:
    case 16:
    case 32: 
     dist[0]=sonar.echo(1);
      break;

    case 1:
    case 19:
    case 35:  
     dist[1]=sonar.echo(2);
      break;


    case 6:
    case 22:
    case 38:  
     dist[2]=sonar.echo(3);
      break;

    case 23:
    case 43:
      gyro_heading = wheel.getGyroHeading();
      // no break;

    case 24:
    case 44:
      is_displaying = 1;
      break;
        
    

    default:
   
      switch (wireless.getCommand()) {
    
          case 'A': wheel.setAngle(wireless.getParam()); break;
          case 'S': wheel.setSpeed(wireless.getParam());  break;
          case 'H': wheel.setHeading(wireless.getParam()); break;
          case 'E': wireless.send(dist[wireless.getParam()-1]); break;
          case 'B': wireless.send(batt_percent); break;
          case 'm': strcpy(top_message,wireless.getText()); break;
         
      }

  }

  // display
  if (is_displaying) {
    is_displaying = display.drawMain(gyro_heading, wheel.getAngle(), wheel.getSpeed() , batt_percent, dist[0], dist[1], dist[2], top_message );
  }
  

  tick++;
  if (tick>47) tick=0;

  unsigned int t=micros()-t0;
  if (t<20000) {
    delayMicroseconds(20000-t);
  }
  
}
