/************************************************************************
* Created by FreeKnight
* 2017/1/19
************************************************************************/
#pragma once
//-----------------------------------------------------------------------
#include <DuiLib/UIlib.h>
using namespace DuiLib;
//-----------------------------------------------------------------------
#include "../MiniDumper/MiniDumper.h"
//-----------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "duilib_d.lib")
#pragma comment(lib, "MiniDumper_d.lib")
#else
#pragma comment(lib, "duilib.lib")
#pragma comment(lib, "MiniDumper.lib")
#endif
//-----------------------------------------------------------------------