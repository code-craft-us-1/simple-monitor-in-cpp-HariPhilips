#include "./monitor.h"
#include "gtest/gtest.h"
#include "./TemperatureCheck.cpp"
#include "./PulseRateCheck.cpp"
#include "./Spo2Check.cpp"

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
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT, MAX_PULSE, MIN_SPO2 - 1, Unit::Fahrenheit};  // Some vitals off range
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, OkWhenAllVitalsAreInRange) {
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT - 1, MAX_PULSE - 1, MIN_SPO2 + 5, Unit::Fahrenheit};  // All vitals within range
    ASSERT_TRUE(isVitalsOk(testVitals, checks));

    testVitals = {MIN_TEMP_FAHRENHEIT + 1, MIN_PULSE + 10, MIN_SPO2 + 10, Unit::Fahrenheit};  // Close to minimum but within range
    ASSERT_TRUE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenTemperatureIsOffRange) {
    Vitals testVitals = {MAX_TEMP_FAHRENHEIT + 1, 100, 100, Unit::Fahrenheit};  // Temperature above max
    ASSERT_FALSE(isVitalsOk(testVitals, checks));

    testVitals = {MIN_TEMP_FAHRENHEIT - 1, 100, 100, Unit::Fahrenheit};  // Temperature below min
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenPulseRateIsOffRange) {
    Vitals testVitals = {100, MAX_PULSE + 1, 100, Unit::Fahrenheit};  // Pulse rate above max
    ASSERT_FALSE(isVitalsOk(testVitals, checks));

    testVitals = {100, MIN_PULSE - 1, 100, Unit::Fahrenheit};  // Pulse rate below min
    ASSERT_FALSE(isVitalsOk(testVitals, checks));
}

TEST_F(MonitorTest, NotOkWhenSpO2IsOffRange) {
    Vitals testVitals = {100, 100, MIN_SPO2 - 1, Unit::Fahrenheit};  // SpO2 below min
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
