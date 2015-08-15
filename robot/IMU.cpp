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

#include "IMU.h"

IMU::IMU() { }

 
void IMU::initialize() {  
  // gyro
 _gyro = ITG3200();
  _gyro.init(ITG3200_ADDR_AD0_LOW);
  _gyro.zeroCalibrate(2500, 2);

  // compass
  _compass = Adafruit_HMC5883_Unified(1);
  _compass.begin();
}

float IMU::getGyroSpeedZ() {
  float x,y,z;
  _gyro.readGyro(&x,&y,&z);
  return z;
}
     
float IMU::getCompassHeading() {

  sensors_event_t event; 
  _compass.getEvent(&event);

  float mx = (event.magnetic.x+_compass_x_offset)/_compass_x_scale;
  float my = (event.magnetic.y+_compass_y_offset)/_compass_y_scale;

  float heading = atan2(mx,my);
  
  heading += COMPASS_DECLINATION_ANGLE;
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;
  float headingDegrees = heading * RAD_TO_DEG;

  return headingDegrees;
}

