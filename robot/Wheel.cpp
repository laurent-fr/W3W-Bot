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

#include <avr/pgmspace.h>

#include "Wheel.h"

const uint8_t pwms[]  = { PIN_MOTOR1_PWM, PIN_MOTOR2_PWM, PIN_MOTOR3_PWM };
const uint8_t dirs[] = { PIN_MOTOR1_DIR, PIN_MOTOR2_DIR, PIN_MOTOR3_DIR };

Wheel::Wheel() {
  
  for(int i=0;i<MOTOR_COUNT;i ++) {
    pinMode(dirs[i],OUTPUT);
    pinMode(pwms[i],OUTPUT);
    digitalWrite(dirs[i],0);
    digitalWrite(pwms[i],0);
  }
  
}

void Wheel::useIMU(IMU *imu) {
  _imu=imu;

   _gyro_heading = normalizeAngle( _imu->getCompassHeading() );
  
}

void Wheel::setHeading(float heading) {
  _heading=heading;
   if (_heading!=_old_heading) {
    _old_heading=_heading;
    calcMotors();
  }
}

float Wheel::getHeading() {
  return _heading;
}

float Wheel::getGyroHeading() {
  return _gyro_heading;
}

void Wheel::setAngle(float angle) {
  _angle=angle;
  if (_angle!=_old_angle) {
    _old_angle=_angle;
    calcMotors();
  }
}

float Wheel::getAngle() {
  return _angle;
}

void Wheel::setSpeed(float speed) {
  _speed=speed;
  if (_speed!=_old_speed) {
    _old_speed=_speed;
    calcMotors();
  }
}

float Wheel::getSpeed() {
  return _speed;
}

void Wheel::updateHeading(uint16_t delta_t) {

  _compass_heading = normalizeAngle( _imu->getCompassHeading() );
  
  _gyro_heading += _imu->getGyroSpeedZ()*delta_t/1000000;
  _gyro_heading = normalizeAngle(_gyro_heading);

  _gyro_heading=0.99*_gyro_heading+0.01*_compass_heading;
   
}


void Wheel::setMotorSpeed(uint8_t motor,int16_t speed) {

  if ((motor>MOTOR_COUNT)||(motor==0)) return;


  uint8_t m=motor-1;

  if (speed>255) speed=255;
  if (speed<-255) speed=-255;

  if (speed>=0) {
    digitalWrite(dirs[m],0);
    analogWrite(pwms[m],speed);
  } else {
    digitalWrite(dirs[m],1);
    analogWrite(pwms[m],255+speed);
  }

}


float Wheel::normalizeAngle(float angle) {
  while (angle>180) angle-=360;
  while (angle<-180) angle+=360;
  return angle;
}
    
void Wheel::calcMotors() {

  float rad_angle = (_angle)*DEG_TO_RAD;

  float cos_angle = cos(rad_angle);
  float sin_angle = sin(rad_angle);

  _speed1 = _speed*cos_angle;
  _speed2 = _speed*(-0.5*cos_angle+0.866*sin_angle);
  _speed3 = _speed*(-0.5*cos_angle-0.866*sin_angle);

}

int16_t Wheel::fitSpeed(float speed) {
   if (speed==0) return 0;

  int sign=1;
  if (speed<0) { speed=-speed; sign=-1;}

  float cmd= pow( ((speed/3.4034)+9.9022)/5.3606 ,2.71828) + 57.5886;

  if (cmd<0) cmd=0;
  if (cmd>255) cmd=255;
  return cmd*sign;
}

void Wheel::updateMotors() {

  float error = normalizeAngle(_gyro_heading-_heading)*0.1*65;
  

  setMotorSpeed(1,fitSpeed(_speed1+error));
  setMotorSpeed(2,fitSpeed(_speed2+error));
  setMotorSpeed(3,fitSpeed(_speed3+error));
  
}

