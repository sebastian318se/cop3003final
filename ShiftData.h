#ifndef COP3003FINAL_SHIFTDATA_H
#define COP3003FINAL_SHIFTDATA_H

class ShiftData
{
private:
    double hours;
    double hourlyWage;
    double tips;
    double tipOut;

public:
    ShiftData(double hours, double hourlyWage,
              double tips, double tipOut);

    double calculateEarnings() const;
    double calculateHourly() const;
};

#endif