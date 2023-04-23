#pragma once
#include "PaymentMethod.h"
#include "PayCheck.h"

#include <string>

using namespace std;

class MailMethod : public PaymentMethod
{
public:
    virtual ~MailMethod() {};
    MailMethod(string address);

    string GetAddress() const { return itsAddress; }

    void Pay(PayCheck&) override;

private:
    string itsAddress;
};