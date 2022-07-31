int calculatePosition(int value)
{
  switch (value) {
    case 0:
      return 0;
    case 10:
      return 20;
    case 20:
      return 35;
    case 30:
      return 50;
    case 40:
      return 65;
    case 50:
      return 80;
    case 60:
      return 95;
    case 70:
      return 110;
    case 80:
      return 125;
    case 90:
      return 145;
    case 100:
      return 160;
    default:
      return 0;
  }
}

String setServoPosition(int frontValue, int backValue)
{
  if (EEPROM.read(0) != frontValue)
  {
    Serial.println(calculatePosition(frontValue));
    delay(1000);
    servoFrontLeft.write(calculatePosition(frontValue));
    delay(1000);
    servoFrontRight.write(calculatePosition(frontValue));
    delay(1000);
  }

  if (EEPROM.read(1) != backValue)
  {
    Serial.println(calculatePosition(backValue));
    delay(1000);
    servoBackLeft.write(calculatePosition(backValue));
    delay(1000);
    servoBackRight.write(calculatePosition(backValue));
    delay(1000);
  }
  return "Success";
}
