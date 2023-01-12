#include "../aboo/config.h"
#include "../aboo/log.h"
#include <yaml-cpp/yaml.h>
#include "../aboo/env.h"
#include <iostream>

aboo::ConfigVar<int>::ptr g_int_value_config = aboo::Config::Lookup("system.port", (int)8080, "system port");
aboo::ConfigVar<float>::ptr g_int_valuex_config = aboo::Config::Lookup("system.port", (float)8080, "system port");
aboo::ConfigVar<float>::ptr g_float_value_config = aboo::Config::Lookup("system.value", (float)10.2f, "system value");
aboo::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config = aboo::Config::Lookup("system.int_vec", std::vector<int>{1, 2}, "system int vec");
aboo::ConfigVar<std::list<int> >::ptr g_int_list_value_config = aboo::Config::Lookup("system.int_list", std::list<int>{1, 2}, "system int vec");
aboo::ConfigVar<std::set<int> >::ptr g_int_set_value_config = aboo::Config::Lookup("system.int_set", std::set<int>{1, 2}, "system int set");
aboo::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_value_config = aboo::Config::Lookup("system.int_uset", std::unordered_set<int>{1, 2}, "system int uset");
aboo::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_value_config = aboo::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"k", 2}}, "system str int map");
aboo::ConfigVar<std::map<int, std::string> >::ptr g_int_str_map_value_config = aboo::Config::Lookup("system.int_str_map", std::map<int, std::string>{{2, "K"}, {3, "V"}}, "system int str map");
aboo::ConfigVar<std::map<int, char> >::ptr g_int_char_map_value_config = aboo::Config::Lookup("system.int_char_map", std::map<int, char>{{1, 'a'}, {2, 'b'}, {3, 'c'}}, "system int char map");
aboo::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_value_config = aboo::Config::Lookup("system.str_int_umap", std::unordered_map<std::string, int>{{"k", 3}}, "system str int umap");

void print_yaml(const YAML::Node& node, int level) {
	if (node.IsScalar()) {
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << std::string(level * 4, ' ') << node.Scalar() << '-' << node.Type() << '-' << level;
	} else if (node.IsNull()) {
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << std::string(level * 4, ' ') << "NULL - " << node.Type() << '-' << level;
	} else if (node.IsMap()) {
		for (auto it = node.begin(); it != node.end(); ++it) {
			ABOO_LOG_INFO(ABOO_LOG_ROOT()) << std::string(level * 4, ' ') << it->first << '-' << it->second.Type() << '-' << level;
			print_yaml(it->second, level + 1);
		}
	} else if (node.IsSequence()) {
		for (size_t i = 0; i < node.size(); ++i) {
			ABOO_LOG_INFO(ABOO_LOG_ROOT()) << std::string(level * 4, ' ') << i << '-' << node[i].Type() << '-' << level;
			print_yaml(node[i], level + 1);
		}
	}
}

void test_yaml() {
	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/test.yml");
	print_yaml(root, 0);

	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << root;
}

void test_config() {
//	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
//	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "before: " << g_float_value_config->toString();

#define XX(g_var, name, prefix) \
	{ \
		auto& v = g_var->getValue(); \
		for (auto& i : v) { \
			ABOO_LOG_INFO(ABOO_LOG_ROOT()) << #prefix " " #name ": " << i; \
		} \
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
	}

#define XX_M(g_var, name, prefix) \
	{ \
		auto& v = g_var->getValue(); \
		for (auto& i : v) { \
			ABOO_LOG_INFO(ABOO_LOG_ROOT()) << #prefix " " #name ": {" << i.first << " - " << i.second << '}'; \
		} \
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
	}
/*
	XX(g_int_vec_value_config, int_vec, before);
	XX(g_int_list_value_config, int_list, before);
	XX(g_int_set_value_config, int_set, before);
	XX(g_int_uset_value_config, int_uset, before);
*/	XX_M(g_str_int_map_value_config, str_int_map, before);
	XX_M(g_int_str_map_value_config, int_str_map, before);
	XX_M(g_int_char_map_value_config, int_char_map, before);
//	XX_M(g_str_int_umap_value_config, str_int_umap, before);

	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/test.yml");
	aboo::Config::LoadFromYaml(root);

//	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
//	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "after: " << g_float_value_config->toString();

/*	XX(g_int_vec_value_config, int_vec, after);
	XX(g_int_list_value_config, int_list, after);
	XX(g_int_set_value_config, int_set, after);
	XX(g_int_uset_value_config, int_uset, after);
*/	XX_M(g_str_int_map_value_config, str_int_map, after);
	XX_M(g_int_str_map_value_config, int_str_map, after);
	XX_M(g_int_char_map_value_config, int_char_map, after);
//	XX_M(g_str_int_umap_value_config, str_int_umap, after);
}

class Person {
public:
	std::string m_name = "";
	int m_age = 0;
	bool m_sex = 0;

	std::string toString() const {
		std::stringstream ss;
		ss << "[ Person name=" << m_name
		   << " age=" << m_age
		   << " sex=" << m_sex
		   << "]";
		return ss.str();
	}

	bool operator== (const Person& oth) const {
		return m_name == oth.m_name && m_age == oth.m_age && m_sex == oth.m_sex;
	}
};

namespace aboo {

template<>
class LexicalCast<std::string, Person > {
public:
	Person operator() (const std::string& v) {
		YAML::Node node = YAML::Load(v);
		Person p;
		p.m_name = node["name"].as<std::string>();
		p.m_age = node["age"].as<int>();
		p.m_sex = node["sex"].as<bool>();
		return p;
	}
};

template<>
class LexicalCast<Person, std::string> {
public:
	std::string operator() (const Person&  p) {
		YAML::Node node;
		node["name"] = p.m_name;
		node["age"] = p.m_age;
		node["sex"] = p.m_sex;
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

}
aboo::ConfigVar<Person>::ptr g_person = aboo::Config::Lookup("class.person", Person(), "class person");
aboo::ConfigVar<std::map<std::string, Person> >::ptr g_person_map = aboo::Config::Lookup("class.map", std::map<std::string, Person>(), "class person");

void test_class() {
	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "before: " << g_person->getValue().toString() << " - " << g_person->toString();

#define XX_PM(g_var, prefix) \
	{ \
			auto &m = g_var->getValue(); \
		for (auto& i : m) { \
			ABOO_LOG_INFO(ABOO_LOG_ROOT()) << prefix << ": " << i.first << " - " << i.second.toString(); \
		} \
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << prefix << ": size=" << m.size(); \
	}

	g_person->addListener([](const Person& old_value, const Person& new_value){
				ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "old_value=" << old_value.toString() << " new_value=" << new_value.toString();
			});

	XX_PM(g_person_map, "class map before");

	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/test.yml");
	aboo::Config::LoadFromYaml(root);

	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "after: " << g_person->getValue().toString() << " - " << g_person->toString();
	XX_PM(g_person_map, "class map after");

}

void test_log() {
	static aboo::Logger::ptr system_log = ABOO_LOG_NAME("system");
	ABOO_LOG_INFO(system_log) << "hello system" << std::endl;
	std::cout << aboo::LoggerMgr::getInstance()->toYamlString() << std::endl;

	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/log.yml");
	aboo::Config::LoadFromYaml(root);

	std::cout << "------------------------------------------------\n";

	std::cout << aboo::LoggerMgr::getInstance()->toYamlString() << std::endl;
	ABOO_LOG_INFO(system_log) << "hello system" << std::endl;

	system_log->setFormatter("%d - %m%n");
	ABOO_LOG_INFO(system_log) << "hello system" << std::endl;
}

void test_loadconf() {
	aboo::Config::LoadFromConfDir("conf");
}

int main(int argc, char **argv) {
	// test_config();
	// test_yaml();
	// test_class();
	// test_log();
	aboo::EnvMgr::getInstance()->init(argc, argv);
	test_loadconf();
	std::cout << "==================================================\n";
	sleep(10);
	test_loadconf();
	aboo::Config::Visit([](aboo::ConfigVarBase::ptr var) {
		ABOO_LOG_INFO(ABOO_LOG_ROOT()) << "name=" << var->getName() << " description=" << var->getDescription() << " typename=" << var->getTypeName() << " value=" << var->toString();
	});
	return 0;
}
