/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#include "../Include/FKCommandManager.h"
//-----------------------------------------------------------------------
CFKCommandManager::CFKCommandManager()
{
	m_mapCommandsList.clear();
}
//-----------------------------------------------------------------------
CFKCommandManager::~CFKCommandManager()
{
	map<string, IFKCommand*>::const_iterator IteEnd = m_mapCommandsList.end();
	map<string, IFKCommand*>::iterator Ite = m_mapCommandsList.begin();
	for (; Ite != IteEnd; ++Ite) {
		if (Ite->second != nullptr) {
			delete Ite->second;
		}
	}
	m_mapCommandsList.erase(m_mapCommandsList.begin(), m_mapCommandsList.end());
}
//-----------------------------------------------------------------------
IFKCommand* CFKCommandManager::AddCommand(IFKCommand* pCmd)
{
	if (pCmd == nullptr)
		return nullptr;
	map<string, IFKCommand*>::const_iterator Ite = m_mapCommandsList.find(pCmd->m_strCmdKey);
	if (Ite != m_mapCommandsList.end())
		return Ite->second;

	string str = pCmd->m_strCmdKey;
	m_mapCommandsList.insert(std::pair<string, IFKCommand*>(str, pCmd));
	return pCmd;
}
//-----------------------------------------------------------------------