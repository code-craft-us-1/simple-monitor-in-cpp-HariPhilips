#include "./monitor.h"

constexpr int MAX_PULSE = 100;
constexpr int MIN_PULSE = 60;
constexpr float PULSE_TOLERANCE = MAX_PULSE * 0.015;

class PulseRateCheck : public VitalCheck {
public:
    bool isCritical(const Vitals& vitals) const override {
        return vitals.pulseRate > MAX_PULSE || vitals.pulseRate < MIN_PULSE;
    }

    bool isWarning(const Vitals& vitals) const override {
        return (vitals.pulseRate >= MAX_PULSE - PULSE_TOLERANCE && vitals.pulseRate < MAX_PULSE) ||
               (vitals.pulseRate > MIN_PULSE && vitals.pulseRate <= MIN_PULSE + PULSE_TOLERANCE);
    }

    const char* criticalMessage() const override {
        return "Pulse Rate is out of range!";
    }

    const char* warningMessage() const override {
        return "Warning: Approaching abnormal pulse rate!";
    }
};
