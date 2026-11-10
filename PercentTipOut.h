#include "TipOut.h"

#ifndef COP3003FINAL_PercentTipOut_H
#define COP3003FINAL_PercentTipOut_H


class PercentTipOut : public TipOut
{
private:
    double rate;
public:
    PercentTipOut(double tipRate);

    double calculateTipOut(double sales) const override;
};
#endif //COP3003FINAL_PERCENTAGECALCULATOR_H