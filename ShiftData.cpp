#include "ShiftData.h"

//Constructor
ShiftData::ShiftData(double shiftHours, double shiftWage,
    double shiftTips, double shiftTipOut)
{
    hours = shiftHours;
    hourlyWage = shiftWage;
    tips = shiftTips;
    tipOut = shiftTipOut;
}
