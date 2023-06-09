#include "TimeCardTransaction.h"


TimeCardTransaction::TimeCardTransaction(Date date,
	double hours,
	int empid)
	: itsDate(date)
	, itsHours(hours)
	, itsEmpid(empid)
{
}

void TimeCardTransaction::Execute()
{
	Employee* e = GpayrollDatabase.GetEmployee(itsEmpid);
	if (e) {
		PaymentClassification* pc = e->GetClassification();
		if (HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc)) {
			hc->AddTimeCard(new TimeCard(itsDate, itsHours));
		}
		else {
			throw("Tried to add timecard to non-hourly employee");
		}
	}
	else {
		throw("No such employee.");
	}
}