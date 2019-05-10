// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Parser.h"
#include "Step.h"

Step* getStepObject(std::string name) {

	return new Step(name);
}

std::string getNextStep(std::string value, StepInfo* stepInfo) {

	std::vector<Result*> results = stepInfo->result;
	for (auto result : results) {
		if (result->value.compare(value) == 0) {
			if (value == "FLOW_END") {
				return result->returnVal;
			} else {
				return result->next;
			}
		}
	}
}

StepInfo* getStepByName(std::string name, std::vector<StepInfo*> flow) {

	for (auto step : flow) {
		if (step->name == name)
			return step;
	}
	return nullptr;
}

int main(void)
{

	Parser parser;

	std::vector<StepInfo*> flow = parser.parse("void_flow.xml");
	StepInfo* stepInfo = flow[0];
	std::string result = "FLOW_END";
	std::string name = stepInfo->name;
	std::cout << "Flow Size: " << flow.size() << std::endl;
	std::cout << "Step Execution: " << std::endl;
	do {
		std::cout << "Step: " + name << std::endl;
		Step* step = getStepObject(name);
		std::string result = step->execute();
		
		name = getNextStep(result, stepInfo);
		stepInfo = getStepByName(name, flow);
	} while (name != "FLOW_END");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
