#pragma once

#include <map>


using namespace std;

class Employee;

class PayrollDatabase
{
public:
	virtual ~PayrollDatabase() {};
	PayrollDatabase() = default;

	Employee* GetEmployee(int empId);
	void AddEmployee(int empid, Employee*);
	void DeleteEmployee(int empid);

	void AddUnionMember(int memberId, Employee*);
	Employee* GetUnionMember(int memberId);
	void RemoveUnionMember(int memberId);

	void clear();

private:
	map<int, Employee*> itsEmployees;
	map<int, int> itsUnionMembers;
};
