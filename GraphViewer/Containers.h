#pragma once
#include <string>

#include "Config.h"

struct Error {
	std::string source = "";
	std::string message = "";

	Error(const std::string& source, const std::string& message) {
		this->source = source;
		this->message = message;
		return;
	}
};

