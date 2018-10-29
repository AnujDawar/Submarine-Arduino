#include "SubmarineVariables.h"
#include "SubmarineStringConstants.h"

int hexToDec(String hexString)
{
  int decValue = 0;
  int nextInt;

  for (int i = 0; i < hexString.length(); i++)
  {
    nextInt = int(hexString.charAt(i));

    if (nextInt >= 48 && nextInt <= 57)
      nextInt = nextInt - 48;

    else if (nextInt >= 65 && nextInt <= 70)
      nextInt = nextInt - 55;

    else if (nextInt >= 97 && nextInt <= 102)
      nextInt = nextInt - 87;

    nextInt = constrain(nextInt, 0, 15);

    decValue = (decValue * 16) + nextInt;
  }

  return decValue;
}

void debug(String debugMsg)
{
  Serial.println(debugMsg);
}

void debug(String message, String value)
{
  debug(message + value);
}

void debug(String message, int value)
{
  debug(message + (String)value);
}

void debug(String msg1, int val1, String msg2, int val2, String msg3, int val3)
{
  Serial.println(msg1 + (String)val1 + "\t" + msg2 + (String)val2 + "\t" + msg3 + val3);
}

void decryptValues(String fromNetwork)
{
  index1 = fromNetwork.indexOf(DATA_SEPARATOR);
  speedValue = fromNetwork.substring(0, index1);
  index2 = fromNetwork.indexOf(DATA_SEPARATOR, index1 + 1);
  directionValue = fromNetwork.substring(index1 + 1, index2);
  depthValue = fromNetwork.substring(index2 + 1, fromNetwork.indexOf(DATA_TERMINATOR));

  mySpeed = hexToDec(speedValue);
  myDirection = hexToDec(directionValue);
  myDepth = hexToDec(depthValue);
}

void writeDataToMotors()
{
  mySpeed = constrain(mySpeed, 0, 250);
  myDirection = constrain(myDirection, 20, 160);
  myDepth = constrain(myDepth, 20, 160);
  
  debug(SPEED, mySpeed, DIRECTION, myDirection, DEPTH, myDepth);

  if (mySpeed == 0)
  {
    debug(WRITE_DATA_TO_BRUSHLESS, BRUSHLESS_MOTOR_LOWER_LIMIT);
    directionServo.write(myDirection);
    speedServo.writeMicroseconds(BRUSHLESS_MOTOR_LOWER_LIMIT);
  }
  else
  {
    brushlessMotorValue = map(mySpeed, MIN_VAL_TO_ENTERTAIN_FROM_REMOTE, MAX_VAL_TO_ENTERTAIN_FROM_REMOTE, BRUSHLESS_MOTOR_MIN_TO_WORK, BRUSHLESS_MOTOR_UPPER_LIMIT);
    debug(WRITE_DATA_TO_BRUSHLESS, brushlessMotorValue);
    directionServo.write(myDirection);
    speedServo.writeMicroseconds(brushlessMotorValue);
  }
}
