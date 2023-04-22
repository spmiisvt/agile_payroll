#pragma once
#include "Date.h"
#include <map>
#include <string>

using namespace std;

class PayCheck
{
public:
    virtual ~PayCheck() {};
    PayCheck(Date payPeriodStart, Date payPeriodEnd);


    void SetGrossPay(double grossPay);
    void SetDeductions(double deductions);
    void SetNetPay(double netPay);

    double GetGrossPay() const { return itsGrossPay; }
    double GetDeductions() const { return itsDeductions; }
    double GetNetPay() const { return itsNetPay; }

    Date GetPayPeriodEndDate() const { return itsPayPeriodEndDate; }
    Date GetPayPeriodStartDate() const { return itsPayPeriodStartDate; }
    void SetField(const string& name, string value);
    string GetField(const string& name);

private:
    Date itsPayPeriodStartDate;
    Date itsPayPeriodEndDate;
    double itsGrossPay{ 0 };
    double itsNetPay{ 0 };
    double itsDeductions{ 0 };
    map<string, string> itsFields;
};