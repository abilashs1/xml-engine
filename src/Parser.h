#pragma once
#include <string>
#include "StepInfo.h"
#include "rapidxml/rapidxml.hpp"

class StepInfo;

class Parser
{
public:
	Parser();
	~Parser();

	std::vector<StepInfo*> parse(const std::string& fileName);
	std::vector<Result*> getResult(rapidxml::xml_node<> *step_node);
};

