
#ifndef COP3003FINAL_SHIFTDATA_H
#define COP3003FINAL_SHIFTDATA_H

#include <memory>
#include <string>

class ShiftData
{
protected:
    double hours;
    double hourlyWage;
    double tips;
    double tipOut;

public:
    ShiftData(double hours, double hourlyWage,
              double tips, double tipOut);

    virtual ~ShiftData();

    virtual double calculateEarnings() const;

    virtual double calculateHourly() const;

    virtual std::string getShiftType() const;

    virtual std::unique_ptr<ShiftData> clone() const;
};

#endif
