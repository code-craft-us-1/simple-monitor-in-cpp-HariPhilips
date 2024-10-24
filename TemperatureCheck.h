#pragma once
#include "./monitor.h"

constexpr float MAX_TEMP_FAHRENHEIT = 102.0;
constexpr float MIN_TEMP_FAHRENHEIT = 95.0;
constexpr float TEMP_TOLERANCE_FAHRENHEIT = MAX_TEMP_FAHRENHEIT * 0.015;  // 1.5% tolerance

float convertToFahrenheit(float temperature, Unit unit) {
    if (unit == Unit::Celsius) {
        return (temperature * 9.0 / 5.0) + 32.0;
    }
    return temperature;  // Already in Fahrenheit
}

class TemperatureCheck : public VitalCheck {
 public:
    bool isCritical(const Vitals& vitals) const override {
        float tempInFahrenheit = convertToFahrenheit(vitals.temperature, vitals.temperatureUnit);
        return tempInFahrenheit > MAX_TEMP_FAHRENHEIT || tempInFahrenheit < MIN_TEMP_FAHRENHEIT;
    }

    bool isWarning(const Vitals& vitals) const override {
        float tempInFahrenheit = convertToFahrenheit(vitals.temperature, vitals.temperatureUnit);

        return isWithinTolerance(tempInFahrenheit, MAX_TEMP_FAHRENHEIT - TEMP_TOLERANCE_FAHRENHEIT, MAX_TEMP_FAHRENHEIT) ||
               isWithinTolerance(tempInFahrenheit, MIN_TEMP_FAHRENHEIT, MIN_TEMP_FAHRENHEIT + TEMP_TOLERANCE_FAHRENHEIT);
    }

    const char* criticalMessage() const override {
        return "Temperature is critical!";
    }

    const char* warningMessage() const override {
        return "Warning: Approaching hyperthermia or hypothermia!";
    }
};
