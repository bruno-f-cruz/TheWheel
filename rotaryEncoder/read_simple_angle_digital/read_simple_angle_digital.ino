/**************************************************************************/
/*!
    @file     read_simple_angle.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

	read a simple angle from AS5048B over I2C bus

    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#include "ams_as5048b.h"

//unit consts
#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10

AMS_AS5048B mysensor;

float angle = 0;
float velocity = 0;

void setup() {

	//Start serial
	Serial.begin(115200);
	while (!Serial) ; //wait until Serial ready

	//Start Wire object. Unneeded here as this is done (optionally) by the AMS_AS5048B object (see lib code - #define USE_WIREBEGIN_ENABLED)
	//Wire.begin();

	//init AMS_AS5048B object
	mysensor.begin();

	//consider the current position as zero
	//mysensor.setZeroReg();
  angle = mysensor.angleR(U_DEG, true);

}

void loop() {
  
  float newAngle = mysensor.angleR(U_DEG, true);
  Serial.print(newAngle);
  Serial.print(",");
	velocity = angle - newAngle;
  if (abs(velocity) > 180.0)
  {
    if (velocity > 0.0)
      velocity =  velocity -360;
    else
      velocity = 360 + velocity;
  }
  angle = newAngle;
  Serial.println(velocity);

	delay(8);
}
