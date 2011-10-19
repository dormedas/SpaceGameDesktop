/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "curl/curl.h"
#include "jsonxx\jsonxx.h"
 
using namespace std;

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  string response;
  if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, "http://spacega.me/data/systems?game=1&page=1&start=0&limit=1000");

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	res = curl_easy_perform(curl);
 
	/* always cleanup */ 
	curl_easy_cleanup(curl);
  }
  //std::cout << response << endl;

  istringstream input(response);
  jsonxx::Object o;

	assert(jsonxx::Object::parse(input, o));
	assert(o.has<jsonxx::Array>("data"));

	for(int i = 0; i < o.get<jsonxx::Array>("data").size(); ++i)
	{
		cout << o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("name") << ": ";
		cout << o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("num_planets") << endl;
	}

  cin.get();
  return 0;
}