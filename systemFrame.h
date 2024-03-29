#include <wx/wx.h>
#include "wx/listctrl.h"
#include "dataPoll.h"

class SystemFrame : public wxFrame
{
public:
	SystemFrame(const wxString& title);

	void OnQuit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void getData(wxListCtrl& listCtrl);


	

	wxListCtrl* m_item_list;
	//wxPanel* m_parent;

	wxMenuBar* menubar;
	wxMenu* file;
	wxMenu* edit;
	wxMenu* help;
	wxMenuItem* quit;
	wxMenuItem* newMenu;
};
