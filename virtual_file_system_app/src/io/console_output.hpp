#pragma once

#include <string>

#include "i_output_handler.hpp"

class ConsoleOutput : public IOutputHandler {
public:
	void Print(const std::string& message) override;
	void PrintLine(const std::string& message) override;
	void RedrawInput(const std::string& prompt, const std::string& input, const std::string& sugggested) override;

private:
	void SetColor(int color);

};


