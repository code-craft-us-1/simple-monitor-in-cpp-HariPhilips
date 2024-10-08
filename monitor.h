#pragma once

struct Vitals {
    float temperature;
    float pulseRate;
    float spo2;
};

int vitalsOk(const Vitals& vitals);
