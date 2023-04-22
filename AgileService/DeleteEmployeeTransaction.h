#pragma once

#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
public:
	virtual ~DeleteEmployeeTransaction() {};
	DeleteEmployeeTransaction(int empid);

	virtual void Execute();
private:
	int itsEmpid;
};