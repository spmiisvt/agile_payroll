#pragma once

#include "Transaction.h"
#include "PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

class DeleteEmployeeTransaction : public Transaction
{
public:
	virtual ~DeleteEmployeeTransaction() {};
	DeleteEmployeeTransaction(int empid);

	virtual void Execute();
private:
	int itsEmpid;
};