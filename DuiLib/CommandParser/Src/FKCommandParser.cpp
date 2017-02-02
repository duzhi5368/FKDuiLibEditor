/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#include "../Include/FKCommandParser.h"
//-----------------------------------------------------------------------
CFKCommandParser::CFKCommandParser()
{
	if (m_pOption == nullptr)
		m_pOption = new AnyOption();
}
//-----------------------------------------------------------------------
CFKCommandParser::~CFKCommandParser()
{
	if (m_pOption != nullptr)
		delete m_pOption;
}
//-----------------------------------------------------------------------