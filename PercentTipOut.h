#ifndef COP3003FINAL_PercentTipOut_H
#define COP3003FINAL_PercentTipOut_H

#include "TipOut.h"
#include "Utilities.h"

class PercentTipOut : public TipOut
{
private:
    double rate;
public:
    PercentTipOut(double tipRate);

    double calculateTipOut(double sales) const override;

    std::string getType() const override;

    double getValue() const override;
};
#endif //COP3003FINAL_PERCENTAGECALCULATOR_H