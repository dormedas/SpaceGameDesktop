#include "wx\wx.h"
#include "wx\menu.h"
//#include "wx\list.h"
#include "wx\listctrl.h"

class FleetFrame : public wxFrame
{
public:
	FleetFrame(const wxString& title);

	void OnQuit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);

	wxListCtrl* m_item_list;
	//wxPanel* m_parent;

	wxMenuBar* menubar;
	wxMenu* file;
	wxMenu* edit;
	wxMenu* help;
	wxMenuItem* quit;
	wxMenuItem* newMenu;
};
