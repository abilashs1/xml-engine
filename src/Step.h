#pragma once
class Step
{
public:
	Step(std::string nam) {
		name = nam;
	}
	~Step() {

	}

	std::string name;

	std::string execute() {
		return "success";
	}
};

