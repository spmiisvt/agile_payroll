#pragma once

#include "ChangeEmployeeTransaction.h"

class PaymentMethod;

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
public:
    virtual ~ChangeMethodTransaction() {};
    ChangeMethodTransaction(int empId);

    virtual PaymentMethod* GetMethod() const = 0;
    void Change(Employee&) override;
};