
#include "OvertimeShift.h"

OvertimeShift::OvertimeShift(double shiftHours, double shiftWage,
                             double shiftTips, double shiftTipOut)
    : ShiftData(shiftHours, shiftWage, shiftTips, shiftTipOut)
{
}

// Overtime earnings calculation
double OvertimeShift::calculateEarnings() const
{
    double regularHours = hours;
    double overtimeHours = 0;

    if (hours > 8)
    {
        regularHours = 8;
        overtimeHours = hours - 8;
    }

    double regularPay = regularHours * hourlyWage;
    double overtimePay = overtimeHours * hourlyWage * 1.5;

    return regularPay + overtimePay + tips - tipOut;
}

std::string OvertimeShift::getShiftType() const
{
    return "Overtime Shift";
}

std::unique_ptr<ShiftData> OvertimeShift::clone() const
{
    return std::unique_ptr<ShiftData>(new OvertimeShift(*this));
}
