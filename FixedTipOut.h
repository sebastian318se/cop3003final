//
// Created by Destiny Acuna on 11/12/26.
//

#ifndef COP3003FINAL_FIXEDTIPOUT_H
#define COP3003FINAL_FIXEDTIPOUT_H

#include "TipOut.h"

class FixedTipOut : public TipOut
{
private:
    double amount;
public:
    FixedTipOut(double fixedAmount);

    double calculateTipOut(double sales) const override;
};


#endif //COP3003FINAL_FIXEDTIPOUT_H