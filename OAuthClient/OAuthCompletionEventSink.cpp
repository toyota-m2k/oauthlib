#include "stdafx.h"
#include "OAuthCompletionEventSink.h"


OAuthCompletionEventSink::OAuthCompletionEventSink(ICompletionHandler* handler)
{
	mRef = 0;
	mHandler = handler;
}


OAuthCompletionEventSink::~OAuthCompletionEventSink()
{
}

STDMETHODIMP OAuthCompletionEventSink::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDispatch) || IsEqualIID(riid, DIID_IOAuthCompletedEvent)) {
		*ppvObject = static_cast<IDispatch *>(this);
	} else {
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) OAuthCompletionEventSink::AddRef()
{
	return InterlockedIncrement(&mRef);
}

STDMETHODIMP_(ULONG) OAuthCompletionEventSink::Release()
{
	if (InterlockedDecrement(&mRef) == 0) {
		delete this;
		return 0;
	}
	return mRef;
}
STDMETHODIMP OAuthCompletionEventSink::GetTypeInfoCount(UINT *pctinfo)
{
	*pctinfo = 0;
	return S_OK;
}

STDMETHODIMP OAuthCompletionEventSink::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}

STDMETHODIMP OAuthCompletionEventSink::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	return E_NOTIMPL;
}

STDMETHODIMP OAuthCompletionEventSink::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	if (dispIdMember == 1) {
		mHandler->OAuthCompleted(pDispParams->rgvarg[0].boolVal);
	}
	return S_OK;
}

STDMETHODIMP OAuthCompletionEventSink::OnCompleted(VARIANT_BOOL succeeded) {
	mHandler->OAuthCompleted(succeeded);
	return S_OK;
}
