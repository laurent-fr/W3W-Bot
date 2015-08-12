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

#include "Sonar.h"

const uint8_t pins[] = { PIN_SONAR_1, PIN_SONAR_2, PIN_SONAR_3 };

Sonar::Sonar() {

  for (int i=0;i<SONAR_COUNT;i ++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i],LOW);
  }
}


float Sonar::echo(uint8_t num) {

  if ((num==0)||(num>SONAR_COUNT)) return 0;

  uint8_t pin=pins[num-1];
 
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  uint16_t ping = pulseIn(pin, HIGH, SONAR_MAX_TIME );
  return (float)ping / 58.;

}

