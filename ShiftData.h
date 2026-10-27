//
// Created by Destiny Acuna on 10/26/26.
//

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


#endif //COP3003FINAL_SHIFTDATA_H