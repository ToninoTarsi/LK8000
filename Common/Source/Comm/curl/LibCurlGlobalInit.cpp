/*
 * LK8000 Tactical Flight Computer -  WWW.LK8000.IT
 * Released under GNU/GPL License v.2
 * See CREDITS.TXT file for authors and copyrights
 *
 * File:   init_curl.cpp
 * Author: Bruno de Lacheisserie
 *
 * Created on September 21, 2016, 11:09 PM
 */

#include "LibCurlGlobalInit.h"
#include <curl/curl.h>

LibCurlGlobalInit::LibCurlGlobalInit() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

LibCurlGlobalInit::~LibCurlGlobalInit() {
    curl_global_cleanup();
}
