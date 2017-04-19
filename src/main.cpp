/*    
    MWinSID.exe : Display the Windows Security Identifiers for accounts
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


//v1.0 copyright Comine.com 20170419W0925
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MLicenseGPL.h"
#include "MWinSID.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MWinSID";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<1)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.GetArgCount()<=1)
		{
		// Print out computer name
		MWinSID sid;
		if(sid.CreateFromComputerName()==false)
			{
			MStdPrintf("**System Failure\n");
			return 1;
			}

		sid.Print();
		return 0;
		}

	// Print out all sids passed as arguments
	for(int i=1;i<args.GetArgCount();++i)
		{
		const char *accountname=args.GetArg(i);
		MStdAssert(accountname!=0);

		MWinSID sid;
		if(sid.CreateFromAccountName(accountname)==false)
			{
			MStdPrintf("** Unable to get SID for Account %s\n",accountname);
			return 1;
			}
		
		sid.Print();
		}

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-gpl] [<account name>+]\n"
				"           v%s copyright Comine.com\n"
				"           Licensed under GPL.  use -gpl to read licence.\n"
				"\n"
				"   Prints out the Security Identifier(SID) for passed account names.\n"
				"   If no arguments are passed, then the Computer SID is printed.\n"				
				"\n"
				,GApplicationName,GApplicationVersion);
	}


