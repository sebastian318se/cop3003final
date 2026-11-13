//
// Created by Destiny Acuna on 11/12/26.
//

#include "FixedTipOut.h"
#include <stdexcept>

//constructor
FixedTipOut::FixedTipOut(double fixedAmount)
{
    if (fixedAmount < 0) {
        throw std:: invalid_argument("Tip amount cannot be negative");
    }

    amount = fixedAmount;
}

//return fixed dollar amount
double FixedTipOut::calculateTipOut(double sales) const
{
    return amount;
}
