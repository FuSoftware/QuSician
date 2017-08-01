#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H

#include "../midievent.h"
#include <string>
#include <sstream>


class TimeSignature : public MidiEvent
{
public:
    TimeSignature(int delta = 0, int nn = TimeSignature::DEFAULT_NUMERATOR, int dd = TimeSignature::DEFAULT_DENOMINATOR, int cc = TimeSignature::DEFAULT_CLOCK, int bb = TimeSignature::DEFAULT_32);
    int getNumerator() const;
    int getDenominator() const;
    int getClock() const;
    int getThirtySeconds() const;
    std::string toString();
    std::vector<unsigned char> getData();

    const static int DEFAULT_CLOCK = 24;
    const static int DEFAULT_DENOMINATOR = 4;
    const static int DEFAULT_NUMERATOR = 4;
    const static int DEFAULT_32 = 4;

private:
    int numerator;
    int denominator;
    int clock;
    int thirtySeconds;
};

#endif // TIMESIGNATURE_H
