#pragma once
#include "PaymentClassification.h"

#include <map>

using namespace std;

class CommissionedClassification : public PaymentClassification
{
public:
	virtual ~CommissionedClassification();
	CommissionedClassification(double salary, double commissionRate);

	double GetSalary() const;
	double GetRate() const;

private:
	double itsSalary;
	double itsCommissionRate;
	
};