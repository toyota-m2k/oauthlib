using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OAuthLib
{
    [Guid("5683ED00-A837-446C-8354-F6CAE2C771CB")]
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    [ComDefaultInterface(typeof(IOAuthDriver))]
    [ComSourceInterfaces(typeof(IOAuthCompletedEvent))]
    public class OAuthDriver : IOAuthDriver
    {
        private string AccessToken { get; set; }
        private string RefreshToken { get; set; }

        public OAuthDriver()
        {

        }

        [ComVisible(false)]
        public delegate void OnCompletedEventHandler(bool succeeded);

        public event OnCompletedEventHandler OnCompleted;

        public async void Auth()
        {
            var scheduler = TaskScheduler.Current;
            var core = new OAuthCore();
            await core.Auth().ContinueWith(task =>
            {
                bool result = task.Result;
                if(result)
                {
                    AccessToken = core.AccessToken;
                    RefreshToken = core.RefreshToken;
                }
                OnCompleted?.Invoke(result);
            }, scheduler);
        }

        public void Update(string accessToken, string refreshToken)
        {
            OnCompleted?.Invoke(false);
        }

        public string GetAccessToken()
        {
            return AccessToken;
        }

        public string GetRefreshToken()
        {
            return RefreshToken;
        }

        public string GetErrorMessage()
        {
            return "No Error.";
        }
    }
}
