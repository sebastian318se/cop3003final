
#include "ShiftData.h"
#include <stdexcept>
#include "Utilities.h"

ShiftData::ShiftData(double shiftHours, double shiftWage,
                     double shiftTips, double shiftSales,
                     std::shared_ptr<TipOut> shiftTipOutMethod)
{
    if (negative(shiftHours)) {
        throw std::invalid_argument("Shift hours cannot be negative");
    }

    if (negative(shiftHours)) {
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

//access private attributes through getters
double ShiftData::getHours() const
{
    return hours;
}

double ShiftData::getHourlyWage() const
{
    return hourlyWage;
}

double ShiftData::getTips() const
{
    return tips;
}

double ShiftData::getSales()const
{
    return sales;
}

//Asks TipOut object what the type is
std::string ShiftData::getTipOutType() const
{
    return tipOutMethod->getType();
}

//Asks TipOut object for what number it stores
double ShiftData::getTipOutValue() const
{
    return tipOutMethod->getValue();
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
