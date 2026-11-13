
#include "ShiftData.h"
#include <stdexcept>

ShiftData::ShiftData(double shiftHours, double shiftWage,
                     double shiftTips, double shiftSales,
                     std::shared_ptr<TipOut> shiftTipOutMethod)
{
    if (shiftHours < 0) {
        throw std::invalid_argument("Shift hours cannot be negative");
    }

    if (shiftSales < 0) {
        throw std::invalid_argument("Sales cannot be negative");
    }

    hours = shiftHours;
    hourlyWage = shiftWage;
    tips = shiftTips;
    sales = shiftSales;
    tipOutMethod = shiftTipOutMethod;
}

ShiftData::~ShiftData()
{
}

//total earnings for a shift
double ShiftData::calculateEarnings() const
{
   // use the tip-out method for this shift and calculate the amount
    double calculatedTipOut = tipOutMethod -> calculateTipOut(sales);

    return (hours * hourlyWage) + tips - calculatedTipOut;
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
