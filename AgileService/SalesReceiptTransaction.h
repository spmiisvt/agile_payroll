#pragma once

#include "Transaction.h"
#include "Date.h"

class SalesReceiptTransaction : public Transaction
{
public:
	virtual ~SalesReceiptTransaction() {};
	SalesReceiptTransaction(Date date, double amount, int empid);

	virtual void Execute();
public:
	int itsEmpid;
	Date itsDate;
	double itsAmount;
};