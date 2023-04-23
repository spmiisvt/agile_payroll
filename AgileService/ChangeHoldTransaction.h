#pragma once

#include "ChangeMethodTransaction.h"
#include "HoldMethod.h"

class ChangeHoldTransaction : public ChangeMethodTransaction
{
public:
    virtual ~ChangeHoldTransaction() {};
    ChangeHoldTransaction(int empId);

    PaymentMethod* GetMethod() const override;
};