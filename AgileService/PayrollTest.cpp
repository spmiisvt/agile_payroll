#include "gtest/gtest.h"

#include "AddSalariedEmployee.h"
#include "PayrollDatabase.h"
#include "Employee.h"
#include "SalariedClassification.h"
#include "HoldMethod.h"
#include "MonthlySchedule.h"
#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

extern PayrollDatabase GpayrollDatabase;

TEST(PayrollTest, TestAddSalariedEmployee)
{
	GpayrollDatabase.clear();
	const int empId = 1;
	AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Bob" == e->GetName());
	PaymentClassification* pc = e->GetClassification();
	SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
	ASSERT_TRUE(sc);

	ASSERT_DOUBLE_EQ(1000.00, sc->GetSalary(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
	ASSERT_TRUE(ms);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
TEST(PayrollTest, TestAddHourlyEmployee)
{
	GpayrollDatabase.clear();
	int empId = 2;
	AddHourlyEmployee t(empId, "Sam", "Home", 15.25);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Sam" == e->GetName());

	PaymentClassification* pc = e->GetClassification();
	HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
	ASSERT_TRUE(hc);
	ASSERT_DOUBLE_EQ(15.25, hc->GetRate(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
	ASSERT_TRUE(ws);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
TEST(PayrollTest, TestAddCommissionedEmployee)
{
	GpayrollDatabase.clear();
	int empId = 3;
	AddCommissionedEmployee t(empId, "Miller", "Home", 2400, 1.7);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Miller" == e->GetName());

	PaymentClassification* pc = e->GetClassification();
	CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
	ASSERT_TRUE(cc);
	ASSERT_DOUBLE_EQ(2400, cc->GetSalary(), 0.01);
	ASSERT_DOUBLE_EQ(1.7, cc->GetRate(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	BiweeklySchedule* bws = dynamic_cast<BiweeklySchedule*>(ps);
	ASSERT_TRUE(bws);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
