
#include "Tracker.h"
#include <iostream>
#include <stdexcept>

// Adds a copy of a shift to the tracker
void Tracker::addShift(const ShiftData& shift)
{
    shifts.push_back(shift.clone());
}

// Edits an existing shift
void Tracker::editShift(int index, const ShiftData& shift)
{
    if (index < 0 || index >= static_cast<int>(shifts.size()))
    {
        throw std::out_of_range("Invalid shift index for editing.");
    }

    // Clone first, then replace the existing shift.
    // Existing data remains intact if cloning fails.
    std::unique_ptr<ShiftData> updatedShift = shift.clone();
    shifts[index] = std::move(updatedShift);
}

// Deletes an existing shift
void Tracker::deleteShift(int index)
{
    if (index < 0 || index >= static_cast<int>(shifts.size()))
    {
        throw std::out_of_range("Invalid shift index for deletion.");
    }

    shifts.erase(shifts.begin() + index);
}

// Returns a shift using a base-class reference
const ShiftData& Tracker::getShift(int index) const
{
    if (index < 0 || index >= static_cast<int>(shifts.size()))
    {
        throw std::out_of_range("Invalid shift index.");
    }

    return *shifts[index];
}

// Returns the number of shifts
int Tracker::getShiftCount() const
{
    return static_cast<int>(shifts.size());
}

// Calculates earnings from all shifts
double Tracker::getTotalEarnings() const
{
    double total = 0;

    for (const auto& shift : shifts)
    {
        total += shift->calculateEarnings();
    }

    return total;
}

// Displays every shift
void Tracker::displayShifts() const
{
    for (int i = 0; i < getShiftCount(); i++)
    {
        const ShiftData& shift = getShift(i);

        std::cout << "\nShift " << i + 1 << std::endl;

        std::cout << "Type: "
                  << shift.getShiftType() << std::endl;

        std::cout << "Earnings: $"
                  << shift.calculateEarnings() << std::endl;

        std::cout << "Hourly Average: $"
                  << shift.calculateHourly() << std::endl;
    }
}
