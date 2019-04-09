// OAuthClient.h : OAuthClient DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// COAuthClientApp
// このクラスの実装に関しては OAuthClient.cpp をご覧ください
//

class COAuthClientApp : public CWinApp
{
public:
	COAuthClientApp();

// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
