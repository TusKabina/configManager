#include "configManager.hpp"
#include <iostream>



auto main() -> int
{
	ConfigManager::ConfigManager cfg;
	char filePath[35] = { "C:/Users/ivanr/Documents/file.json" };
	
	if (!cfg.readConfig("C:/Users/ivanr/Documents/file.json"))
	{
		std::cout << "Error!\n";
		return 1;
	}
	std::cout << cfg.m_intA << std::endl;
	std::cout << cfg.m_doubleB << std::endl;
	std::cout << cfg.m_floatC << std::endl;
	std::cout << cfg.m_str << std::endl;

	cfg.m_intA = 876;
	cfg.m_doubleB = 321.321;
	cfg.m_floatC = 1.2f;
	cfg.m_str = "Hello!";
	cfg.serialize(filePath);


}
