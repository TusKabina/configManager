#pragma once
#include "json.hpp"
#include <string>
#include <fstream>

namespace ConfigManager
{
	class ConfigManager
	{
		public:
			using deserializer = std::function<void(const nlohmann::json&)>;

			std::map<std::string, deserializer> m_Deserializer;

			int m_intA;
			double m_doubleB;
			float m_floatC;
			std::string m_str{};
		public:
			ConfigManager();
			bool initialize();
			ConfigManager(ConfigManager&& other) noexcept;

			bool readConfig(const std::string& filePath);

			template<typename T>
			bool writeConfig(const std::string& filePath, const std::string& field, const T& value)
			{
				std::ifstream ifs(filePath);
				nlohmann::json j = nlohmann::json::parse(ifs);
				ifs.close();

				if (!j.contains(field))
				{
					return false;
				}
				j[field] = value;

				std::ofstream ofs(filePath);
				ofs << j.dump(4);
				ofs.close();

			}

			
	};
}