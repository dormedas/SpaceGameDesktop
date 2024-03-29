/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <cassert>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "main.h"
#include "systemFrame.h"
#include "fleetFrame.h"
#include "logInHandler.h"

using namespace std;

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	LogInHandler handler;
	
	SystemFrame* systemFrame = new SystemFrame(wxT("Systems"));
	systemFrame->Show(true);

	FleetFrame* fleetFrame = new FleetFrame(wxT("Fleets"));
	fleetFrame->Show(true);
	
	return true;
}
