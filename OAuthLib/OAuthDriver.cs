using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OAuthLib
{
    [Guid("5683ED00-A837-446C-8354-F6CAE2C771CB")]
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.AutoDual)]
    //[ComDefaultInterface(typeof(IOAuthDriver))]
    [ComSourceInterfaces(typeof(IOAuthResultEvent))]
    public class OAuthDriver //: IOAuthDriver
    {
        public OAuthDriver()
        {

        }

        [ComVisible(false)]
        public delegate int ResultEventHandler(bool succeeded);

        public event ResultEventHandler OnResult;

        public void Auth()
        {
            OnResult?.Invoke(false);
        }

        public void Update(string accessToken, string refreshToken)
        {
            OnResult?.Invoke(true);
        }

        public string GetAccessToken()
        {
            return "Dummy Access Token";
        }

        public string GetRefreshToken()
        {
            return "Dummy RefreshToken()";
        }

        public string GetErrorMessage()
        {
            return "No Error.";
        }
    }
}
