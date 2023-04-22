#include "DeleteEmployeeTransaction.h"


DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empid)
	: itsEmpid(empid)
{
}

void DeleteEmployeeTransaction::Execute()
{
	GpayrollDatabase.DeleteEmployee(itsEmpid);
}