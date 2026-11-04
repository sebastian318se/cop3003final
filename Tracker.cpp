#include "Tracker.h"

// Adds a new shift to the vector
void Tracker::addShift(const ShiftData& shift)
{
    shifts.push_back(shift);
}

// Edits an existing shift using its index
bool Tracker::editShift(int index, const ShiftData& shift)
{
    if (index < 0 || index >= shifts.size())
    {
        return false;
    }

    shifts[index] = shift;
    return true;
}

// Deletes a shift using its index
bool Tracker::deleteShift(int index)
{
    if (index < 0 || index >= shifts.size())
    {
        return false;
    }

    shifts.erase(shifts.begin() + index);
    return true;
}

// Returns the vector of shifts
const std::vector<ShiftData>& Tracker::getShifts() const
{
    return shifts;
}

// Returns the number of shifts
int Tracker::getShiftCount() const
{
    return shifts.size();
}