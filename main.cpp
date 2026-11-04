#include <iostream>
#include "ShiftData.h"
#include "Tracker.h"

int main()
{
    Tracker tracker;

    // Create shifts
    ShiftData shiftOne(15, 20, 225, 23);
    ShiftData shiftTwo(8, 18, 150, 15);

    // Add shifts to tracker
    tracker.addShift(shiftOne);
    tracker.addShift(shiftTwo);

    std::cout << "Shift Tracker Created!" << std::endl;

    std::cout << "Total Shifts: "
              << tracker.getShiftCount() << std::endl;

    // Display earnings
    std::cout << "Shift One Earnings: $"
              << tracker.getShifts()[0].calculateEarnings()
              << std::endl;

    // Edit shift one
    ShiftData updatedShift(16, 20, 250, 25);
    tracker.editShift(0, updatedShift);

    // Delete shift two
    tracker.deleteShift(1);

    std::cout << "Updated Shift Count: "
              << tracker.getShiftCount() << std::endl;

    return 0;
}