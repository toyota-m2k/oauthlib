#pragma once

class COAuthClient;
typedef COAuthClient* HANDLE_OAUTH;

typedef void(*OAUTHCallback)(HANDLE_OAUTH hAuth, void* clientData, bool succeeded, LPCWSTR accessToken, LPCWSTR refreshToken);

extern "C" {
	HANDLE_OAUTH APIENTRY OAUTHOpen(OAUTHCallback callback, void* clientData);
	void APIENTRY OAUTHClose(HANDLE_OAUTH hAuth);
	BOOL APIENTRY OAUTHAuthenticate(HANDLE_OAUTH hAuth, LPCWSTR mailAddress);
	//BOOL APIENTRY OAUTHUpdateAuth(HANDLE_OAUTH hAuth, LPCWSTR accessToken, LPCWSTR refreshToken);
}
