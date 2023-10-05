#include "configManager.hpp"
#include <iostream>



int main()
{
	ConfigManager::ConfigManager cfg;
	cfg.initialize();
	cfg.readConfig("C:/Users/ivanr/Documents/file.json");

	std::cout << cfg.m_intA << std::endl;
	std::cout << cfg.m_doubleB << std::endl;
	std::cout << cfg.m_floatC << std::endl;
	std::cout << cfg.m_str << std::endl;

	cfg.writeConfig("C:/Users/ivanr/Documents/file.json","intA",10);

	std::cout << cfg.m_intA << std::endl;


}