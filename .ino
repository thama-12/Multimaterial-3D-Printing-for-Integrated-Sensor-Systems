/*
  ============================================================================
  Title       : Strain Sensor Monitoring via Wheatstone Bridge
  Project     : Multimaterial 3D Printed Strain Sensor Evaluation
  Author      : Thamarai Kannan M K S
  Institution : Bannari Amman Institute of Technology
  Date        : April 2025
  Platform    : Arduino Uno (10-bit ADC)
  Version     : 1.0

  Description:
    This code is designed to monitor voltage output from a Wheatstone bridge
    circuit in which one leg includes a 3D printed strain sensor. The system
    records the initial voltage and logs deflection (voltage change) as the
    sensor is subjected to tensile load in a UTM.

  Components:
    - Arduino Uno
    - Wheatstone Bridge (3 known resistors + 1 strain sensor)
    - 5V DC Power Supply
    - Breadboard for resistor network
    - UTM (Universal Testing Machine) for applying tensile load

  ============================================================================
*/

// ------------------------ Configuration ------------------------

const int bridgePin = A0;       // Analog pin connected to bridge output
const float Vcc = 5.0;          // Supply voltage (typically 5V)
const int adcResolution = 1023; // 10-bit ADC resolution

// ------------------------ Runtime Variables ------------------------

float initialVoltage = 0.0;     // To store baseline voltage at rest
bool isBaselineSet = false;     // Flag for initial reading

// ------------------------ Arduino Setup ------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Strain Sensor Bridge Monitoring...");
  delay(2000);  // Allow sensor to stabilize

  // Capture baseline voltage
  int rawInitial = analogRead(bridgePin);
  initialVoltage = (rawInitial * Vcc) / adcResolution;
  isBaselineSet = true;

  Serial.print("Initial Bridge Voltage: ");
  Serial.print(initialVoltage, 4);
  Serial.println(" V");
  Serial.println("Monitoring started...\n");
}

// ------------------------ Main Loop ------------------------

void loop() {
  int rawADC = analogRead(bridgePin);
  float currentVoltage = (rawADC * Vcc) / adcResolution;

  // Calculate deflection (change from baseline)
  float voltageDeflection = currentVoltage - initialVoltage;

  // Serial output
  Serial.print("Current Voltage: ");
  Serial.print(currentVoltage, 4);
  Serial.print(" V\t");

  Serial.print("Voltage Deflection: ");
  Serial.print(voltageDeflection, 4);
  Serial.println(" V");

  delay(500);  // Sampling interval
}
