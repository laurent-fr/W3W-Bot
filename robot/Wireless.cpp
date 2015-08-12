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

#include <SoftwareSerial.h>

#include "Wireless.h"

SoftwareSerial wifiSerial(PIN_WIFI_RX,PIN_WIFI_TX);


Wireless::Wireless() {

  _mode = WIRELESS_MODE_CMD;
  _cmd=0;
  _param=0;
  _sign=1;
}


void Wireless::begin() {
  wifiSerial.begin(9600);
}


char Wireless::getCommand() {

  
 if (!wifiSerial.available()) return 0;

  char c = wifiSerial.read();

  Serial.print("RX: ");
  Serial.write(c);
  Serial.println("");

  if (c=='\r') return 0;

  if (c=='\n') { 
    _mode=WIRELESS_MODE_CMD; 
    return _cmd; 
  }

  if (_mode == WIRELESS_MODE_CMD ) {
    _cmd = c;
    _param = 0;
    _sign=1;
    _mode = WIRELESS_MODE_PARAM;
    return 0;
  }

  if (_mode == WIRELESS_MODE_PARAM) {

    if (c=='-') {
      _sign=-1;
      return 0;
    }
    
    if ((c<'0')||(c>'9')) {
      wifiSerial.println("Err");
      _mode=WIRELESS_MODE_CMD;
      return 0;
    } 

    _param = (int16_t)(c-'0')+(_param*10);
  }
    
}

int16_t Wireless::getParam() {
  return _param*_sign;
}

void Wireless::send(int value) {
  wifiSerial.println(value);  
}


