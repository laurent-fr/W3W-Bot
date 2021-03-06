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
  _buffer[_buffer_pos++]=analogRead(A0)/4;
  if (_buffer_pos>=BATTERY_BUFFER_SIZE) _buffer_pos=0;

  float volt=0;
  for(int i=0;i<BATTERY_BUFFER_SIZE;i++) volt+=_buffer[i];

  return volt/12.8;
  
}

uint8_t Battery::percent() {
  
  int percent=(voltage()-BATTERY_EMPTY)*100./(BATTERY_FULL-BATTERY_EMPTY) ;
  if (percent>100) return 100;
  if (percent<0) return 0;
  return percent;
  
}

