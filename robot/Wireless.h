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

#ifndef wireless_h
#define wireless_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "config.h"

#define WIRELESS_MODE_CMD 1
#define WIRELESS_MODE_PARAM 2

class Wireless {

  private:
    char _cmd;
    int16_t _param;
    int8_t _sign;
    uint8_t _mode;
    
  public:

    Wireless();
    void begin();
    char getCommand();
    int16_t getParam();
    void send(int);

  
};

#endif

