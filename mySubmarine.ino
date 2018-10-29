#include "Submarine.h"

String fromNetwork = "";
unsigned long timer = 0;

int batteryPercentage = 0;
String dataToSend = "";

void setup()
{
  Serial.begin(9600);
  Serial1.begin(38400);
  debug(INIT);
  setUpModules();
}

void loop()
{
  if (Serial1.available() > 0)
  {
    readDataFromNetwork();
  }

  if (timer != 0 && millis() - timer >= 5000)
  {
    debug("Disconnected.. Going in Rescue Mode");
    rescueMode();
  }
}

void readDataFromNetwork()
{
  fromNetwork += ((char) Serial1.read());

  if (fromNetwork.equals(HELLO_FROM_REMOTE))
  {
    debug(CONNECTED_WITH_REMOTE);
    fromNetwork = "";
    directionServo.write(90);
    speedServo.writeMicroseconds(BRUSHLESS_MOTOR_LOWER_LIMIT);
    timer = millis();

    dataToSend = "S" + (String)batteryPercentage + "E";

    Serial1.flush();
    Serial1.print(dataToSend);

    if (batteryPercentage < 100)
      batteryPercentage++;
  }
  else if (fromNetwork.indexOf(DATA_TERMINATOR) > -1)
  {
    debug(DATA_FROM_CONTROLLER, fromNetwork);
    decryptValues(fromNetwork);
    writeDataToMotors();
    fromNetwork = "";
    timer = millis();

    dataToSend = "S" + (String)batteryPercentage + "E";
    Serial1.flush();
    Serial1.print(dataToSend);

    if (batteryPercentage < 100)
      batteryPercentage++;
  }
}

void rescueMode()
{
  fromNetwork = "";
  directionServo.write(90);
  speedServo.writeMicroseconds(BRUSHLESS_MOTOR_LOWER_LIMIT);
  timer = 0;
}
