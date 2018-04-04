


#include "intcrypt.h"
#include "cryptopp_impl.h"


extern "C"
int ExistsKey(const char* domain, const char* app)
{
    return CryptoppImpl::ExistsKey(domain, app);
}

extern "C"
int IsCached(const char* domain)
{
    return CryptoppImpl::IsCached(domain);
}

int DeleteCached() 
{
    return CryptoppImpl::DeleteCached();
}

extern "C"
int Encrypt(const char* domain, const char* app, const char*plain, char *enc)
{
    std::string r = CryptoppImpl::Encrypt(domain, app, plain);
    strcpy(enc, r.c_str());

    return (int)r.length();
}

extern "C"
int Decrypt(const char* domain, const char* app, const char *enc, char *plain)
{
    std::string r = CryptoppImpl::Decrypt(domain, app, enc);
    strcpy(plain, r.c_str());

    return (int)r.length();
}

extern "C"
int ConvertKeyFile(const char* plainfile, const char* keyfile)
{
    bool b = CryptoppImpl::EncryptKeyFile(plainfile, keyfile);
    return b ? 1 : 0;
}