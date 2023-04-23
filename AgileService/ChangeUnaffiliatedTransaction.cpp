#include "ChangeUnaffiliatedTransaction.h"

ChangeUnaffiliatedTransaction::ChangeUnaffiliatedTransaction(int empId)
	: ChangeAffiliationTransaction(empId)
{
}

Affiliation* ChangeUnaffiliatedTransaction::GetAffiliation() const
{
	return new NoAffiliation();
}

void ChangeUnaffiliatedTransaction::RecordMembership(Employee* e)
{
	Affiliation* af = e->GetAffiliation();
	if (UnionAffiliation* uf = dynamic_cast<UnionAffiliation*>(af))
	{
		int memberId = uf->GetMemberId();
		GpayrollDatabase.RemoveUnionMember(memberId);
	}
}