#include "PercentTipOut.h"
#include <stdexcept>

PercentTipOut::PercentTipOut(double tipRate)
{
    if (tipRate < 0 || tipRate > 100) {
        throw std::invalid_argument ("Rate must be between 0-100%");
    }

    rate = tipRate;
}

double PercentTipOut::calculateTipOut(double sales) const
{
    if (negative(sales)) {
        throw std::invalid_argument("Sales cannot be negative");
    }
    return sales * (rate / 100.0);

}
