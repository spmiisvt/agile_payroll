#include "ChangeHoldTransaction.h"




ChangeHoldTransaction::ChangeHoldTransaction(int empId)
    : ChangeMethodTransaction(empId)
{
}

PaymentMethod* ChangeHoldTransaction::GetMethod() const
{
    return new HoldMethod();
}