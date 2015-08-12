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

#include "Battery.h"

Battery::Battery() {
  analogReference(DEFAULT);
}

float Battery::voltage() {
  return (float)analogRead(A0)/102.4;
}

uint8_t Battery::percent() {
  
  int percent=(((float)analogRead(PIN_BATTERY)/102.4)-BATTERY_EMPTY)*100./(BATTERY_FULL-BATTERY_EMPTY) ;
  if (percent>100) return 100;
  if (percent<0) return 0;
  return percent;
  
}

