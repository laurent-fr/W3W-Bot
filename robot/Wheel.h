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

#ifndef wheel_h
#define wheel_h

#include <Arduino.h>

#include "IMU.h"

class Wheel {

  private:

    IMU *_imu;

    float _heading,_old_heading;
    float _angle,_old_angle;
    float _speed,_old_speed;

    float _speed1,_speed2,_speed3;

    float _compass_heading,_gyro_heading;

    void setMotorSpeed(uint8_t motor,int16_t speed);
    float normalizeAngle(float angle);
    
    void calcMotors();

    int16_t fitSpeed(float speed);

  public:

    Wheel();

    void useIMU(IMU *imu);

    void setHeading(float heading);
    void setAngle(float angle);
    void setSpeed(float speed);

    float getHeading();
    float getGyroHeading();
    
    float getAngle();
    float getSpeed();

    void updateHeading(uint16_t delta_t);
    void updateMotors();
};

#endif
