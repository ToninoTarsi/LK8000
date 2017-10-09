/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HttpSession.cpp
 * Author: bruno
 *
 * Created on September 21, 2016, 11:39 PM
 */

#include "HttpSession.h"
#include "Time/PeriodClock.hpp"

static size_t data_write_to_ostream(void* buf, size_t size, size_t nmemb, void* userp) {
	if(userp) {
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len)) {
			return len;
        }
	}

	return 0;
}

HttpSession::HttpSession() {
    curl = curl_easy_init();
    if(curl) {
        // ignore unsecure ssl
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // allow ipv4 and ip ipv6
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_WHATEVER);

        // set timout
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        // enable TCP keep-alive
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);

        // set Response callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_write_to_ostream);
    }
}

HttpSession::~HttpSession() {
    if(curl) {
        curl_easy_cleanup(curl);
    }
}

void HttpSession::SetTimeout(unsigned sec) {
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, sec);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, sec);
    }
}

bool HttpSession::Request(const char* Host, uint16_t Port, const char* Url) {
    if(!curl) {
        return false;
    }

    // build url
    std::ostringstream ossUrl;
    ossUrl << "http://" << Host << ":" << Port << Url;
	curl_easy_setopt(curl, CURLOPT_URL,ossUrl.str().c_str());

    // set response callback
    std::ostringstream ossResponse;
    curl_easy_setopt(curl, CURLOPT_FILE, &ossResponse);

    // send request
	CURLcode res = curl_easy_perform(curl);

    strResponse = ossResponse.str();

    return (res == CURLE_OK);
}
