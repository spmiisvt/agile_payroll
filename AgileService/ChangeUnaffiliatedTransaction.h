#pragma once
#include "ChangeAffiliationTransaction.h"
#include "NoAffiliation.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
public:
	virtual ~ChangeUnaffiliatedTransaction() {};
	ChangeUnaffiliatedTransaction(int empId);
	virtual Affiliation* GetAffiliation() const;
	virtual void RecordMembership(Employee*);
};