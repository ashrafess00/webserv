#pragma once
#include "webserv.hpp"

class HttpMessage {
    private:
        std::stringstream startLine;
        std::string statusCode;
        std::string contentType;
        std::string statusText;
        std::string header;
        std::map<std::string, std::string> mime_types;
        std::string get_mime_type(const std::string &fileName);
    public:
        HttpMessage(std::string statusCodep, std::string &target);
        std::string &createAndGetHeader();
};