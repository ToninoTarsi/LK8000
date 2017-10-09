/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HttpSession.h
 * Author: bruno
 *
 * Created on September 21, 2016, 11:39 PM
 */

#ifndef HTTPSESSION_H
#define HTTPSESSION_H

#include <curl/curl.h>
#include <sstream>

class HttpSession final {
public:
    HttpSession();
    ~HttpSession();

    bool Request(const char* Host, uint16_t Port, const char* Url);

    std::string Response() const {
        return strResponse;
    }

    void SetTimeout(unsigned sec);

private:
    CURL* curl;
    std::string strResponse;
};

#endif /* HTTPSESSION_H */
