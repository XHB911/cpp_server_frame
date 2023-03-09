#ifndef __ABOO_ENV_H__
#define __ABOO_ENV_H__

#include "singleton.h"
#include "thread.h"
#include <map>
#include <vector>

namespace aboo {

class Env {
public:
	typedef RWMutex RWMutexType;
	/**
	 * @brief 根据 main 函数命令行参数初始化
	 * 
	 * @param[in] argc main 函数命令行参数个数
	 * @param[in] argv main 函数命令行参数
	 * @return bool 返回是否初始化成功
	**/
	bool init(int argc, char** argv);

	/**
	 * @brief 添加程序自定义环境变量
	 * 
	 * @param[in] key 程序自定义环境变量的键
	 * @param[in] val 程序自定义环境变量的值
	 * @return void
	 */
	void add(const std::string& key, const std::string& val);

	/**
	 * @brief 判断程序是否拥有环境变量
	 * 
	 * @param[in] key 程序自定义环境变量的键
	 * @return bool 成功返回 true
	 */
	bool has(const std::string& key);

	/**
	 * @brief 删除程序自定义环境变量
	 * 
	 * @param[in] key 删除环境变量的键
	 * @return bool 成功返回 true
	 */
	bool del(const std::string& key);

	/**
	 * @brief 根据 key 得到环境变量，若为空，则返回默认值
	 * 
	 * @param[in] key 要得到的环境变量的键
	 * @param[in] default_val 默认的该环境变量的值
	 * @return std::string 返回环境变量的值
	 */
	std::string get(const std::string& key, const std::string& default_val = "");

	/**
	 * @brief 添加帮助信息
	 *
	 * @parama[in] 添加帮助信息的键
	 * @param[in] 添加帮助信息的内容描述
	 */
	void addHelp(const std::string& key, const std::string& desc);

	/**
	 * @brief 移除帮助信息
	 *
	 * @parama[in]要移除帮助信息的键
	 */
	void removeHelp(const std::string& key);

	/**
	 * @brief打印帮助信息
	 */
	void printHelp();

	/**
	 * @brief 得到程序的绝对路径
	 */
	const std::string& getExe() { return m_exe; }

	/**
	 * @brief 得到程序的运行路径
	 */
	const std::string& getCwd() { return m_cwd; }

	/**
	 * @brief 设置系统环境变量
	 *
	 * @param[in] key 要设置的系统环境变量的键
	 * @param[in] val 要设置的系统环境变量的内容
	 */
	bool setEnv(const std::string& key, const std::string& val);

	/**
	 * @brief 得到系统环境变，若该系统变量不存在，则返回默认值量
	 *
	 * @param[in] key 要得到的系统环境变量的键
	 * @param[in] fault_val 要得到的系统环境变量的默认返回值
	 */
	std::string getEnv(const std::string& key, const std::string& default_val = "");

	/**
	 * @brief 传入一个相对于 bin 文件的路径，返回这个路径的绝对路径。
	 *
	 * @param[in] path 相对于 bin 文件的路径
	 */
	std::string getAbsolutePath(const std::string& path) const;
private:
	RWMutexType m_mutex;
	// 内部存储程序级环境变量的 map
	std::map<std::string, std::string> m_args;
	// 存储帮助信息的结构
	std::vector<std::pair<std::string, std::string>> m_helps;

	// 程序的名称
	std::string m_program;
	// 获取程序的 bin 文件绝对路径
	std::string m_exe;
	// 程序运行路径
	std::string m_cwd;
};

typedef aboo::Singleton<Env> EnvMgr;

}

#endif
