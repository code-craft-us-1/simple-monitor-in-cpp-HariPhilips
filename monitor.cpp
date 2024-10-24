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

bool isVitalsOk(const Vitals& vitals, const std::vector<VitalCheck*>& checks) {
    bool allVitalsOk = true;

    for (const auto& check : checks) {
        if (check->isWarning(vitals)) {
            displayAlert(check->warningMessage());
        }

        if (check->isCritical(vitals)) {
            displayAlert(check->criticalMessage());
            allVitalsOk = false;
        }
    }

    return allVitalsOk;
}
