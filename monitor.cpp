#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void displayAlert(const std::string& message) {
    cout << message << "\n";
    std::string blinkPattern[2] = {"\r* ", "\r *"};
    for (int i = 0; i < 6; ++i) {
        cout << blinkPattern[i % 2] << flush;
        sleep_for(seconds(1));
    }
    cout << "\n";
}

bool handleWarning(const Vitals& vitals, const VitalCheck* check) {
    if (check->isWarning(vitals)) {
        displayAlert(check->warningMessage());
        return true;
    }
    return false;
}

bool handleCritical(const Vitals& vitals, const VitalCheck* check) {
    if (check->isCritical(vitals)) {
        displayAlert(check->criticalMessage());
        return true;
    }
    return false;
}

bool isVitalsOk(const Vitals& vitals, const std::vector<VitalCheck*>& checks) {
    bool allVitalsOk = true;

    for (const auto& check : checks) {
        handleWarning(vitals, check);
        if (handleCritical(vitals, check)) {
            allVitalsOk = false;
        }
    }

    return allVitalsOk;
}

