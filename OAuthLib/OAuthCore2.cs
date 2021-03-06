﻿using Google.Apis.Auth.OAuth2;
using Google.Apis.Util.Store;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OAuthLib
{
    public static class OAuthCore2
    {
        private const string clientId = Secrets.clientId;
        private const string clientSecret = Secrets.clientSecret;

        public static async Task<(string accessToken, string refreshToken)> Auth(string mailAddress, CancellationToken? token)
        {
            try
            {
                var userCredential = await GoogleWebAuthorizationBroker.AuthorizeAsync(
                    new ClientSecrets
                    {
                        ClientId = clientId,
                        ClientSecret = clientSecret
                    },
                    new[]
                    {
                    "https://mail.google.com/"
                    },
                    mailAddress,
                    token ?? CancellationToken.None,
                    new FileDataStore("mchMail")
                    );
                return (userCredential.Token.AccessToken, userCredential.Token.RefreshToken);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.ToString());
                throw e;
            }
        }
    }
}
