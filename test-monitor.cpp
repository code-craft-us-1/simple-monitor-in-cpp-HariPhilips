#include "./monitor.h"
#include "gtest/gtest.h"
#include "./TemperatureCheck.h"
#include "./PulseRateCheck.h"
#include "./Spo2Check.h"
#include <vector>

// Test fixture class
class MonitorTest : public ::testing::Test {
 protected:
    std::vector<VitalCheck*> checks;

    void SetUp() override {
        checks = {new TemperatureCheck(), new PulseRateCheck(), new Spo2Check()};
    }

    void TearDown() override {
        for (auto check : checks) {
            delete check;
        }
        checks.clear();
    }
};

TEST_F(MonitorTest, NotOkWhenAnyVitalIsOffRange) {
    // Some vitals off range
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT, MAX_PULSE, MIN_SPO2 - 1, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, OkWhenAllVitalsAreInRange) {
    // All vitals within range
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT - 1, MAX_PULSE - 1, MIN_SPO2 + 5, Unit::Fahrenheit};
    ASSERT_TRUE(isVitalsOk(testVitals, checks));

    // Close to minimum but within range
    testVitals = {MIN_TEMP_FAHRENHEIT + 1, MIN_PULSE + 10, MIN_SPO2 + 10, Unit::Fahrenheit};
    ASSERT_TRUE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenTemperatureIsOffRange) {
    // Temperature above max
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT + 1, 100, 100, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));

    // Temperature below min
    testVitals = {MIN_TEMP_FAHRENHEIT - 1, 100, 100, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenPulseRateIsOffRange) {
    // Pulse rate above max
    Vitals testVitals = {100, MAX_PULSE + 1, 100, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));

    // Pulse rate below min
    testVitals = {100, MIN_PULSE - 1, 100, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenSpO2IsOffRange) {
    // SpO2 below min
    Vitals testVitals = {100, 100, MIN_SPO2 - 1, Unit::Fahrenheit};
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, TemperatureInCelsius) {
    // Normal temperature in Celsius
    ASSERT_TRUE(isVitalsOk(Vitals{37.0, MAX_PULSE, MIN_SPO2, Unit::Celsius}, checks));

    // High temperature warning in Celsius (Approaching hyperthermia)
    ASSERT_TRUE(isVitalsOk(Vitals{38.2, MAX_PULSE, MIN_SPO2, Unit::Celsius}, checks));

    // High temperature critical in Celsius
    ASSERT_FALSE(isVitalsOk(Vitals{39.0, MAX_PULSE, MIN_SPO2, Unit::Celsius}, checks));

    // Low temperature warning in Celsius (Approaching hypothermia)
    ASSERT_TRUE(isVitalsOk(Vitals{35.2, MAX_PULSE, MIN_SPO2, Unit::Celsius}, checks));

    // Low temperature critical in Celsius
    ASSERT_FALSE(isVitalsOk(Vitals{34.0, MAX_PULSE, MIN_SPO2, Unit::Celsius}, checks));
}
