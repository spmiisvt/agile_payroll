#pragma once

#include "PaymentClassification.h"
#include "Date.h"
#include "TimeCard.h"
#include <map>;
using namespace std;




class HourlyClassification : public PaymentClassification
{
public:
	~HourlyClassification();
	HourlyClassification(double hourlyRate);

	double GetRate() const { return itsRate; }

	void AddTimeCard(TimeCard* tc);
	TimeCard* GetTimeCard(const Date& date);

private:
	double itsRate;
	map<Date, TimeCard*> itsTimeCards;
};