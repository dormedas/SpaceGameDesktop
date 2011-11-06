#include "fleetFrame.h"
#include "dataPoll.h"
#include "logInHandler.h"
#include <iostream>
#include <string>
#include <sstream>

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

	int x = 0;
	stringstream temp;

	string finalString;

	//wxString tempHabitable;

	for(int i = 0; i < o.get<jsonxx::Array>("data").size(); ++i)
	{
		x = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("profit");
		temp << x;
		wxString tempNum = temp.str();

		wxString tempName = wxString(o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("name"));

		wxString tempStatus = wxString(o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("status"));

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
		listCtrl.SetItem(index, 2, tempNum);
		//listCtrl.SetItem(index, 2, tempHabitable);

		temp.str("");
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
	m_item_list->InsertColumn(2, col2);
		   
	wxListItem col3;
	col3.SetId(3);
	col3.SetText( _("Habitable") );
	m_item_list->InsertColumn(3, col3);

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
