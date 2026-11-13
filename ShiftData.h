
#ifndef COP3003FINAL_SHIFTDATA_H
#define COP3003FINAL_SHIFTDATA_H

#include <memory>
#include <string>
#include "TipOut.h"

class ShiftData
{
protected:
    double hours;
    double hourlyWage;
    double tips;
    double sales;

    // stores which method we figure out the tip out
    std::shared_ptr<TipOut> tipOutMethod;

public:
    ShiftData(double hours, double hourlyWage,
              double tips, double sales,
              std::shared_ptr<TipOut> tipOutMethod);

    virtual ~ShiftData();

    virtual double calculateEarnings() const;

    virtual double calculateHourly() const;

    virtual std::string getShiftType() const;

    virtual std::unique_ptr<ShiftData> clone() const;
};

#endif
