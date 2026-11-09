
#include <iostream>
#include <stdexcept>

#include "ShiftData.h"
#include "OvertimeShift.h"
#include "Tracker.h"

int main()
{
    Tracker tracker;

    std::cout << "=================================\n";
    std::cout << "       SHIFT TRACKER SYSTEM\n";
    std::cout << "=================================\n";

    // Create regular shifts
    ShiftData shiftOne(5, 20, 100, 10);
    ShiftData shiftTwo(6, 18, 80, 15);

    // Create an overtime shift
    OvertimeShift shiftThree(10, 20, 150, 20);

    // Add shifts to tracker
    tracker.addShift(shiftOne);
    tracker.addShift(shiftTwo);
    tracker.addShift(shiftThree);

    //test negative shift hours are denied
    try {
        ShiftData testValidation(-200,30,20,10);
    }
    catch (const std::invalid_argument&error) {
        std::cout << error.what() << '\n';
    }


    std::cout << "\nShifts successfully added!\n";

    std::cout << "Total Shifts: "
              << tracker.getShiftCount() << std::endl;

    // Demonstrate runtime polymorphism
    std::cout << "\n===== RUNTIME POLYMORPHISM =====\n";

    const ShiftData& regularReference = tracker.getShift(0);
    const ShiftData& overtimeReference = tracker.getShift(2);

    std::cout << regularReference.getShiftType()
              << " Earnings: $"
              << regularReference.calculateEarnings()
              << std::endl;

    std::cout << overtimeReference.getShiftType()
              << " Earnings: $"
              << overtimeReference.calculateEarnings()
              << std::endl;

    // Display all shifts
    std::cout << "\n===== ALL SHIFT INFORMATION =====\n";

    tracker.displayShifts();

    // Display total earnings
    std::cout << "\nTotal Earnings: $"
              << tracker.getTotalEarnings()
              << std::endl;

    // Edit a shift
    std::cout << "\n===== EDITING A SHIFT =====\n";

    ShiftData updatedShift(7, 22, 120, 15);

    try
    {
        tracker.editShift(0, updatedShift);

        std::cout << "Shift successfully updated!\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

    // Demonstrate invalid operation and recovery
    std::cout << "\n===== INVALID OPERATION TEST =====\n";

    int originalCount = tracker.getShiftCount();
    double originalEarnings = tracker.getTotalEarnings();

    try
    {
        std::cout << "Attempting to edit an invalid shift...\n";

        tracker.editShift(99, updatedShift);
    }
    catch (const std::out_of_range& error)
    {
        std::cout << "Exception caught: "
                  << error.what() << std::endl;

        std::cout << "The tracker recovered successfully!\n";
    }

    // Verify existing information was preserved
    std::cout << "\n===== DATA PRESERVATION CHECK =====\n";

    std::cout << "Original Shift Count: "
              << originalCount << std::endl;

    std::cout << "Current Shift Count: "
              << tracker.getShiftCount() << std::endl;

    std::cout << "Original Earnings: $"
              << originalEarnings << std::endl;

    std::cout << "Current Earnings: $"
              << tracker.getTotalEarnings() << std::endl;

    // Continue using tracker after exception
    std::cout << "\n===== CONTINUED USE =====\n";

    ShiftData newShift(4, 25, 60, 5);

    tracker.addShift(newShift);

    std::cout << "A new shift was successfully added after the error!\n";

    // Delete a shift
    tracker.deleteShift(1);

    std::cout << "Another shift was successfully deleted!\n";

    // Final results
    std::cout << "\n===== FINAL TRACKER RESULTS =====\n";

    tracker.displayShifts();

    std::cout << "\nFinal Shift Count: "
              << tracker.getShiftCount() << std::endl;

    std::cout << "Final Total Earnings: $"
              << tracker.getTotalEarnings() << std::endl;

    std::cout << "\nShift Tracker completed successfully!\n";

    return 0;
}
