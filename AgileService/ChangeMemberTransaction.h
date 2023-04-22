#pragma once

#include "ChangeAffiliationTransaction.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

class ChangeMemberTransaction : public ChangeAffiliationTransaction
{
public:
	virtual ~ChangeMemberTransaction() {};
	ChangeMemberTransaction(int empid, int memberid, double dues);

	virtual Affiliation* GetAffiliation() const;
	virtual void RecordMembership(Employee*);
private:
	int itsMemberId;
	double itsDues;
};