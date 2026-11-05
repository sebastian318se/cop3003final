
#include "ShiftData.h"

ShiftData::ShiftData(double shiftHours, double shiftWage,
                     double shiftTips, double shiftTipOut)
{
    hours = shiftHours;
    hourlyWage = shiftWage;
    tips = shiftTips;
    tipOut = shiftTipOut;
}

ShiftData::~ShiftData()
{
}

// Regular shift earnings
double ShiftData::calculateEarnings() const
{
    return (hours * hourlyWage) + tips - tipOut;
}

// Average hourly earnings
double ShiftData::calculateHourly() const
{
    if (hours == 0)
    {
        return 0;
    }

    return calculateEarnings() / hours;
}

std::string ShiftData::getShiftType() const
{
    return "Regular Shift";
}

// Allows Tracker to safely copy derived objects
std::unique_ptr<ShiftData> ShiftData::clone() const
{
    return std::unique_ptr<ShiftData>(new ShiftData(*this));
}
