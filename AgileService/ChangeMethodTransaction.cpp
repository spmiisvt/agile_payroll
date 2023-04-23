#include "ChangeMethodTransaction.h"



ChangeMethodTransaction::ChangeMethodTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
}

void ChangeMethodTransaction::Change(Employee& e)
{
    e.SetMethod(GetMethod());
}