#pragma once
#include "PaymentMethod.h"
#include "PayCheck.h"

#include <string>

using namespace std;

class DirectMethod : public PaymentMethod
{
public:
    virtual ~DirectMethod() {};
    DirectMethod(string bank, string account);


    string GetBank() const { return itsBank; }
    string GetAccount() const { return itsAccount; }

    void Pay(PayCheck&) override;

private:
    string itsBank;
    string itsAccount;
};