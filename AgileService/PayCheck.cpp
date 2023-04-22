#include "PayCheck.h"


PayCheck::PayCheck(Date payPeriodStartDate,
    Date payPeriodEndDate)
    : itsPayPeriodStartDate(payPeriodStartDate)
    , itsPayPeriodEndDate(payPeriodEndDate)
{
    itsGrossPay = 0;
    itsNetPay = 0;
    itsDeductions = 0;
}

void PayCheck::SetGrossPay(double grossPay)
{
    itsGrossPay = grossPay;
}

void PayCheck::SetNetPay(double netPay)
{
    itsNetPay = netPay;
}

void PayCheck::SetDeductions(double deductions)
{
    itsDeductions = deductions;
}

void PayCheck::SetField(const string& name, string value)
{
    itsFields[name] = std::move(value);
}

string PayCheck::GetField(const string& name)
{
    return itsFields[name];
}