
import com.sun.jna.Library;
import com.sun.jna.Native;

interface libcrypto extends Library {
    int ExistsKey(String domain, String app);
    int IsCached(String domain);
    int DeleteCached();
    int Encrypt(String domain, String app, byte[] plain, byte[] enc);
    int Decrypt(String domain, String app, String enc, byte[] plain);

}

public class main {

    static final String DLL_PATH = "intcrypt";
    static libcrypto lib = (libcrypto) Native.loadLibrary(DLL_PATH, libcrypto.class);

    static String Encrypt(String domain, String app, String plain) {
        byte[] buf = new byte[256];

        try {
            int r = lib.Encrypt(domain, app, Native.toByteArray(plain, "euc-kr"), buf);
        } catch (Exception e) {}

        return Native.toString(buf);
    }

    static String Decrypt(String domain, String app, String enc) {
        byte[] buf = new byte[256];
        int r = lib.Decrypt(domain, app, enc, buf);
        String rv = "";

        try {
            rv = Native.toString(buf, "euc-kr");
        } catch (Exception e) {}

        return rv;
    }

    public static void main(String[] args) {

        if (args.length != 3) {
            System.out.println("usage : java main domain app str");
            return ;
        }

        String str = args[2];

        System.out.printf("domain : %s \n", args[0]);
        System.out.printf("app : %s \n", args[1]);

        for (int i = 0; i < 2; ++i) {
            System.out.printf("TEST %d \n", i);
            System.out.printf("    IsCached : %d \n", lib.IsCached(args[0]));

            System.out.printf("    plan text : %s / ", str);

            String sEnc = Encrypt(args[0], args[1], str);
            System.out.printf("encrypt: %s / ", sEnc);

            String sPlain = Decrypt(args[0], args[1], sEnc);
            System.out.printf("decrypt: %s \n", sPlain);

            System.out.printf("    IsCached : %d \n", lib.IsCached(args[0]));

            System.out.println("===============================================\n");

        }
    }
}

