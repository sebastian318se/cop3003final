
#ifndef COP3003FINAL_TRACKER_H
#define COP3003FINAL_TRACKER_H

#include <vector>
#include <memory>
#include "ShiftData.h"

class Tracker
{
private:
    std::vector<std::unique_ptr<ShiftData>> shifts;

public:
    void addShift(const ShiftData& shift);

    void editShift(int index, const ShiftData& shift);

    void deleteShift(int index);

    const ShiftData& getShift(int index) const;

    int getShiftCount() const;

    double getTotalEarnings() const;

    void displayShifts() const;
};

#endif
