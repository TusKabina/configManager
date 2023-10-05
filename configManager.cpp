#include "configManager.hpp"
#include <iostream>
#include <fstream>


ConfigManager::ConfigManager::ConfigManager()
{
}

bool ConfigManager::ConfigManager::initialize()
{

	m_Deserializer = {
	{"intA", [this](const nlohmann::json& j) 
	{
		m_intA = j.get<int>();
	}},
		{"doubleB", [this](const nlohmann::json& j)
		{
			m_doubleB = j.get<double>();
		}},
			{"floatC", [this](const nlohmann::json& j)
			{
				m_floatC = j.get<float>();
			}},
				{"string", [this](const nlohmann::json& j)
				{
					m_str = j.get<std::string>();
				}},
	};
	return true;
}

ConfigManager::ConfigManager::ConfigManager(ConfigManager&& other) noexcept
{
	m_intA = std::exchange(other.m_intA, 0);
	m_doubleB = std::exchange(other.m_doubleB, 0.0);
	m_floatC = std::exchange(other.m_floatC, 0.0);
	m_str = std::move(other.m_str);
}

bool ConfigManager::ConfigManager::readConfig(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		return false;
	}
	nlohmann::json j = nlohmann::json::parse(ifs);

	for (const auto& [field, deserializer] : m_Deserializer)
	{
		if (!j.contains(field))
		{
			return false;
		}
		deserializer(j[field]);

	}
	return true;
}
