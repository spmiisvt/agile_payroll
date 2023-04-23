#include "DirectMethod.h"


DirectMethod::DirectMethod(string bank, string account)
    : itsBank(bank)
    , itsAccount(account)
{
}

void DirectMethod::Pay(PayCheck& pc)
{
    pc.SetField("Disposition", "Direct");
}