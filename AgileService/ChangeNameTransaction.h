#pragma once

#include "ChangeEmployeeTransaction.h"
#include <string>

using namespace std;

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:
	virtual ~ChangeNameTransaction() {};
	ChangeNameTransaction(int empid, string name);
	virtual void Change(Employee&);
private:
	string itsName;
};