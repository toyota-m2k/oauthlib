using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OAuthLib
{
    [Guid("93CDD046-E07B-4274-BA76-5F9B467F6D13")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IOAuthResultEvent
    {
        void Result(bool succeeded);
    }
}
