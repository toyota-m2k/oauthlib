﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OAuthLib
{
    [Guid("5451A7AC-2576-4ADC-9E53-ECF29D3BB188")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IOAuthDriver
    {
        [DispId(1)]
        void Auth(string mailAddress);

        [DispId(2)]
        void Cancel();

        [DispId(3)]
        string GetAccessToken();

        [DispId(4)]
        string GetRefreshToken();

        [DispId(5)]
        string GetErrorMessage();
    }
}
