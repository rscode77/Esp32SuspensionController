int calculatePosition(int value)
{
  switch (value) {
    case 0:
      return 0;
    case 10:
      return 16;
    case 20:
      return 32;
    case 30:
      return 48;
    case 40:
      return 64;
    case 50:
      return 80;
    case 60:
      return 96;
    case 70:
      return 112;
    case 80:
      return 128;
    case 90:
      return 144;
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
    delay(3000);
    servoFrontLeft.write(calculatePosition(frontValue));
    Serial.print("ok");
    delay(3000);
    servoFrontRight.write(calculatePosition(frontValue));
    Serial.print("ok");
  }

  if (EEPROM.read(1) != backValue)
  {
    Serial.println(calculatePosition(backValue));
    delay(3000);   
    servoBackLeft.write(calculatePosition(backValue));
     Serial.print("ok");
    delay(3000);
    servoBackRight.write(calculatePosition(backValue));
    Serial.print("ok");
  }
  return "Success";
}
