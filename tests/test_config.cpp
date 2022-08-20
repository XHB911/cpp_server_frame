#include "../aboo/config.h"
#include "../aboo/log.h"
#include <yaml-cpp/yaml.h>

aboo::ConfigVar<int>::ptr g_int_value_config = aboo::Config::Lookup("system.port", (int)8080, "system port");
aboo::ConfigVar<float>::ptr g_float_value_config = aboo::Config::Lookup("system.value", (float)10.2f, "system value");

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
	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/log.yml");
	print_yaml(root, 0);

	// ABOO_LOG_INFO(ABOO_LOG_ROOT()) << root;
}

int main(int argc, char **argv) {
	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << g_int_value_config->getValue();
	ABOO_LOG_INFO(ABOO_LOG_ROOT()) << g_float_value_config->toString();

	test_yaml();

	return 0;
}
