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
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// wifi
#include <SoftwareSerial.h>


// robot components
#include "Sonar.h"
#include "Battery.h"
#include "IMU.h"
#include "Wheel.h"
#include "Wireless.h"
//#include "Display.h"

// robot objects
Sonar sonar;
Battery battery;
Wheel wheel;
IMU imu;
Wireless wireless;
// Display display;

void setup() {
  // put your setup code here, to run once: 

  Serial.begin(9600);
  
  Wire.begin();


  Serial.print("Gyro calibration ... ");
  imu.initialize();
  Serial.println("done.");

  wireless.begin();

  wheel.useIMU(&imu);

  wheel.setHeading(0);
  wheel.setAngle(0);
  wheel.setSpeed(0);

}

void loop() {
  // put your main code here, to run repeatedly:

  wheel.updateHeading();
  wheel.updateMotors();

  switch (wireless.getCommand()) {

      case 'A': wheel.setAngle(wireless.getParam()); break;
      case 'S': wheel.setSpeed(wireless.getParam());  break;
      case 'H': wheel.setHeading(wireless.getParam()); break;
      case 'E': wireless.send((int)sonar.echo(wireless.getParam())); break;
      case 'B': wireless.send((int)battery.percent()); break;
     
  }
  

  delay(20);

}
