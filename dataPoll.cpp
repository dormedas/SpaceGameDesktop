#include "dataPoll.h"

size_t writeToString(void *ptr, size_t size, size_t count, void *stream)
{
	using namespace std;
	((string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}

DataPoll::DataPoll()
{
	mCurl = curl_easy_init();
	curl_easy_setopt(mCurl, CURLOPT_COOKIEFILE, "cookies.cks");
	mSystemData = "";
	mFleetData = "";
	//pollSystemData();
	//getFleetData(true);
}

void DataPoll::logIn(std::string username, std::string password)
{
	if(mCurl)
	{
		curl_easy_reset(mCurl);
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */ 
		curl_easy_setopt(mCurl, CURLOPT_URL, "http://spacega.me/accounts/signin/");
		/* Now specify the POST data */ 
		curl_easy_setopt(mCurl, CURLOPT_COOKIEFILE, "");
 
		/* Perform the request, res will get the return code */	
		mRes = curl_easy_perform(mCurl);

		curl_easy_reset(mCurl); // Clear POSTFIELDS Option
		
		std::string csrftoken = "";

		struct curl_slist* list;
		curl_easy_getinfo(mCurl, CURLINFO_COOKIELIST, &list);
		
		struct curl_slist* i = list;
		
		while(i != NULL)
		{
			std::string temp = i->data;
			if(temp.find("csrf") != std::string::npos)
			{
				csrftoken = temp;
			}
			i = i->next;
		}
		
		if(csrftoken.find("csrftoken") != std::string::npos)
		{
			csrftoken = "csrfmiddlewaretoken=" + csrftoken.substr(csrftoken.find("csrftoken") + 10) +"&identification=" + username + "&password=" + password;
		}
		
		static const char* postdata = csrftoken.c_str();
		//void* pString = &csrftoken;
		
		curl_easy_reset(mCurl);

		curl_easy_setopt(mCurl, CURLOPT_URL, "http://spacega.me/accounts/signin/");
		curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, postdata);
		
		mRes = curl_easy_perform(mCurl);
		
		//if(mRes == CURLE_OK)
		//{
			mLoggedIn = true;
		//}

		curl_easy_reset(mCurl); // Clear POSTFIELDS Option
		
		curl_easy_setopt(mCurl, CURLOPT_HTTPGET, 1);

		curl_easy_setopt(mCurl, CURLOPT_URL, "http://spacega.me/join/1?");
		mRes = curl_easy_perform(mCurl);

		/* always cleanup */ 
		//curl_easy_cleanup(mCurl);
	}
	return;
}

std::string DataPoll::poll(std::string url)
{
	std::string response = "";
	if(mCurl)
	{
		curl_easy_reset(mCurl);

		curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, writeToString);
		curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &response);
		mRes = curl_easy_perform(mCurl);
 
		/* always cleanup */ 
		//curl_easy_cleanup(mCurl);
	}
	return response;
}

std::string DataPoll::getSystemData(bool refresh)
{
	using namespace std;

	if(refresh)
	{
		mSystemData = poll("http://spacega.me/data/systems?game=1&page=1&start=0&limit=1000");
	}	
	

	return mSystemData;
}

std::string DataPoll::getFleetData(bool refresh, std::string username, std::string password)
{
	using namespace std;
	if(refresh)
	{
		if(!mLoggedIn)
			logIn(username, password);
		mFleetData = poll("http://spacega.me/data/fleets?game=1&page=1&start=0&limit=1000");
	}

	return mFleetData;
}

bool DataPoll::getState()
{
	if(mRes == CURLE_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DataPoll::~DataPoll()
{
	curl_easy_reset(mCurl);
	curl_easy_setopt(mCurl, CURLOPT_COOKIEJAR, "cookies.cks");
	curl_easy_cleanup(mCurl);
}
