#include "ChangeDirectTransaction.h"


ChangeDirectTransaction::ChangeDirectTransaction(int empId, string bank, string account)
    : ChangeMethodTransaction(empId)
    , itsBank(bank)
    , itsAccount(account)
{
}

PaymentMethod* ChangeDirectTransaction::GetMethod() const
{
    return new DirectMethod(itsBank, itsAccount);
}