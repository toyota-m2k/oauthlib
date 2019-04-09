
// OAuthTestApp.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "OAuthTestApp.h"
#include "OAuthTestAppDlg.h"
//#ifdef _DEBUG
//#import "..\OAuthLib\bin\Debug\OAuthLib.tlb" no_namespace named_guids
//#else
//#import "..\OAuthLib\bin\Release\OAuthLib.tlb" no_namespace named_guids
//#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COAuthTestApp

BEGIN_MESSAGE_MAP(COAuthTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COAuthTestApp の構築

COAuthTestApp::COAuthTestApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の COAuthTestApp オブジェクト

COAuthTestApp theApp;


BOOL COAuthTestApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	::CoInitialize(NULL);
	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	////SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	COAuthTestAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
#if 0
		IUnknown* oauthLib = NULL;
		IOAuthDriver* dsp = NULL;
		IConnectionPointContainer* cpc = NULL;
		IConnectionPoint* cp = NULL;
		HRESULT hr;
		do {
			hr = ::CoCreateInstance(CLSID_OAuthDriver, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&oauthLib);
			if (FAILED(hr)) {
				break;
			}
			hr = oauthLib->QueryInterface(DIID_IOAuthDriver, (void**)&dsp);
			if (FAILED(hr)) {
				break;
			}

			_bstr_t token = dsp->GetAccessToken();
			TRACE(LPCWSTR(token));

			hr = dsp->QueryInterface(IID_IConnectionPointContainer, (void**)&cpc);
			if (FAILED(hr)) {
				break;
			}

			hr = cpc->FindConnectionPoint(DIID_IOAuthCompletedEvent, &cp);
			if (FAILED(hr)) {
				break;
			}

		} while (0);

		if (dsp) {
			dsp->Release();
		}
		if (cpc) {
			cpc->Release();
		}
		if (cp) {
			cp->Release();
		}
		if (oauthLib) {
			oauthLib->Release();
		}
#endif

	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

int COAuthTestApp::ExitInstance() {
	::CoUninitialize();
	return CWinApp::ExitInstance();
}



