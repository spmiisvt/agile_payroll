#include "PayrollDatabase.h"
#include "Employee.h"

PayrollDatabase GpayrollDatabase;

Employee* PayrollDatabase::GetEmployee(int empid)
{
	return itsEmployees[empid];
}

void PayrollDatabase::AddEmployee(int empid, Employee* e)
{
	itsEmployees[empid] = e;
}
void PayrollDatabase::DeleteEmployee(int empid) {
	itsEmployees.erase(empid);
}

void PayrollDatabase::clear()
{
	for (auto& employee : itsEmployees)
	{
		delete employee.second;
	}
	itsEmployees.clear();
}