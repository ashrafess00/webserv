#include "HttpRequestChecker.hpp"

HttpRequestChecker::HttpRequestChecker(RequestData &requestData, Config &config) : requestData(requestData), config(config) {
    this->target = requestData.getUri();
    this->method = requestData.getMethod();
}

std::string HttpRequestChecker::getStatusCode() {
    return this->statusCode;
}

void    HttpRequestChecker::createHttpHeader() {
    
}




//this will check the request and at the end it will create an http message and return it
AResponseMessage *HttpRequestChecker::checkRequestAndReturnHttpMessage() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";

    //////////////////////// check if req formed well /////////////////////////////
    if (checkNotAllowededChars()) {
        this->statusCode = "400";
        this->statusMessage = "Bad Request";
    }
    if (checkUriLength()) {
        //create 414 Request-URI Too Long
        //this->statusCode = 414
        //this->statusMessage = Request-URI Too Long
        // return errorPage
    }
    if (checkRequestHttpMessage()) {
        //create 413 Request Entity Too Large
        //this->statusCode = 413
        //this->statusMessage = Request Entity Too Large
        // return errorPage
    }
    
    //check if no location match the request uri
    if (!checkLocationMatchRequestUri()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return Page
        // std::cout << "not found a bb\n";
        // return ;
        // std::cout << this->config.srvConf[0].errorPages << "la\n";
        
        std::cout << "called\n";
        return new NotFound404(this->target, abstractErrorPages["404"]);
    }
    if (checkLocationHasRedirection()) {
        //create 301 Moved Permanently
        //this->statusCode = 301
        //this->statusMessage = MOved Permanently
        //return Page
    }

    //check if the method allowed in location
    if (checkMethodAllowed()) {
        //create 405 Method Not Allowed
        //this->statusCode = 405
        //this->statusMessage = Method Not Allowed
        //return Page
    }

    //now we check the request method
    //////////////////////////////// GET ///////////////////////////
    if (method == "GET") {
        handleGetMethod();
    }

    return new NotFound404(this->target, abstractErrorPages["404"]);
    //return the created http response message
}