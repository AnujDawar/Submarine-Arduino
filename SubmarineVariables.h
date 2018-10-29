#include <Servo.h>
#include "SubmarinePinConfig.h"

Servo speedServo, directionServo;

const int ARDUINO_SERIAL_BAUD_RATE = 9600;
const int BLUETOOTH_SERIAL_BAUD_RATE = 38400;

const int BRUSHLESS_MOTOR_LOWER_LIMIT = 1000;
const int BRUSHLESS_MOTOR_UPPER_LIMIT = 2000;

const int BRUSHLESS_MOTOR_MIN_TO_WORK = 1060;

const int MIN_VAL_TO_ENTERTAIN_FROM_REMOTE = 1;
const int MAX_VAL_TO_ENTERTAIN_FROM_REMOTE = 250;

String directionValue = "";
String speedValue = "";
String depthValue = "";
int brushlessMotorValue = 0;

int index1;
int index2;

int mySpeed;
int myDirection;
int myDepth;
