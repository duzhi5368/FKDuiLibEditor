/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#pragma once
//-----------------------------------------------------------------------
#include "anyoption.h"
//-----------------------------------------------------------------------
class CFKCommandParser {
public:
	CFKCommandParser();
	virtual ~CFKCommandParser();
public:

private:
	AnyOption* m_pOption;
};