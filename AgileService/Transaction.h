#pragma once

class Transaction
{
public:
	virtual ~Transaction() {};
	Transaction() {};

	virtual void Execute() = 0;
};
