#pragma once

#include "ChangeMethodTransaction.h"
#include "MailMethod.h"
#include <string>

using namespace std;

class ChangeMailTransaction : public ChangeMethodTransaction
{
public:
    virtual ~ChangeMailTransaction() {};
    ChangeMailTransaction(int empId, string address);

    PaymentMethod* GetMethod() const override;
private:
    string itsAddress;
};