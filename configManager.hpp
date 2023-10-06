#pragma once
#include "json.hpp"
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

namespace ConfigManager
{
	class ConfigManager
	{
		public:
			using deserializer = std::function<void(const nlohmann::json&)>;

			std::map<std::string, deserializer> m_Deserializer;

			int m_intA{};
			double m_doubleB{};
			float m_floatC{};
			std::string m_str{};
		public:
			ConfigManager();
			ConfigManager(ConfigManager&& other) noexcept;

			bool readConfig(const std::string& filePath);

			template<typename T>
			bool writeConfig(const std::string& filePath, const std::string& field, const T& value)
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
					std::cout << "Exception while trying to parse the json file: " << ex.what() << '\n';
					ifs.close();
					return false;
				}
				catch (const std::exception& ex)
				{
					std::cout << "Exception while trying to parse the json file: " << ex.what() << '\n';
					ifs.close();
					return false;
				}
				catch (...)
				{
					std::cout << "Unexpected error has occurred while trying to parse json file.\n";
					ifs.close();
					return false;
				}

				if (!j.contains(field))
				{
					std::cout << "Error: field: '" << field << "'." << " Does not exist!\n";
					return false;
				}
				j[field] = value;
				std::ofstream ofs(filePath);
				if (!ofs.is_open())
				{
					return false;
				}
				ofs << j.dump(4);

				ofs.close();
				return true;
			}
			bool serialize(const std::string& filePath);

			
	};

	void to_json(nlohmann::ordered_json& j, const ConfigManager& cfg);
}