#pragma once
#include <string>
#include <vector>
class Result;

class StepInfo
{

public:
	StepInfo(){}
	~StepInfo() {}

	std::string name;
	std::string className;
	std::vector<Result*> result;
};

class Result {
public:
	std::string value;
	std::string next;
	std::string returnVal;
};

