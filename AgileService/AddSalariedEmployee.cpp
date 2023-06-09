#include "AddSalariedEmployee.h"


AddSalariedEmployee::
AddSalariedEmployee(int empid, string name,
	string address, double salary)
	: AddEmployeeTransaction(empid, name, address)
	, itsSalary(salary)
{
}

PaymentClassification*
AddSalariedEmployee::GetClassification() const
{
	return new SalariedClassification(itsSalary);
}

PaymentSchedule* AddSalariedEmployee::GetSchedule() const
{
	return new MonthlySchedule();
}