
#ifndef COP3003FINAL_TRACKER_H
#define COP3003FINAL_TRACKER_H

#include <vector>
#include <memory>
#include "ShiftData.h"
#include "TipOut.h"

class Tracker
{
    //creates a list that owns all the shifts
private:
    std::vector<std::unique_ptr<ShiftData>> shifts;

public:
    // adds Shiftdata object to tracker thats already been created
    void addShift(const ShiftData& shift);

    //overload of addShift
    // user can provide shift information
    void addShift(double hours, double hourlyWage,
        double tips, double sales, std::shared_ptr<TipOut> tipOutMethod);



    void editShift(int index, const ShiftData& shift);

    void deleteShift(int index);

    const ShiftData& getShift(int index) const;

    int getShiftCount() const;

    double getTotalEarnings() const;

    void displayShifts() const;
};

#endif
