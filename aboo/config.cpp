#include "config.h"
#include "env.h"
#include "util.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace aboo {

static aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");

ConfigVarBase::ptr Config::LookupBase(const std::string& name) {
	RWMutexType::ReadLock lock(GetMutex());
	auto it = getDatas().find(name);
	return it == getDatas().end() ? nullptr : it->second;
}

//"A.B", 10
static void ListAllMember(const std::string& prefix, const YAML::Node& node, std::list<std::pair<std::string , const YAML::Node> >& output) {
	if (prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos) {
		ABOO_LOG_ERROR(g_logger)<< "Config invalid name: " << prefix << " : " << node;
		return;
	}
	output.push_back(std::make_pair(prefix, node));
	if (node.IsMap()) {
		for (auto it = node.begin(); it != node.end(); ++it) {
			ListAllMember(prefix.empty() ? it->first.Scalar() : prefix + "." +  it->first.Scalar(), it->second, output);
		}
	}
}

void Config::LoadFromYaml(const YAML::Node& root) {
	std::list<std::pair<std::string, const YAML::Node> > all_nodes;
	ListAllMember("", root, all_nodes);

	for (auto& i : all_nodes) {
		std::string key = i.first;
		if (key.empty()) {
			continue;
		}

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);
		ConfigVarBase::ptr var = Config::LookupBase(key);

		if (var) {
			if (i.second.IsScalar()) {
				var->fromString(i.second.Scalar());
			} else {
				std::stringstream ss;
				ss << i.second;
				var->fromString(ss.str());
			}
		}
	}
}

static std::map<std::string, uint64_t> s_file2modifytime;
static aboo::Mutex s_mutex;

void Config::LoadFromConfDir(const std::string& path) {
	std::string absolute_path = aboo::EnvMgr::getInstance()->getAbsolutePath(path);
	std::vector<std::string> files;
	FSUtil::ListAllFile(files, absolute_path, ".yml");

	for (auto& i : files) {
		{
			struct stat st;
			lstat(i.c_str(), &st);
			aboo::Mutex::Lock lock(s_mutex);
			if (s_file2modifytime[i] == (uint64_t)st.st_mtime) {
				continue;
			}
			s_file2modifytime[i] = st.st_mtime;
		}
		try {
			YAML::Node root = YAML::LoadFile(i);
			LoadFromYaml(root);
			ABOO_LOG_INFO(g_logger) << "LoadConfFile file=" << i << " ok";
		} catch (...) {
			ABOO_LOG_ERROR(g_logger) << "LoadConfFile file=" << i << " failure";
		}
	}
}

void Config::Visit(std::function<void (ConfigVarBase::ptr)> cb) {
	RWMutexType::ReadLock lock(GetMutex());
	ConfigVarMap& m = getDatas();
	for (auto it = m.begin(); it != m.end(); it++) {
		cb(it->second);
	}
}

}
