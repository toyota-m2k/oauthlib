#include "stdafx.h"
#include "OAuthClientApi.h"
#include "COAuthClient.h"

HANDLE_OAUTH APIENTRY OAUTHOpen(OAUTHCallback callback, void* clientData) {
	COAuthClient* client = new COAuthClient(callback, clientData);
	if (client->HasError()) {
		delete client;
		return NULL;
	}
	return client;
}

void APIENTRY OAUTHClose(HANDLE_OAUTH client) {
	if (client) {
		delete client;
	}
}

BOOL APIENTRY OAUTHAuthenticate(HANDLE_OAUTH client, LPCWSTR mailAddress) {
	return client->Auth(mailAddress);
}

//BOOL APIENTRY OAUTHUpdateAuth(HANDLE_OAUTH client, LPCWSTR accessToken, LPCWSTR refreshToken) {
//	return client->Update(accessToken, refreshToken);
//}
