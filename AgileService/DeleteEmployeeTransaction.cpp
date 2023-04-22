#include "DeleteEmployeeTransaction.h"
#include "PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empid)
	: itsEmpid(empid)
{
}

void DeleteEmployeeTransaction::Execute()
{
	GpayrollDatabase.DeleteEmployee(itsEmpid);
}