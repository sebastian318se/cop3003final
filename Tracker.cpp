
#include "Tracker.h"
#include <iostream>
#include <stdexcept>
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include "PercentTipOut.h"
#include "FixedTipOut.h"

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
    if (negative(index) || index >= static_cast<int>(shifts.size()))
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

// Saves all the shifts in tracker
void Tracker::saveInFile(const std::string &fileName) const
{
    std::ofstream file(fileName);

    if (!file) {
        throw std::runtime_error("Failed to open file.");
    }

    //loop to go through every stored shift
    for (int i = 0; i < getShiftCount(); i++) {

        //grab current shift
        const ShiftData& shift = getShift(i);

        //save all the information
        file << shift.getHours() << ","
        << shift.getHourlyWage() << ","
        << shift.getTips() << ","
        << shift.getSales() << ","
        << shift.getTipOutType() << ","
        << shift.getTipOutValue() << std:: endl;
    }
}

//load saved shifts
void Tracker::loadFromFile(const std::string &fileName)
{
    std::ifstream loadFile(fileName);

    if (!loadFile) {
        throw std::runtime_error("Could not load file");
    }

    //temporarily hold one line from the file
    std::string line;

    //read one full line until none left
    while (std::getline(loadFile, line)) {
        std::stringstream lineStream(line);

        //temporarily hold values to read
        std::string hoursText;
        std::string wageText;
        std::string tipsText;
        std::string salesText;
        std::string tipType;
        std::string tipValueText;

        std::getline(lineStream, hoursText, ',');
        std::getline(lineStream, wageText, ',');
        std::getline(lineStream, tipsText, ',');
        std::getline(lineStream, salesText, ',');
        std::getline(lineStream, tipType, ',');
        std::getline(lineStream, tipValueText, ',');

        //stod means string to double
        //convert text values into numbers
        double hours = std::stod(hoursText);
        double wage = std::stod(wageText);
        double tips = std::stod(tipsText);
        double sales = std::stod(salesText);
        double tipValue = std::stod(tipValueText);

        //holds whatever tip out type used
        std::shared_ptr<TipOut> tipOutType;

        //builds a PercentTipOut object
        if (tipType == "Percent") {
            tipOutType =
                std::make_shared<PercentTipOut>(tipValue);
        }
        //builds a FixedTipOut object
        else if (tipType == "Fixed") {
            tipOutType =
                std::make_shared<FixedTipOut>(tipValue);
        }

        //validation rejects anything else
        else {
            throw std::runtime_error("Not valid tip out type");
        }

        ShiftData loadedShift(hours, wage, tips, sales, tipOutType);

        addShift(loadedShift);
    }

}

void Tracker::addShift(double hours, double hourlyWage, double tips,
    double sales, std::shared_ptr<TipOut> tipOutType)
{
    ShiftData newShift(hours, hourlyWage, tips, sales, tipOutType);

    addShift(newShift);
}
