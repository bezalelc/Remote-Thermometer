#include <Arduino.h>
#include "ntc.hpp"
#include "debugUtils.hpp"

#define COEFF(C) COEFF_##C
#define COEFF_A (0.6727718450e-03f)
#define COEFF_B (3.023118148e-04f)
#define COEFF_C (-1.209848900e-07f)
#define RESISTOR_OHMS (23000.0)
// #define NTC_MAX_OHMS (37000U)
#define POWER_SUPLY_VOLT (5U)
#define ADC_MAX_VOLT (3.3f)
#define ADC_MAX_VAL (0x3FFU)

double Ntc::getResistence()
{
    DEBUG_MODE_SERIAL_PRINTLN("getResistence() ->");
    int adc = analogRead(A0);
    DEBUG_MODE_SERIAL_PRINT("adc: ");
    DEBUG_MODE_SERIAL_PRINT(adc);
    double adcSample = (((double)adc) * ADC_MAX_VOLT) / (double)ADC_MAX_VAL;
    // double adcSample = adc*(3.3/1024.0);
    DEBUG_MODE_SERIAL_PRINT(", adcSample: ");
    DEBUG_MODE_SERIAL_PRINT(adcSample);
    double probResistence = ((double)RESISTOR_OHMS * adcSample) / ((double)POWER_SUPLY_VOLT - adcSample);
    DEBUG_MODE_SERIAL_PRINT(", probResistence: ");
    DEBUG_MODE_SERIAL_PRINTLN(probResistence);
    DEBUG_MODE_SERIAL_PRINTLN("getResistence() <-");
    return probResistence;
}

double Ntc::readTemperature()
{
    double lnProbResistence = log(getResistence());
    DEBUG_MODE_SERIAL_PRINTLN("readTemperature() ->");
    DEBUG_MODE_SERIAL_PRINT("lnProbResistence: ");
    DEBUG_MODE_SERIAL_PRINT(lnProbResistence);
    double temperature = 1.0 / (COEFF(A) + COEFF(B) * lnProbResistence + COEFF(C) * lnProbResistence * lnProbResistence * lnProbResistence);
    // convert from kelvin to celsius
    DEBUG_MODE_SERIAL_PRINT(", temperature: ");
    DEBUG_MODE_SERIAL_PRINT(temperature);
    DEBUG_MODE_SERIAL_PRINT(", temperature celsius: ");
    DEBUG_MODE_SERIAL_PRINTLN(temperature - 273.15);
    DEBUG_MODE_SERIAL_PRINTLN("readTemperature() <-");
    return temperature - 273.15;
}
