#include "ShiftData.h"

// Constructor
ShiftData::ShiftData(double shiftHours, double shiftWage,
                     double shiftTips, double shiftTipOut)
{
    hours = shiftHours;
    hourlyWage = shiftWage;
    tips = shiftTips;
    tipOut = shiftTipOut;
}

// Calculates total earnings for the shift
double ShiftData::calculateEarnings() const
{
    return (hours * hourlyWage) + tips - tipOut;
}

// Calculates average hourly earnings
double ShiftData::calculateHourly() const
{
    if (hours == 0)
    {
        return 0;
    }

    return calculateEarnings() / hours;
}