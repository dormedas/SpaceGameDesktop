#include <wx/wx.h>
#include "logInHandler.h"

string LogInHandler::mUsername = "";
string LogInHandler::mPassword = "";

LogInHandler::LogInHandler()
{
	mLoggedIn = false;
	wxTextEntryDialog dialog(0, wxT("Enter your username"), wxT("Caption."), wxT("Enter Username"), wxOK | wxCANCEL);


	if(dialog.ShowModal() != wxID_OK)
	{
		wxMessageBox(wxT("Must enter username to request this data."), wxT("Error"));
	}

	wxPasswordEntryDialog passDiag(0, wxT("Enter your password"), wxT("Caption."), wxT("Enter Password"), wxOK | wxCANCEL);
	
	if(passDiag.ShowModal() != wxID_OK)
		wxMessageBox(wxT("Must enter username to request this data."), wxT("Error"));
	
	mUsername = dialog.GetValue();
	mPassword = passDiag.GetValue();
	return;
}

void LogInHandler::getLogInData(string& username, string& password)
{
	username = mUsername;
	password = mPassword;
}

void LogInHandler::prompt(string& username, string& password)
{

}
