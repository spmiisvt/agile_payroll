#include "ServiceChargeTransaction.h"


ServiceChargeTransaction::
ServiceChargeTransaction(int memberId, Date date, double charge)
	: itsMemberId(memberId)
	, itsDate(date)
	, itsCharge(charge)
{
}

void ServiceChargeTransaction::Execute()
{
	Employee* e = GpayrollDatabase.GetUnionMember(itsMemberId);
	Affiliation* af = e->GetAffiliation();
	if (UnionAffiliation* uaf = dynamic_cast<UnionAffiliation*>(af)) {
		uaf->AddServiceCharge(itsDate, itsCharge);
	}
}