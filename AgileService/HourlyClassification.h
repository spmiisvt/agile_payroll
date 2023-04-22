#pragma once
#include "PaymentClassification.h"

#include <map>;
using namespace std;




class HourlyClassification : public PaymentClassification
{
public:
	~HourlyClassification();
	HourlyClassification(double hourlyRate);

	double GetRate() const { return itsRate; }


private:
	double itsRate;

};