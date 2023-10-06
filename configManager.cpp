#include "configManager.hpp"



ConfigManager::ConfigManager::ConfigManager()
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
}

ConfigManager::ConfigManager::ConfigManager(ConfigManager&& other) noexcept
{
	m_intA = std::exchange(other.m_intA, 0);
	m_doubleB = std::exchange(other.m_doubleB, 0.0);
	m_floatC = std::exchange(other.m_floatC, 0.0);
	m_str = std::move(other.m_str);
}

bool ConfigManager::ConfigManager::serialize(const std::string& filePath)
{
	nlohmann::ordered_json j = *this;
	std::ofstream ofs(filePath);
	if (!ofs.is_open())
	{
		return false;
	}
	ofs << j.dump(4);

	ofs.close();
	return true;
}

bool ConfigManager::ConfigManager::readConfig(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	nlohmann::ordered_json j;
	if (!ifs.is_open())
	{
		return false;
	}
	try
	{
		j = nlohmann::ordered_json::parse(ifs);
	}
	catch (const nlohmann::json::exception& ex)
	{
		std::cout << ex.what();
		ifs.close();
		return false;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error: " << ex.what();
		ifs.close();
		return false;
	}
	catch (...)
	{
		std::cout << "error";
		ifs.close();
		return false;
	}
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

void ConfigManager::to_json(nlohmann::ordered_json& j, const ConfigManager& cfg)
{
	j = nlohmann::ordered_json
	{
		{"intA",cfg.m_intA},
		{"doubleB",cfg.m_doubleB},
		{"floatC",cfg.m_floatC},
		{"string",cfg.m_str}
	};
}
