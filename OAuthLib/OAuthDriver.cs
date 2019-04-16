using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
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
        static TaskSerializer<(string accessToken, string refreshToken)> Serializer { get; } = new TaskSerializer<(string accessToken, string refreshToken)>();

        private string AccessToken { get; set; }
        private string RefreshToken { get; set; }
        private CancellationTokenSource mCancellationTokenSource = new CancellationTokenSource();
        private bool mCompleted = false;
        private Exception mError = null;

        public OAuthDriver()
        {

        }

        [ComVisible(false)]
        public delegate void OnCompletedEventHandler(bool succeeded);

        public event OnCompletedEventHandler OnCompleted;

        public async void Auth(string mailAddress)
        {
            var scheduler = TaskScheduler.Current;
            try
            {
                await Serializer.Execute(mailAddress, () =>
                {
                    return OAuthCore2.Auth(mailAddress, mCancellationTokenSource.Token);
                }).ContinueWith(task =>
                {
                    (AccessToken, RefreshToken) = task.Result;
                    mCompleted = true;
                    OnCompleted?.Invoke(true);
                }, scheduler);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.ToString());
                mError = e;
                new Task(() =>
                {
                    OnCompleted?.Invoke(false);
                }).RunSynchronously(scheduler);
            }
        }

        public void Cancel()
        {
            mError = new OperationCanceledException("cancelled by caller.");
            mCancellationTokenSource.Cancel();
        }

        //public void Update(string accessToken, string refreshToken)
        //{
        //    OnCompleted?.Invoke(false);
        //}

        public string GetAccessToken()
        {
            return mCompleted ? AccessToken : null;
        }

        public string GetRefreshToken()
        {
            return mCompleted ? RefreshToken : null;
        }

        public string GetErrorMessage()
        {
            return mError?.Message ?? "no error.";
        }
    }
}
