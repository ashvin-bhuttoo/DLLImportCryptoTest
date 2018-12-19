# DLLImportCryptoTest

Calling a Simple C++ Crypto Library from .NET using DLLImport 

<b>The methods from Simple C++ Crypto Library can be imported using DLLImport, only the crypt(..) method was imported</b><br/>
[DllImport("CryptApi.dll", CallingConvention = CallingConvention.Cdecl)]<br/>
public static extern void crypt(IntPtr buf, int msg_len, bool decrypt = false);

<b>Notice the definition of crypt differs from in .NET Import, the first parameter char* was replaced with IntPtr</b><br/>
extern "C" __declspec(dllexport) void crypt(char* buf, int msg_len, bool decrypt);

<b>Unmanaged memory is used to work with the unmanaged type char*, The Marshal class was used to Allocate and Populate the value at the specified IntPtr -> buf</b><br/>
IntPtr buf = Marshal.AllocHGlobal(msg.Length);<br/>
Marshal.WriteByte(buf + k, 0x00, msg[k]);
