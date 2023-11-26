#include "HttpMessage.hpp"

void HttpMessage::handlePostMethod() {
    
    //check if location support upload
    if(checkLocationSupportUpload()) {
        //upload the post request body
        //create `201 Created` http response message
        //return ;
    }

    if(!checkContentExistsInRoot()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return Page
    }

    //we check if the uri is dir (has '/' at end)
    if (checkContentIsDir()) {
        if (!checkDirIndedWithBackSlash()) {
            //creeate 301 redirection to request uri with '/' at the end
            //return;
        }
        if (checkIndexFilesInDir()) {
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                //create 403 Forbidden
                //return requested file
            }
        }
        else {
            //create 403 Forbidden
            //this->statusCode = 403
            //this->statusMessage = Forbidden
            //return errorPage
        }
    }
    //we request a file here
    else {
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with POST request method
        }
        else {
            //create 403 Forbidden
            //this->statusCode = 403
            //this->statusMessage = Forbidden
            //return errorPage
        }
    }
}