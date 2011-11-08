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
	std::string mFleetData;
	std::string cookieFile;
	bool mLoggedIn;
	//size_t writeToString(void *ptr, size_t size, size_t count, void *stream);
	void logIn(std::string username, std::string password);
	std::string poll(std::string url);

public:
	DataPoll();
	~DataPoll();
	std::string getSystemData(bool refresh);
	std::string getFleetData(bool refresh, std::string username, std::string password);
	bool getState();
};
