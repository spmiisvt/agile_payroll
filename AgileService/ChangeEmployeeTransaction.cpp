#include "ChangeEmployeeTransaction.h"


ChangeEmployeeTransaction::ChangeEmployeeTransaction(int empid)
	: itsEmpId(empid)
{
}

void ChangeEmployeeTransaction::Execute()
{
	Employee* e = GpayrollDatabase.GetEmployee(itsEmpId);
	if (e != 0) {
		Change(*e);
	}
}