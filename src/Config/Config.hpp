#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "webserv.hpp"
typedef std::vector<std::string> vec;
typedef std::map<std::string, std::string> mp;

struct serv_conf
{
	std::string host;
	long long port;
	std::string errorPages;
	std::string name;
	long long clientBodyLimit;
	mp routes;
};
class Config
{

public:
	Config();
	Config(Config const &src);
	Config(std::string conf);
	~Config();
	Config &operator=(Config const &rhs);
	// 
	unsigned int getPort() const;
	void parseInfosStr(std::string name , int leng, std::string &host);
	void parseInfosInt(std::string name , int leng, long long &host);
	void parseLocation();
	serv_conf srvConf;
	std::string value_fo_loca(vec::iterator it);
	void parseConf();
private:
	std::vector<std::string> raw_data;
	unsigned int port;
};

std::ostream &operator<<(std::ostream &o, Config const &i);

#endif /* ********************************************************** CONFIG_H */