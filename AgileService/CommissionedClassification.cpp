#include "CommissionedClassification.h"

#include <string>

using namespace std;

CommissionedClassification::~CommissionedClassification()
{
}

CommissionedClassification::CommissionedClassification(double salary, double commissionRate)
	: itsSalary(salary)
	, itsCommissionRate(commissionRate)
{
}
double CommissionedClassification::GetSalary() const {
	return itsSalary;
}

double CommissionedClassification::GetRate() const {
	return itsCommissionRate;
}