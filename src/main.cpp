#include "webserv.hpp"

Logger logger = Logger("webserv.log");

int main(int argc, char const *argv[])
{
    // execute_php("php/index.php");
    try
    {
        if (argc != 2)
        {
            logger.Log(ERROR, "bad arguments");
            logger.Log(INFO, "try: ./webserv ./webserver.conf");
            return 1;
        }
        Config config(argv[1]);
        std::string l = "la";
        RequestData rd(l);
        HttpMessage HttpMessage(rd, config);

        Server server(config, HttpMessage);
        server.start();
        server.waitClients();
        
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
