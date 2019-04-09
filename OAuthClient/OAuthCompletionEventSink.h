#pragma once

class ICompletionHandler {
public:
	virtual void OAuthCompleted(BOOL succeeded) = 0;
};

class OAuthCompletionEventSink : public IOAuthCompletedEvent
{
private:
	LONG mRef;
	ICompletionHandler* mHandler;
public:
	OAuthCompletionEventSink(ICompletionHandler* handler);
	~OAuthCompletionEventSink();

	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP OnCompleted(VARIANT_BOOL succeeded);

	STDMETHODIMP GetTypeInfoCount(UINT *pctinfo);
	STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
	STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
};

