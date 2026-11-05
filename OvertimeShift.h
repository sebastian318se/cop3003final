
#ifndef COP3003FINAL_OVERTIMESHIFT_H
#define COP3003FINAL_OVERTIMESHIFT_H

#include "ShiftData.h"

class OvertimeShift : public ShiftData
{
public:
    OvertimeShift(double hours, double hourlyWage,
                  double tips, double tipOut);

    double calculateEarnings() const override;

    std::string getShiftType() const override;

    std::unique_ptr<ShiftData> clone() const override;
};

#endif
