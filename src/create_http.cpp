/* ************************************************************************** */
/*                                                                            */
/*                                  :::      ::::::::                         */
/*                                :+:      :+:    :+:                         */
/*                              +:+ +:+         +:+                           */
/*                            +#+  +:+       +#+                              */
/*                          +#+#+#+#+#+   +#+                                 */
/*                               #+#    #+#                                   */
/*                              ###   ########.fr                             */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

std::map<std::string, std::string> init_mime_types()
{
    std::map<std::string, std::string> mime_types;

    // Define your MIME type mappings in a loop
    mime_types[".html"] = "text/html";
    mime_types[".htm"] = "text/html";
    mime_types[".shtml"] = "text/html";
    mime_types[".css"] = "text/css";
    mime_types[".js"] = "application/javascript";
    mime_types[".json"] = "application/json";
    mime_types[".xml"] = "application/xml";
    mime_types[".txt"] = "text/plain";
    mime_types[".jpg"] = "image/jpeg";
    mime_types[".jpeg"] = "image/jpeg";
    mime_types[".png"] = "image/png";
    mime_types[".gif"] = "image/gif";
    mime_types[".bmp"] = "image/bmp";
    mime_types[".svg"] = "image/svg+xml";
    mime_types[".pdf"] = "application/pdf";
    mime_types[".doc"] = "application/msword";
    mime_types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mime_types[".xls"] = "application/vnd.ms-excel";
    mime_types[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mime_types[".ppt"] = "application/vnd.ms-powerpoint";
    mime_types[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mime_types[".zip"] = "application/zip";
    mime_types[".tar"] = "application/x-tar";
    mime_types[".gz"] = "application/gzip";
    mime_types[".mp3"] = "audio/mpeg";
    mime_types[".wav"] = "audio/wav";
    mime_types[".ogg"] = "audio/ogg";
    mime_types[".mp4"] = "video/mp4";
    mime_types[".avi"] = "video/x-msvideo";
    // Add more mappings as needed

    return mime_types;
}

std::string get_mime_type(const std::string &fileName)
{
    // Define a mapping of file extensions to MIME types
    std::map<std::string, std::string> mime_types;
    mime_types = init_mime_types();

    // Find the file extension in the given file name
    size_t dotPosition = fileName.find_last_of('.');
    if (dotPosition != std::string::npos)
    {
        std::string fileExtension = fileName.substr(dotPosition);

        // Search for the MIME type in the mapping
        std::map<std::string, std::string>::iterator it = mime_types.find(fileExtension);
        if (it != mime_types.end())
        {
            return it->second;
        }
    }

    // Default to a generic binary MIME type if the extension is not recognized
    return "application/octet-stream";
}

std::string not_found_404()
{
    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
}

std::string buildHttpResponse(std::string __unused &method, std::string &target)
{
    if (target.empty())
        target = "index.html";
    std::string mime_type = get_mime_type(target), response;
    std::stringstream header;
    header << "HTTP/1.1 200 OK\r\n"
           << "Content-Type: " << mime_type << "\r\n"
           << "\r\n";
    // --------------------------------------------------------------
    response = header.str();
    std::ifstream file((STATIC_HTTP + target).c_str(), std::ios::binary);
    if (!file)
        return not_found_404();
    // --------------------------------------------------------------
    std::ostringstream fileContent;
    fileContent << file.rdbuf();
    response += fileContent.str();
    // --------------------------------------------------------------
    return (response);
}
