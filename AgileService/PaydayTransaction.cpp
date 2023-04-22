#include "PaydayTransaction.h"


PaydayTransaction::~PaydayTransaction() {
    for (auto& element : itsPaychecks)
    {
        delete element.second;
    }
    itsPaychecks.clear();
}

PaydayTransaction::PaydayTransaction(Date payDate)
    : itsPayDate(payDate)
{
}


void PaydayTransaction::Execute()
{
    list<int> empIds;
    GpayrollDatabase.GetAllEmployeeIds(empIds);

    for (auto i = empIds.begin(); i != empIds.end(); ++i)
    {
        int empId = *i;
        if (Employee* e = GpayrollDatabase.GetEmployee(empId))
        {
            if (e->IsPayDate(itsPayDate))
            {
                const auto pc = new PayCheck(e->GetPayPeriodStartDate(itsPayDate),
                    itsPayDate);
                itsPaychecks[empId] = pc;
                e->Payday(*pc);
            }
        }
    }
}

PayCheck* PaydayTransaction::GetPaycheck(int empId)
{
    return itsPaychecks[empId];
}

int PaydayTransaction::GetPaycheckCount() const
{
    return static_cast<int>(itsPaychecks.size());
}