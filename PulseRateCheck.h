#pragma once
#include "./monitor.h"

constexpr float MAX_PULSE = 100.0;
constexpr float MIN_PULSE = 60.0;
constexpr float PULSE_TOLERANCE = MAX_PULSE * 0.015;

class PulseRateCheck : public VitalCheck {
 public:
    bool isCritical(const Vitals& vitals) const override {
        return vitals.pulseRate > MAX_PULSE || vitals.pulseRate < MIN_PULSE;
    }

bool isWarning(const Vitals& vitals) const override {
    return isWithinTolerance(vitals.pulseRate, MAX_PULSE - PULSE_TOLERANCE, MAX_PULSE) ||
           isWithinTolerance(vitals.pulseRate, MIN_PULSE, MIN_PULSE + PULSE_TOLERANCE);
}

    const char* criticalMessage() const override {
        return "Pulse Rate is out of range!";
    }

    const char* warningMessage() const override {
        return "Warning: Approaching abnormal pulse rate!";
    }
};
