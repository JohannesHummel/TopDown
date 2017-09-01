#pragma once
#include <string>
class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();
 std::string readFromFile(std::string const& filename);
};

