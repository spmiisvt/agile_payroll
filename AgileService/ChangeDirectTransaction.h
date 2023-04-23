#pragma once

#include "ChangeMethodTransaction.h"
#include "DirectMethod.h"
#include <string>

using namespace std;

class ChangeDirectTransaction : public ChangeMethodTransaction
{
public:
    virtual ~ChangeDirectTransaction() {};
    ChangeDirectTransaction(int empId, string bank, string account);

    PaymentMethod* GetMethod() const override;
private:
    string itsBank;
    string itsAccount;
};