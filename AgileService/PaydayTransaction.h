#pragma once
#include "Transaction.h"
#include "PayCheck.h"
#include "Date.h"
#include "PayrollDatabase.h"
#include "Employee.h"

#include <map>
#include <list>

using namespace std;

extern PayrollDatabase GpayrollDatabase;

class PaydayTransaction : public Transaction
{
public:
    ~PaydayTransaction() override;
    PaydayTransaction(Date payDate);

    void Execute() override;
    PayCheck* GetPaycheck(int empId);
    int GetPaycheckCount() const;

private:
    Date itsPayDate;
    map<int, PayCheck*> itsPaychecks;
};