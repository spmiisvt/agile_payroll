#pragma once

#include "Transaction.h"
#include "Date.h"
#include "Employee.h"
#include "ServiceCharge.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"
#include "Affiliation.h"

class ServiceChargeTransaction : public Transaction
{
public:
	virtual ~ServiceChargeTransaction() {};
	ServiceChargeTransaction(int memberId, Date date, double charge);

	virtual void Execute();
private:
	int itsMemberId;
	Date itsDate;
	double itsCharge;
};