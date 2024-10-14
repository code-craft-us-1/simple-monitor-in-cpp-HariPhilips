#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

constexpr float MAX_TEMP = 102.0;
constexpr float MIN_TEMP = 95.0;
constexpr int MAX_PULSE = 100;
constexpr int MIN_PULSE = 60;
constexpr float MIN_SPO2 = 90.0;


void displayAlert(const std::string& message) {
    cout << message << "\n";
    std::string blinkPattern[2] = {"\r* ", "\r *"};
    for (int i = 0; i < 6; ++i) {
        cout << blinkPattern[i % 2] << flush;
        sleep_for(seconds(1));
    }
    cout << "\n";
}

bool isTemperatureCritical(const Vitals& vitals) {
    return vitals.temperature > MAX_TEMP || vitals.temperature < MIN_TEMP;
}

bool isPulseRateCritical(const Vitals& vitals) {
    return vitals.pulseRate < MIN_PULSE || vitals.pulseRate > MAX_PULSE;
}

bool isSpo2Critical(const Vitals& vitals) {
    return vitals.spo2 < MIN_SPO2;
}

int vitalsOk(const Vitals& vitals) {
    VitalCheck checks[] = {
        {isTemperatureCritical, "Temperature is critical!"},
        {isPulseRateCritical, "Pulse Rate is out of range!"},
        {isSpo2Critical, "Oxygen Saturation is out of range!"}
    };

    bool allVitalsOk = true;

    for (const auto& check : checks) {
        if (check.isCritical(vitals)) {
            displayAlert(check.message);
            allVitalsOk = false;
        }
    }

    return allVitalsOk;
}
