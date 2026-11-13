
#include <iostream>
#include <stdexcept>

#include "ShiftData.h"
#include "Tracker.h"
#include "TipOut.h"
#include "PercentTipOut.h"
#include "FixedTipOut.h"

int main()
{
    Tracker tracker;

    try {
        tracker.loadFromFile("shifts.txt");
    }
    //catch exception call it error tell me why
    catch (const std::exception&error) {
        std:: cout << "Loading error: " << error.what() << "\n";
    }

    return 0;
}