#include "dataPoll.h"

DataPoll::DataPoll()
{
	mCurl = curl_easy_init();
	mSystemData = "";
	pollSystemData();
}

size_t writeToString(void *ptr, size_t size, size_t count, void *stream)
{
	using namespace std;
	((string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}

void DataPoll::pollSystemData()
{
	std::string response;
	if(mCurl) 
	{
		curl_easy_setopt(mCurl, CURLOPT_URL, "http://spacega.me/data/systems?game=1&page=1&start=0&limit=1000");

		curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, writeToString);
		curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &response);
		mRes = curl_easy_perform(mCurl);
 
		/* always cleanup */ 
		curl_easy_cleanup(mCurl);
	}
	mSystemData = response;
}

std::string DataPoll::getSystemData(bool refresh)
{
	using namespace std;

	if(refresh)
	{
		pollSystemData();
	}

	return mSystemData;
}