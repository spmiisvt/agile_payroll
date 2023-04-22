#pragma once

#include "ChangeEmployeeTransaction.h"

class ChangeAffiliationTransaction : public ChangeEmployeeTransaction
{
public:
	virtual ~ChangeAffiliationTransaction() {};
	ChangeAffiliationTransaction(int empid);

	virtual Affiliation* GetAffiliation() const = 0;
	virtual void RecordMembership(Employee*) = 0;
	virtual void Change(Employee&);
};