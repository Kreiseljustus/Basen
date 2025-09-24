#pragma once

#include <iostream>
#include <filesystem>

namespace Basen {
	void Init() {
		std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
	}
}