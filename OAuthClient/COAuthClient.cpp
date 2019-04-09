#include "stdafx.h"
#include "COAuthClient.h"

COAuthClient::COAuthClient(OAUTHCallback callback, void* clientData)
{
	mCallback = callback;
	mClientData = clientData;

	do {
		mResult = ::CoCreateInstance(CLSID_OAuthDriver, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&mOAuthLib);
		if (FAILED(mResult)) {
			break;
		}
		mResult = mOAuthLib->QueryInterface(DIID_IOAuthDriver, (void**)&mAuthDriver);
		if (FAILED(mResult)) {
			break;
		}

		mResult = mAuthDriver->QueryInterface(IID_IConnectionPointContainer, (void**)&mCPointContainer);
		if (FAILED(mResult)) {
			break;
		}

		mResult = mCPointContainer->FindConnectionPoint(DIID_IOAuthCompletedEvent, &mCPoint);
		if (FAILED(mResult)) {
			break;
		}
		mEventSink = new OAuthCompletionEventSink(this);
		mEventSink->AddRef();
		mResult = mCPoint->Advise(mEventSink, &mCookie);
		if (FAILED(mResult)) {
			break;
		}
		return;
	} while (0);
	Dispose();
}

COAuthClient::~COAuthClient()
{
	Dispose();
}

void COAuthClient::Dispose() {
	if (mOAuthLib) {
		mOAuthLib->Release();
		mOAuthLib = NULL;
	}
	if (mAuthDriver) {
		mAuthDriver->Release();
		mAuthDriver = NULL;
	}
	if (mCPointContainer) {
		mCPointContainer->Release();
		mCPointContainer = NULL;
	}
	if (mCPoint) {
		if (mCookie != (DWORD)-1) {
			mCPoint->Unadvise(mCookie);
		}
		mCPoint->Release();
		mCPoint = NULL;
	}
	if (mEventSink) {
		mEventSink->Release();
		mEventSink = NULL;
	}
}

void COAuthClient::OAuthCompleted(BOOL succeeded) {
	if (mCallback) {
		if (!succeeded) {
			mCallback(this, mClientData, FALSE, NULL, NULL);
		} else {
			_bstr_t accessToken = mAuthDriver->GetAccessToken();
			_bstr_t refreshToken = mAuthDriver->GetRefreshToken();
			mCallback(this, mClientData, TRUE, accessToken, refreshToken);
		}
	}
}

BOOL COAuthClient::Auth() {
	if (HasError()) {
		return FALSE;
	}
	HRESULT hr = mAuthDriver->Auth();
	return SUCCEEDED(hr);
}

BOOL COAuthClient::Update(LPCWSTR accessToken, LPCWSTR refreshToken) {
	if (HasError()) {
		return FALSE;
	}
	HRESULT hr = mAuthDriver->Update(accessToken, refreshToken);
	return SUCCEEDED(hr);
}
