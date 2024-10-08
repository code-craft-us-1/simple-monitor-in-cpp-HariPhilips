#include "./monitor.h"
#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(Vitals{99, 102, 70}));
  ASSERT_TRUE(vitalsOk(Vitals{98.1, 70, 98}));
}

TEST(Monitor, OkWhenAllVitalsAreInRange) {
  ASSERT_TRUE(vitalsOk(Vitals{100, 100, 100}));
  ASSERT_TRUE(vitalsOk(Vitals{98.6, 80, 95}));
  ASSERT_TRUE(vitalsOk(Vitals{97.5, 90, 100}));
}

TEST(Monitor, NotOkWhenTemperatureIsOffRange) {
  ASSERT_FALSE(vitalsOk(Vitals{103, 100, 100}));
  ASSERT_FALSE(vitalsOk(Vitals{90, 100, 100}));
}

TEST(Monitor, NotOkWhenPulseRateIsOffRange) {
  ASSERT_FALSE(vitalsOk(Vitals{100, 101, 100}));
  ASSERT_FALSE(vitalsOk(Vitals{100, 55, 100}));
}

TEST(Monitor, NotOkWhenBloodPressureIsOffRange) {
  ASSERT_FALSE(vitalsOk(Vitals{100, 100, 71}));
  ASSERT_FALSE(vitalsOk(Vitals{100, 100, 69}));
}