    const int thermistorPin = A0; // Analog pin connected to the thermistor
    const float nominalResistance = 10000; // Thermistor nominal resistance at 25°C
    const float nominalTemperature = 25; // Nominal temperature in Celsius
    const float B_coefficient = 3950; // Beta coefficient of the thermistor
    const float seriesResistor = 10000; // Resistance of the series resistor in the voltage divider

    void setup() {
      Serial.begin(9600); // Initialize serial communication at 9600 baud rate
    }

    void loop() {
      int analogValue = analogRead(thermistorPin); // Read the analog value from the thermistor
      float voltage = analogValue * (5.0 / 1023.0); // Convert analog value to voltage
      float resistance = seriesResistor / ((5.0 / voltage) - 1); // Calculate thermistor resistance

      // Calculate temperature using the Steinhart-Hart equation
      float steinhart;
      steinhart = resistance / nominalResistance; // (R/Ro)
      steinhart = log(steinhart); // ln(R/Ro)
      steinhart /= B_coefficient; // 1/B * ln(R/Ro)
      steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/To)
      steinhart = 1.0 / steinhart; // Invert to get absolute temperature
      steinhart -= 273.15; // Convert to Celsius

      Serial.print("Temperature: ");
      Serial.print(steinhart);
      Serial.println(" °C");

      delay(1000); // Wait for a second before the next reading
    }