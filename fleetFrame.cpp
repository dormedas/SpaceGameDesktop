#include "fleetFrame.h"
#include "dataPoll.h"
#include "logInHandler.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

void getFleetData(wxListCtrl& listCtrl)
{
	DataPoll poll;

	string data = poll.getFleetData(1, LogInHandler::mUsername, LogInHandler::mPassword);
	if(!poll.getState())
	{
		return;
	}

	istringstream input(data);

	jsonxx::Object o;

	assert(jsonxx::Object::parse(input, o));
	assert(o.has<jsonxx::Array>("data"));

	long long int profit = 0;
	double distance = 0,
	       velocity = 0;
	stringstream sstream;

	string finalString;

	//wxString tempHabitable;

	for(int i = 0; i < o.get<jsonxx::Array>("data").size(); ++i)
	{
		profit = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("profit");
		velocity = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("velocity");
		distance = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("distance");
		cout << profit;
		cout << endl;
		int minutesToTarget = floor(distance / velocity);
		if(velocity == 0)
		{
			minutesToTarget = 0;
		}
		wxString sProfit;
		sProfit << profit;
		//wxString sProfit(wxT("4"), wxConvUTF8);
		wxString sVelocity;
		sVelocity << velocity;
		wxString sDistance;
		sDistance << distance;
		wxString sMinToTarget;
		sMinToTarget << minutesToTarget;

		wxString tempName(o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("name").c_str(), wxConvUTF8);

		wxString tempStatus(o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("status").c_str(), wxConvUTF8);

		//bool y = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<bool>("hasHabitable");

		//if(y)
		//	tempHabitable = wxString("Yes");
		//else
		//	tempHabitable = wxString("No");

		wxListItem item;

		item.SetId(i);

		long index = listCtrl.InsertItem(item);

		listCtrl.SetItem(index, 0, tempName);
		listCtrl.SetItem(index, 1, tempStatus);
		listCtrl.SetItem(index, 2, sProfit);
		listCtrl.SetItem(index, 3, sDistance);
		listCtrl.SetItem(index, 4, sVelocity);
		listCtrl.SetItem(index, 5, sMinToTarget);

		//listCtrl.SetItem(index, 2, tempHabitable);

		sstream.str("");
	}
}

FleetFrame::FleetFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600,400))
{
	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	m_item_list = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(600,380), wxLC_REPORT);

	wxListItem col0;
	col0.SetId(0);
	col0.SetText( _("Name") );
	col0.SetWidth(100);
	m_item_list->InsertColumn(0, col0);

	wxListItem col1;
	col1.SetId(1);
	col1.SetText( _("Status") );
	col1.SetWidth(300);
	m_item_list->InsertColumn(1, col1);

	wxListItem col2;
	col2.SetId(2);
	col2.SetText( _("Profit") );
	col2.SetWidth(50);
	m_item_list->InsertColumn(2, col2);

	wxListItem col3;
	col3.SetId(3);
	col3.SetText( _("Distance") );
	col3.SetWidth(100);
	m_item_list->InsertColumn(3, col3);

	wxListItem col4;
	col4.SetId(4);
	col4.SetText( _("Velocity") );
	col4.SetWidth(100);
	m_item_list->InsertColumn(4, col4);

	wxListItem col5;
	col5.SetId(5);
	col5.SetText( _("Minutes til Arrival") );
	col5.SetWidth(100);
	m_item_list->InsertColumn(5, col5);

	getFleetData(*m_item_list);

	sizer->Add(m_item_list, 2, wxEXPAND | wxALL);

	panel->SetSizer(sizer);

	//this->SetSize(600, 1080);

	//-- Menu! --\\

	
	menubar = new wxMenuBar;

	file = new wxMenu;

	newMenu = new wxMenuItem(file, wxID_NEW, wxT("&New"));

	file->Append(newMenu);
	file->Append(wxID_ANY, wxT("&Open"));
	file->Append(wxID_ANY, wxT("&Save"));
	file->AppendSeparator();

	edit = new wxMenu;
	help = new wxMenu;

	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	file->Append(quit);

	menubar->Append(file, wxT("&File"));
	menubar->Append(edit, wxT("&Edit"));
	menubar->Append(help, wxT("&Help"));
	SetMenuBar(menubar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FleetFrame::OnQuit));
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FleetFrame::OnNew));

	Centre();
}

void FleetFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void FleetFrame::OnNew(wxCommandEvent& WXUNUSED(event))
{
	FleetFrame* fleetFrame = new FleetFrame(wxT("Fleets"));
	fleetFrame->Show(true);
}
