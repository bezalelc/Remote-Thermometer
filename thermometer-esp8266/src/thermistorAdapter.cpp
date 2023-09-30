#include <Arduino.h>
#include "thermistorAdapter.hpp"
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

#define IS_BIT_SET(number, bitIdx) (number & (1 << bitIdx))
#define S0_INPUT D1
#define S1_INPUT D3
#define S2_INPUT D4

ThermistorAdapter *ThermistorAdapter::instance = nullptr;

ThermistorAdapter::ThermistorAdapter()
{
    pinMode(S0_INPUT, OUTPUT);
    pinMode(S1_INPUT, OUTPUT);
    pinMode(S2_INPUT, OUTPUT);
}

void ThermistorAdapter::setAdcInputToProbId(uint probId) const
{
    digitalWrite(S0_INPUT, IS_BIT_SET(probId, 0));
    digitalWrite(S1_INPUT, IS_BIT_SET(probId, 1));
    digitalWrite(S2_INPUT, IS_BIT_SET(probId, 2));
}

double ThermistorAdapter::getResistence(uint probId) const
{
    setAdcInputToProbId(probId);
    int analog2digital = analogRead(A0);
    double volt = (((double)analog2digital) * ADC_MAX_VOLT) / (double)ADC_MAX_VAL;
    double probResistence = ((double)RESISTOR_OHMS * volt) / ((double)POWER_SUPLY_VOLT - volt);
    DEBUG_MODE_PRINT_NAMES_VALUES(analog2digital, volt, probResistence);
    return probResistence;
}

ThermistorAdapter &ThermistorAdapter::getInstance()
{
    if (!instance)
    {
        instance = new ThermistorAdapter();
    }
    return *instance;
}

double ThermistorAdapter::readTemperature(uint probId) const
{
    double lnProbResistence = log(getResistence(probId));
    double temperature = 1.0 / (COEFF(A) + COEFF(B) * lnProbResistence + COEFF(C) * lnProbResistence * lnProbResistence * lnProbResistence);
    DEBUG_MODE_PRINT_NAMES_VALUES(lnProbResistence, temperature);
    return temperature - 273.15;
}
