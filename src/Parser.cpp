#include "pch.h"
#include "Parser.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>

Parser::Parser()
{
}


Parser::~Parser()
{

}

std::vector<Result*> Parser::getResult(rapidxml::xml_node<> *step_node) {

	std::vector<Result*> results;
	// Interate over the results	
	for (rapidxml::xml_node<> * result_node = step_node->first_node("result"); result_node; result_node = result_node->next_sibling())
	{
		Result* result = new Result;
		std::cout << "Result" << std::endl;
		if (result_node->first_attribute("value"))
			result->value = result_node->first_attribute("value")->value();
		if (result_node->first_attribute("next"))
			result->next = result_node->first_attribute("next")->value();
		if (result_node->first_attribute("return"))
			result->returnVal = result_node->first_attribute("return")->value();

		std::cout << "value: " + result->value << std::endl <<
			"next : " + result->next << std::endl <<
			"return: " + result->returnVal << std::endl;;
		results.push_back(result);
	}
	return results;
}

std::vector<StepInfo*> Parser::parse(const std::string & fileName)
{
	std::cout << "Parsing my flow" << std::endl;
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile(fileName);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node 
	root_node = doc.first_node("Steps");
	// Iterate over the steps
	std::vector<StepInfo*> steps;

	for (rapidxml::xml_node<> * step_node = root_node->first_node("step"); step_node; step_node = step_node->next_sibling())
	{
		StepInfo* step = new StepInfo;

		std::cout << "Step Start" << std::endl;
		if (step_node->first_attribute("name"))
			step->name = step_node->first_attribute("name")->value();
		if (step_node->first_attribute("class"))
			step->className = step_node->first_attribute("class")->value();

		std::cout << "Step Name: " + step->name << std::endl;
		std::cout << "Class: : " + step->className << std::endl;

		step->result = getResult(step_node);
		std::cout << std::endl;
		std::cout << "Result Count: : " << step->result.size() << std::endl;
		if (!step->name.empty())
			steps.push_back(step);
	}
	std::cout << "Step Count: : " << steps.size()<< std::endl;
	return steps;
}
