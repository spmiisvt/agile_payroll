#include "HourlyClassification.h"


HourlyClassification::~HourlyClassification()
{
    for (auto& tc : itsTimeCards)
    {
        delete tc.second;
    }
    itsTimeCards.clear();
}

HourlyClassification::HourlyClassification(double hourlyRate)
	: itsRate(hourlyRate)
{
}

void HourlyClassification::AddTimeCard(TimeCard* tc) {
	itsTimeCards[tc->GetDate()] = tc;
}

TimeCard* HourlyClassification::GetTimeCard(const Date& date)
{
    return itsTimeCards[date];
}