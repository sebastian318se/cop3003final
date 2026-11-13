//
// Created by Destiny Acuna on 11/12/26.
//

#include "FixedTipOut.h"
#include <stdexcept>
#include "Utilities.h"

//constructor
FixedTipOut::FixedTipOut(double fixedAmount)
{
    if (negative(fixedAmount)) {
        throw std:: invalid_argument("Tip amount cannot be negative");
    }

    amount = fixedAmount;
}

//return fixed dollar amount
double FixedTipOut::calculateTipOut(double sales) const
{
    return amount;
}

std::string FixedTipOut::getType() const
{
    return "Fixed";
}

double FixedTipOut::getValue() const
{
    return amount;
}
