#include "AddCommissionedEmployee.h"


AddCommissionedEmployee::
AddCommissionedEmployee(int empid, string name, string address, double salary, double commissionRate)
	: AddEmployeeTransaction(empid, name, address)
	, itsSalary(salary)
	, itsCommissionRate(commissionRate)
{
}

PaymentClassification*
AddCommissionedEmployee::GetClassification() const
{
	return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule*
AddCommissionedEmployee::GetSchedule() const
{
	return new BiweeklySchedule();
}