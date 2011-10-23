#include <sstream>
#include <string>
#include "jsonxx\jsonxx.h"
#include "curl/curl.h"

class DataPoll
{
private:
	CURL *mCurl;
	CURLcode mRes;
	std::string mSystemData;

	//size_t writeToString(void *ptr, size_t size, size_t count, void *stream);
	void pollSystemData();

public:
	DataPoll();
	std::string getSystemData(bool refresh);
};