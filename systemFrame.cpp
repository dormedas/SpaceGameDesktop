#include "systemFrame.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void getSystemData(wxListCtrl& listCtrl)
{
	
	DataPoll poll;
	string data = poll.getSystemData(1);
	
	if(!poll.getState())
	{
		throw 'C';
		return;
	}

	istringstream input(data);

	jsonxx::Object o;

	assert(jsonxx::Object::parse(input, o));
	assert(o.has<jsonxx::Array>("data"));

	int x = 0;
	stringstream temp;

	string finalString;

	wxString tempHabitable;

	for(int i = 0; i < o.get<jsonxx::Array>("data").size(); ++i)
	{
		x = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<jsonxx::number>("num_planets");
		temp << x;
		wxString tempNum(temp.str().c_str(), wxConvUTF8);

		wxString tempName(o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<string>("name").c_str(), wxConvUTF8);

		bool y = o.get<jsonxx::Array>("data").get<jsonxx::Object>(i).get<bool>("hasHabitable");

		if(y)
			tempHabitable = wxString("Yes", wxConvUTF8);
		else
			tempHabitable = wxString("No", wxConvUTF8);

		wxListItem item;

		item.SetId(i);

		long index = listCtrl.InsertItem(item);

		listCtrl.SetItem(index, 0, tempName);
		listCtrl.SetItem(index, 1, tempNum);
		listCtrl.SetItem(index, 2, tempHabitable);

		temp.str("");
	}
}

SystemFrame::SystemFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(450,400))
{
	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	m_item_list = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(400,380), wxLC_REPORT);

	wxListItem col0;
	col0.SetId(0);
	col0.SetText( _("Name") );
	col0.SetWidth(100);
	m_item_list->InsertColumn(0, col0);

	// Add second column
	wxListItem col1;
	col1.SetId(1);
	col1.SetText( _("Num Planets") );
	m_item_list->InsertColumn(1, col1);
		
		// Add third column     
	wxListItem col2;
	col2.SetId(2);
	col2.SetText( _("Habitable") );
	m_item_list->InsertColumn(2, col2);
	
	getSystemData(*m_item_list);
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

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SystemFrame::OnQuit));
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SystemFrame::OnNew));

	Centre();
}

void SystemFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void SystemFrame::OnNew(wxCommandEvent& WXUNUSED(event))
{
	SystemFrame* systemFrame = new SystemFrame(wxT("Systems"));
	systemFrame->Show(true);
}
