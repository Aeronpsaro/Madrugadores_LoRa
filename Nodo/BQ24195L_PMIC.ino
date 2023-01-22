// ----------------------------------------------------------------------------------
// Initilizes BQ24195L_PMIC to allow battery operation and recharge
// ----------------------------------------------------------------------------------

bool init_PMIC()
{
  bool error = false;
  
  if (!PMIC.begin()) {
    SerialUSB.println("ERROR: Failed to initialize PMIC!");
    return false;
  }

  // Set the input current limit to 1 A and the overload input voltage to 3.88 V
  if (!PMIC.setInputCurrentLimit(2.0)) { 
    SerialUSB.println("ERROR: PMIC.setInputCurrentLimit() failed!");
    error = true;
  }

  if (!PMIC.setInputVoltageLimit(3.88)) {
    SerialUSB.println("ERROR: PMIC.setInputVoltageLimit() failed!");
    error = true;
  }

  // set the minimum voltage used to feeding the module embed on Board
  if (!PMIC.setMinimumSystemVoltage(3.5)) {
    SerialUSB.println("ERROR: PMIC.setMinimumSystemVoltage() failed!");
    error = true;
  }

  // Set the desired charge voltage to 4.2 V
  if (!PMIC.setChargeVoltage(4.2)) {
    SerialUSB.println("ERROR: PMIC.setChargeVoltage() failed!");
    error = true;
  }

  // Set the charge current to 375 mA
  // the charge current should be defined as maximum at (C for hour)/2h
  // to avoid battery explosion (for example for a 750 mAh battery set to 0.375 A)
  if (!PMIC.setChargeCurrent(0.375)) {
    SerialUSB.println("ERROR: PMIC.setChargeCurrent() failed!");
    error = true;
  }

  if (!PMIC.enableCharge()) {
    SerialUSB.println("ERROR: PMIC.enableCharge() failed!");
    error = true;
  }
  delay(1000);
  
   int chargeStatus = PMIC.chargeStatus();
  switch(chargeStatus) {
    case NOT_CHARGING:
      SerialUSB.println("Charge status: Not charging");
      break;

    case PRE_CHARGING:
      SerialUSB.println("Charge status: Pre charging");
      break;

    case FAST_CHARGING:
      SerialUSB.println("Charge status: Fast charging");
      break;

    case CHARGE_TERMINATION_DONE:
      SerialUSB.println("Charge status: Charge termination done");
  }

  SerialUSB.print("Battery is connected: ");
  if (PMIC.isBattConnected()) SerialUSB.println("Yes");
  else SerialUSB.println("No");

  SerialUSB.print("Power is good: ");
  if (PMIC.isPowerGood()) SerialUSB.println("Yes");
  else SerialUSB.println("No");

  SerialUSB.print("Charge current (A): ");
  SerialUSB.println(PMIC.getChargeCurrent(),2);

  SerialUSB.print("Charge voltage (V): ");
  SerialUSB.println(PMIC.getChargeVoltage(), 2);

  SerialUSB.print("Minimum system voltage(V): ");
  SerialUSB.println(PMIC.getMinimumSystemVoltage(),2);

  SerialUSB.print("Battery voltage is below minimum system voltage: ");
  if (!PMIC.canRunOnBattery()) SerialUSB.println("No");
  else SerialUSB.println("Yes");
  
  if (error) return false;
  else return true;
}
