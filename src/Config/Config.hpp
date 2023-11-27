#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "webserv.hpp"
typedef std::vector<std::string> vec;
typedef std::map<std::string, std::string> mp;

struct locate
{
	std::string autoindex;
	std::string cgi_path;
	std::string cgi_extension;
	std::string index;
	std::string root;
	std::string redirect;
	std::string method;
	std::string method1;
	std::string method2;
	std::string method3;
};

typedef std::map<std::string, locate > map_last;

struct serv_conf
{
	std::string host;
	long long port;
	std::string errorPages;
	std::string name;
	long long clientBodyLimit;
	mp routes; //dyali do not use it
	map_last rout;
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
		int 	how_mn_servers();
		void display_all(serv_conf srvConf);
		int servers_number;
		unsigned int getPort() const;
		void parseInfosStr(std::string name , int leng, std::string &host);
		locate get_info_for_loca(std::string str);
		void parseInfosInt(std::string name , int leng, long long &host);
		void parseLocation(int i);
		std::string value_fo_loca(vec::iterator it);
		void parseConf();
		std::vector<serv_conf> srvConf; 
	private:
		static const int arr = 10;
		std::vector<std::string> raw_data;
		unsigned int port;
};

std::ostream &operator<<(std::ostream &o, Config const &i);

#endif /* ********************************************************** CONFIG_H */