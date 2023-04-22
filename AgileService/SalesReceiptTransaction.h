#pragma once

#include "Transaction.h"
#include "Date.h"
#include "Employee.h"
#include "PayrollDatabase.h"
#include "CommissionedClassification.h"
#include "SalesReceipt.h"

extern PayrollDatabase GpayrollDatabase;

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