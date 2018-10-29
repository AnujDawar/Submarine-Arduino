#include "SubmarineUtility.h"

void setUpModules()
{
  debug(BLUETOOTH_READY);
  speedServo.attach(SPEED_SERVO_PIN);
  debug(BRUSHLESS_MOTOR_READY);
  directionServo.attach(DIRECTION_SERVO_PIN);
  debug(SERVO_MOTOR_READY);
  directionServo.write(90);
  delay(100);
  debug(BRUSHLESS_MOTOR_CALIBERATING);
  speedServo.writeMicroseconds(BRUSHLESS_MOTOR_UPPER_LIMIT);
  delay(3000);
  speedServo.writeMicroseconds(BRUSHLESS_MOTOR_LOWER_LIMIT);
  debug(BRUSHLESS_MOTOR_CALIBERATED);
}
