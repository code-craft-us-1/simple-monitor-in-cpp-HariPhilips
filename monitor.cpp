#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
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

int vitalsOk(const Vitals& vitals) {
  int vitalStatus = 1;

    if (vitals.temperature > MAX_TEMP || vitals.temperature < MIN_TEMP) {
        displayAlert("Temperature is critical!");
        vitalStatus = 0;
    }
    if (vitals.pulseRate < MIN_PULSE || vitals.pulseRate > MAX_PULSE) {
        displayAlert("Pulse Rate is out of range!");
        vitalStatus = 0;
    }
    if (vitals.spo2 < MIN_SPO2) {
        displayAlert("Oxygen Saturation is out of range!");
        vitalStatus = 0;
    }
    return vitalStatus;
}

