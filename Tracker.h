#ifndef COP3003FINAL_TRACKER_H
#define COP3003FINAL_TRACKER_H

#include <vector>
#include "ShiftData.h"

class Tracker
{
private:
    std::vector<ShiftData> shifts;

public:
    void addShift(const ShiftData& shift);
    bool editShift(int index, const ShiftData& shift);
    bool deleteShift(int index);

    const std::vector<ShiftData>& getShifts() const;
    int getShiftCount() const;
};

#endif