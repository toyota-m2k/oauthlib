
// OAuthTestApp.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// COAuthTestApp:
// このクラスの実装については、OAuthTestApp.cpp を参照してください
//

class COAuthTestApp : public CWinApp
{
public:
	COAuthTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	virtual int ExitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern COAuthTestApp theApp;
