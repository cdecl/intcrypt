#pragma once

#ifndef	INTCRYPT_H_CDECL
#define INTCRYPT_H_CDECL

extern "C" { 
	int ExistsKey(const char* domain, const char* app);
	int IsCached(const char* domain);
	int DeleteCached();

	int Encrypt(const char* domain, const char* app, const char *plain, char *enc);
	int Decrypt(const char* domain, const char* app, const char *enc, char *plain);

	int ConvertKeyFile(const char* plainfile, const char* keyfile);

}

#endif