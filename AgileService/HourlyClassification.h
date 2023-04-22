#pragma once

#include "PaymentClassification.h"
#include "Date.h"
#include "TimeCard.h"
#include "PayCheck.h"
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

	double CalculatePay(PayCheck&) const override;

private:
	double itsRate;
	map<Date, TimeCard*> itsTimeCards;
	double CalculatePayForTimeCard(TimeCard*) const;
};