#include "PayrollDatabase.h"

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
	itsUnionMembers.clear();
}
void PayrollDatabase::AddUnionMember(int memberId, Employee* e)
{
	itsUnionMembers[memberId] = e->GetEmpId();
}

void PayrollDatabase::RemoveUnionMember(int memberId)
{
	itsUnionMembers.erase(memberId);
}

Employee* PayrollDatabase::GetUnionMember(int memberId)
{
	return PayrollDatabase::GetEmployee(itsUnionMembers[memberId]);
}