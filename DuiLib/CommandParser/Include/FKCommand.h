/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#pragma once
//-----------------------------------------------------------------------
#include <vector>
#include <string>
#include <map>
//-----------------------------------------------------------------------
using std::map;
using std::vector;
using std::string;
//-----------------------------------------------------------------------
typedef map<string, string>	CMD_ARG_DESC_MAP;
//-----------------------------------------------------------------------
class CFKCommandManager;
class IFKCommand 
{
	friend class CFKCommandManager;
public:
	IFKCommand(string strCmdKey, string strDesc = "");
	virtual ~IFKCommand();
	virtual bool			AddParams(string strArg, string strDesc);
	virtual string			ToString();
	virtual bool			Do(vector<string> listArgs, string& strResult) = 0;
protected:
	string					m_strCmdKey;
	string					m_strDesc;
	CMD_ARG_DESC_MAP		m_vecCmdArray;
};