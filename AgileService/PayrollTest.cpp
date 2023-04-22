#include "gtest/gtest.h"

#include "AddSalariedEmployee.h"
#include "PayrollDatabase.h"
#include "Employee.h"
#include "SalariedClassification.h"
#include "HoldMethod.h"
#include "MonthlySchedule.h"

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