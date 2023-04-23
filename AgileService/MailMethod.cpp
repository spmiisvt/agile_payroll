#include "MailMethod.h"


MailMethod::MailMethod(string address)
    : itsAddress(address)
{
}

void MailMethod::Pay(PayCheck& pc)
{
    pc.SetField("Disposition", "Mail");
}