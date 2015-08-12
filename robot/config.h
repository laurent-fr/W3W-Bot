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

#ifndef config_h
#define config_h

#include <Arduino.h>

// sonar
#define SONAR_COUNT 3

#define PIN_SONAR_1 8
#define PIN_SONAR_2 9
#define PIN_SONAR_3 10

#define SONAR_MAX_TIME 11600 // 200cm*58 => 11600 us

// battery
#define PIN_BATTERY A0

#define BATTERY_FULL 8.4
#define BATTERY_EMPTY 6.4

// motors
#define MOTOR_COUNT 3

#define PIN_MOTOR1_DIR 2 
#define PIN_MOTOR1_PWM 3
#define PIN_MOTOR2_DIR 4
#define PIN_MOTOR2_PWM 5
#define PIN_MOTOR3_DIR 7
#define PIN_MOTOR3_PWM 6

// IMU
// declination angle, see http://www.magnetic-declination.com/
#define COMPASS_DECLINATION_ANGLE 0.2

// wifi
#define PIN_WIFI_RX 15
#define PIN_WIFI_TX 16

#endif
