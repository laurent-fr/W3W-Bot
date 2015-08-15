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

#include "Display.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_FAST|U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK);  // I2C / TWI 


static const unsigned char PROGMEM wifi_bmp[] =
{ B11100000, B00000000,
  B11111000, B00000000,
  B00011110, B00000000,
  B11000111, B00000000,
  B11110011, B00000000,
  B00111001, B10000000,
  B00011101, B10000000,
  B11001100, B11000000,
  B01100110, B11000000,
  B00100110, B11000000
};

static const unsigned char PROGMEM battery_bmp[] = 
{ B00111100,
  B11111111,
  B10000001,
  B10111101,
  B10111101,
  B10000001,
  B10111101,
  B10111101,
  B10000001,
  B10111101,
  B10111101,
  B10000001,
  B11111111 
};


void Display::begin() {
 
  u8g.setFont(u8g_font_helvR08);
  u8g.firstPage();
  do {
    u8g.drawStr( 12, 13, "Loading ...");
  } while(u8g.nextPage());

  u8g.firstPage();  
  
}


uint8_t Display::drawMain(int heading, int angle,int speed, int batt, int sonar1, int sonar2, int sonar3, char *message) {
  
  u8g.drawBitmapP(0,3,2,10,wifi_bmp);
  u8g.setPrintPos(12,13); u8g.print(message);

  u8g.drawBitmapP(100,0,1,13,battery_bmp);
  u8g.setPrintPos(111, 13); u8g.print(batt);

  u8g.drawVLine(63,16,48);

  u8g.drawStr( 0,30,"Head");
  u8g.drawStr( 0,46,"Angle");
  u8g.drawStr( 0,62,"Speed");

  u8g.setPrintPos(35,30); u8g.print(heading);
  u8g.setPrintPos(35,46); u8g.print(angle);
  u8g.setPrintPos(35,62); u8g.print(speed);

  u8g.drawTriangle(84,30,115,30,99,46);

  u8g.setPrintPos(90,26); u8g.print(sonar1);
  u8g.setPrintPos(72,50); u8g.print(sonar3);
  u8g.setPrintPos(110,50);u8g.print(sonar2);

  if (!u8g.nextPage()) { u8g.firstPage(); return 0; }

  return 1;
}

