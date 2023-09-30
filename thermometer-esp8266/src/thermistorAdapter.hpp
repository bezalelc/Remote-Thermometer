#ifndef NTC_HPP
#define NTC_HPP

#include <Arduino.h>

/**
 * static class for read themperature from analog to digital pin (A0)
 */
class ThermistorAdapter
{
private:
    static ThermistorAdapter *instance;

    double getResistence(uint probId) const;
    ThermistorAdapter();
    ThermistorAdapter(const ThermistorAdapter &other) = delete;
    void setAdcInputToProbId(uint probId) const;

public:
    ~ThermistorAdapter() {}
    double readTemperature(uint probId) const;
    static ThermistorAdapter &getInstance();
};

#endif