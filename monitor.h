#pragma once

struct Vitals {
    float temperature;
    float pulseRate;
    float spo2;
};

struct VitalCheck {
    bool (*isCritical)(const Vitals&);
    const char* message;
};

int vitalsOk(const Vitals& vitals);
