#include <string>

using std::string;

class LogInHandler
{
private:
	bool mLoggedIn;
public:
	static string mUsername;
	static string mPassword;
	LogInHandler();
	void prompt(string& username, string& password);
	void getLogInData(string& username, string& password);
};
