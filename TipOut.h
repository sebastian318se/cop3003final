#ifndef COP3003FINAL_TIPOUT_H
#define COP3003FINAL_TIPOUT_H

#include <string>

class TipOut
{
public:
    //calculates tip out amount with sales
    virtual double calculateTipOut(double sales) const = 0;

    //returns name of method
    virtual std::string getType() const = 0;

    //returns what number gets stored from tip out method
    virtual double getValue() const = 0;

};


#endif //COP3003FINAL_TIPOUT_H