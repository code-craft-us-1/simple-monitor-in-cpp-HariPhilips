#pragma once
#include <vector>
#include <string>

enum class Unit {
    Fahrenheit,
    Celsius
};

struct Vitals {
    float temperature;
    float pulseRate;
    float spo2;
    Unit temperatureUnit;  // Added to differentiate the temperature units
};

class VitalCheck {
 public:
    virtual bool isCritical(const Vitals& vitals) const = 0;
    virtual bool isWarning(const Vitals& vitals) const = 0;
    virtual const char* criticalMessage() const = 0;
    virtual const char* warningMessage() const = 0;
    virtual ~VitalCheck() = default;
};

template <typename T>
bool isWithinTolerance(T value, T lowerBound, T upperBound) {
    return value >= lowerBound && value < upperBound;
}

bool handleWarning(const Vitals&, const VitalCheck* check);
bool handleCritical(const Vitals&, const VitalCheck* check);
bool isVitalsOk(const Vitals&, const std::vector<VitalCheck*>& checks);
void displayAlert(const std::string& message);
