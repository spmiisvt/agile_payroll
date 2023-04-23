#include "ChangeMailTransaction.h"


ChangeMailTransaction::ChangeMailTransaction(int empId, string address)
    : ChangeMethodTransaction(empId)
    , itsAddress(address)
{
}

PaymentMethod* ChangeMailTransaction::GetMethod() const
{
    return new MailMethod(itsAddress);
}