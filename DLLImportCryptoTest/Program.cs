using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DLLImportCryptoTest
{
    class Program
    {
        public class BindingDllClass
        {
            [DllImport("CryptApi.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void crypt(IntPtr buf, int msg_len, bool decrypt = false);
        }

        static void Main(string[] args)
        {
            byte[] msg = Encoding.ASCII.GetBytes("Hello Alice.\x00"); //message string should always be null terminated

            IntPtr buf = Marshal.AllocHGlobal(msg.Length);
            for (int k = 0; k < msg.Length; k++)
            {
                Marshal.WriteByte(buf + k, 0x00, msg[k]);
            }
            Console.WriteLine($"Plain Text: {Encoding.ASCII.GetString(msg)}");

            BindingDllClass.crypt(buf, msg.Length);
            for (int k = 0; k < msg.Length; k++)
            {
                msg[k] = Marshal.ReadByte(buf + k);
            }
            Console.WriteLine($"Encrypted Text: {Encoding.UTF8.GetString(msg)}");

            BindingDllClass.crypt(buf, msg.Length, true);
            for (int k = 0; k < msg.Length; k++)
            {
                msg[k] = Marshal.ReadByte(buf + k);
            }
            Console.WriteLine($"Decrypted Text: {Encoding.UTF8.GetString(msg)}");

            Console.ReadLine();
        }
    }
}
