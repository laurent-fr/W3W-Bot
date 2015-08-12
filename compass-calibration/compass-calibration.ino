

// Reference the I2C Library
#include <Wire.h>

// Reference the HMC5883L Compass Library
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);


#define DIR1 2
#define PWM1 3
#define DIR2 4
#define PWM2 5
#define DIR3 7
#define PWM3 6


float compass_x_offset = 0;
float compass_y_offset = 0;
float compass_x_scale = 0;
float compass_y_scale = 0;


void setSpeed(int dir_pin,int pwm_pin,int speed) {

  if (speed>255) speed=255;
  if (speed<-255) speed=-255;

  if (speed>=0) {
    digitalWrite(dir_pin,0);
    analogWrite(pwm_pin,speed);
  } else {
    digitalWrite(dir_pin,1);
    analogWrite(pwm_pin,255+speed);
  }

  
}

void compass_calibration() {

  int nb = 0;
  float x_total = 0,y_total=0;
  float x_min=0,y_min=0,x_max=0,y_max=0;
  sensors_event_t event;

  float avg_x=0, avg_y=0;
  float error = 0.01;

  Serial.println("");
  Serial.println("");
  Serial.println("Compass calibration :");
  Serial.println("");

  while(1) {

 
    mag.getEvent(&event);

    float mx = event.magnetic.x;
    float my = event.magnetic.y;

    if (nb==0) {
        x_min=mx;x_max=mx;
        y_min=my;y_max=my;
    }

    nb++;
    x_total+=mx;
    y_total+=my;
    if (mx<x_min) x_min=mx;
    if (mx>x_max) x_max=mx;
    if (my<y_min) y_min=my;
    if (my>y_min) y_max=my;

    if (nb>1000) {
        float new_avg_x=x_total/nb;
        float new_avg_y=y_total/nb;

        if ( (abs(new_avg_x-avg_x)<error) && (abs(new_avg_y-avg_y)<error) ) break;
     
        avg_x=x_total/nb;
        avg_y=y_total/nb;
      
    }
    
    delay(20);

  }

  compass_x_offset = -avg_x;
  compass_y_offset = -avg_y;
  compass_x_scale = x_max-x_min;
  compass_y_scale = y_max-y_min;

  Serial.print("#define COMPASS_X_OFFSET ");
  Serial.println(compass_x_offset);
  Serial.print("#define COMPASS_Y_OFFSET ");
  Serial.println(compass_y_offset);
  Serial.print("#define COMPASS_X_SCALE ");
  Serial.println(compass_x_scale);
  Serial.print("#define COMPASS_Y_SCALE ");
  Serial.println(compass_y_scale);

  Serial.println("");
  Serial.println("Finished !");
  
}

void setup() {
  
  // motors
  pinMode(DIR1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  digitalWrite(DIR1,0);
  digitalWrite(PWM1,0);

  pinMode(DIR2,OUTPUT);
  pinMode(PWM2,OUTPUT);
  digitalWrite(DIR2,0);
  digitalWrite(PWM2,0);

  pinMode(DIR3,OUTPUT);
  pinMode(PWM3,OUTPUT);
  digitalWrite(DIR3,0);
  digitalWrite(PWM3,0);

  // i2c
  Wire.begin(); // Start the I2C interface.

  // serial port
  Serial.begin(115200);

  // compass
  mag.begin();  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  setSpeed(DIR1,PWM1,150);
  setSpeed(DIR2,PWM2,150);
  setSpeed(DIR3,PWM3,150);
  compass_calibration();

  setSpeed(DIR1,PWM1,0);
  setSpeed(DIR2,PWM2,0);
  setSpeed(DIR3,PWM3,0);

  while(1) delay(1000);
  
}
