#pragma once
#include <map>
#include <vector>

class Result;
class Step;

class FlowFactory
{
public:
	FlowFactory();
	~FlowFactory();
private:
	std::map <Step*, std::vector<Result*>> flow;
};

