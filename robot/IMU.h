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

#ifndef imu_h
#define imu_h

#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include <ITG3200.h>

#include "config.h"


#define DEG_TO_RAD 0.01745329252
#define RAD_TO_DEG 57.29577951308

class IMU {

  private:
    ITG3200 _gyro;
    Adafruit_HMC5883_Unified _compass;

    float _compass_x_offset=11.06;
    float _compass_y_offset=16.13;
    float _compass_x_scale=35.0;
    float _compass_y_scale=28.45;
      

  public:

     IMU();

     void initialize();
 
     float getGyroSpeedZ();
     float getCompassHeading();

    
};

#endif
