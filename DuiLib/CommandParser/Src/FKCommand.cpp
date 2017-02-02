/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#include <iostream>
#include "../Include/FKCommand.h"
//-----------------------------------------------------------------------
IFKCommand::IFKCommand(string strCmdKey, string strDesc)
	: m_strCmdKey(strCmdKey)
	, m_strDesc(strDesc)
{
	m_vecCmdArray.clear();
}
//-----------------------------------------------------------------------
IFKCommand::~IFKCommand()
{
	m_strCmdKey.clear();
	m_strDesc.clear();
	m_vecCmdArray.clear();
}
//-----------------------------------------------------------------------
bool IFKCommand::AddParams(string strArg, string strDesc)
{
	try {
		CMD_ARG_DESC_MAP::const_iterator Ite = m_vecCmdArray.find(strArg);
		// 参数已经添加，禁止修改
		if (Ite != m_vecCmdArray.end())	
			return false;
		m_vecCmdArray.insert(std::pair<string, string>(strArg, strDesc));
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------
string IFKCommand::ToString()
{
	string strRet;
	strRet += m_strCmdKey;
	strRet += " ";
	strRet += m_strDesc;
	strRet += "\n";
	CMD_ARG_DESC_MAP::const_iterator IteEnd = m_vecCmdArray.end();
	CMD_ARG_DESC_MAP::iterator Ite = m_vecCmdArray.begin();
	for (; Ite != IteEnd; ++Ite) {
		strRet += " - ";
		strRet += Ite->first;
		strRet += "\t\t";
		strRet += Ite->second;
		strRet += "\n";
	}
	return strRet;
}
//-----------------------------------------------------------------------