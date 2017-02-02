/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#pragma once
//-----------------------------------------------------------------------
#include <map>
#include "FKCommand.h"
//-----------------------------------------------------------------------
using std::map;
//-----------------------------------------------------------------------
class CFKCommandManager {
private:
	map<string, IFKCommand*>		m_mapCommandsList;
public:
	CFKCommandManager();
	~CFKCommandManager();
public:
	IFKCommand*	AddCommand(IFKCommand* pCmd);
};
