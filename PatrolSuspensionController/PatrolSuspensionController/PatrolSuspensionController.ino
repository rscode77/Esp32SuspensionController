#include "BluetoothSerial.h"
#include <EEPROM.h>
#include <ESP32Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define EEPROM_SIZE 2

int frontLeft = 12;
int frontRight = 27;
int backLeft = 25;
int backRight = 32;

Servo servoFrontLeft;
Servo servoFrontRight;
Servo servoBackLeft;
Servo servoBackRight;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servoFrontLeft.setPeriodHertz(50);
  servoFrontLeft.attach(frontLeft, 500, 2500);

  servoFrontRight.setPeriodHertz(50);
  servoFrontRight.attach(frontRight, 500, 2500);

  servoBackLeft.setPeriodHertz(50);
  servoBackLeft.attach(backLeft, 500, 2500);

  servoBackRight.setPeriodHertz(50);
  servoBackRight.attach(backRight, 500, 2500);

  Serial.begin(115200);
  SerialBT.begin("PatrolSuspensionController"); //Bluetooth device name
  EEPROM.begin(EEPROM_SIZE);
}

String message = "";
int pos = 0;
void loop() {
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
      message += String(incomingChar);
    }
    else {
      message = "";
    }

    Serial.write(incomingChar);

    if (message == "getconfig")
    {
      int front = EEPROM.read(0);
      int back = EEPROM.read(1);

      SerialBT.println("!" + String(front) + "%" + String(back) + "!");
    }

    if (message[0] == '!' && message[message.length() - 1] == '!' && message.indexOf('%') > 0)
    {
      message.replace("!", "");

      int index = message.indexOf('%');

      int front = message.substring(0, index).toInt();
      int back = message.substring(index + 1, message.length()).toInt();

      Serial.println(front);
      Serial.println(back);

      String result = setServoPosition(front, back);
      if (result == "Success") {
        EEPROM.write(0, front);
        EEPROM.write(1, back);
        EEPROM.commit();
        SerialBT.println("Success");
      }
      else
      {
        SerialBT.println("Error");
      }
    }
  }
}
