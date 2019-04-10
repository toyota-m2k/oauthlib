#pragma once
#include "OAuthCompletionEventSink.h"
#include "OAuthClientApi.h"

class COAuthClient : public ICompletionHandler
{
private:
	IUnknown* mOAuthLib = NULL;
	IOAuthDriver* mAuthDriver = NULL;
	IConnectionPointContainer* mCPointContainer = NULL;
	IConnectionPoint* mCPoint = NULL;
	OAuthCompletionEventSink* mEventSink = NULL;
	HRESULT mResult = S_OK;
	DWORD mCookie = (DWORD)-1;
	
	OAUTHCallback mCallback;
	void* mClientData;

	void Dispose();
	virtual void OAuthCompleted(BOOL succeeded);

public:
	COAuthClient(OAUTHCallback callback, void* clientData);
	~COAuthClient();

	BOOL HasError() {
		return FAILED(mResult);
	}

	BOOL Auth(LPCWSTR mailAddress);
	BOOL Update(LPCWSTR accessToken, LPCWSTR refreshToken);
};

