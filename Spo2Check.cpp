#include "./monitor.h"

constexpr float MIN_SPO2 = 90.0;
constexpr float SPO2_TOLERANCE = 1.5;  // 1.5% tolerance for SpO2

class Spo2Check : public VitalCheck {
public:
    bool isCritical(const Vitals& vitals) const override {
        return vitals.spo2 < MIN_SPO2;
    }

    bool isWarning(const Vitals& vitals) const override {
        return vitals.spo2 > MIN_SPO2 && vitals.spo2 <= MIN_SPO2 + SPO2_TOLERANCE;
    }

    const char* criticalMessage() const override {
        return "Oxygen Saturation is out of range!";
    }

    const char* warningMessage() const override {
        return "Warning: Approaching low oxygen saturation!";
    }
};
