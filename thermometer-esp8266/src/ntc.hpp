#ifndef NTC_HPP
#define NTC_HPP

/**
 * static class for read themperature from analog to digital pin (A0)
 */
class Ntc
{
private:
    static double getResistence();
    Ntc() = delete;
    Ntc(const Ntc &other) = delete;

public:
    ~Ntc() {}
    static double readTemperature();
};

#endif