#pragma once

#ifndef	CRYTOPP_IMPLE_H_CDECL 
#define CRYTOPP_IMPLE_H_CDECL

#include <cstdio>
#include <fstream>
#include <sstream>
#include <array>
#include <map>


// Crypto++ Includes
#include "cryptopp/cryptlib.h"
#include "cryptopp/base64.h"
#include "cryptopp/aes.h"        
#include "cryptopp/seed.h"
#include "cryptopp/des.h"
#include "cryptopp/modes.h"      
#include "cryptopp/filters.h"    


class CryptoppImpl 
{
public:
	using byte = unsigned char;
	using KeyIVType = std::pair<std::array<byte, 16>, std::array<byte, 16>>;
	using KeyType = std::map<std::string, KeyIVType>;
	using KeyReppType = std::map<std::string, KeyType>;

private:
	static const std::string KEY_HEADER;
	static const byte KEY_FILE[];
	static const byte IV_FILE[];
	

private:
	template <class TyMode>
	static std::string Encrypt(TyMode &Encryptor, const std::string &PlainText)
	{
		std::string EncodedText;

		try {
			CryptoPP::StringSource(PlainText, true,
				new CryptoPP::StreamTransformationFilter(Encryptor,
					new CryptoPP::Base64Encoder(
						new CryptoPP::StringSink(EncodedText), false
						), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
					)
				);
		}
		catch (...) {}

		return EncodedText;
	}

	template <class TyMode>
	static std::string Decrypt(TyMode &Decryptor, const std::string &EncodedText)
	{
		std::string RecoveredText;

		try {
			CryptoPP::StringSource(EncodedText, true,
				new CryptoPP::Base64Decoder(
					new CryptoPP::StreamTransformationFilter(Decryptor,
						new CryptoPP::StringSink(RecoveredText),
						CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
						)
					)
				);
		}
		catch (...) {}

		return RecoveredText;
	}


public:
	template <class Ty>
	static std::string CBC_Encrypt(byte *KEY, byte *IV, const std::string &PlainText)
	{
		typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
		return Encrypt(Encryptor, PlainText);
	}


	template <class Ty>
	static std::string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText)
	{
		typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
		return Decrypt(Decryptor, PlainText);
	}

	template <class Ty>
	static std::string ECB_Encrypt(byte *KEY, const std::string &PlainText)
	{
		typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
		return Encrypt(Encryptor, PlainText);
	}


	template <class Ty>
	static std::string ECB_Decrypt(byte *KEY, const std::string &PlainText)
	{
		typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
		return Decrypt(Decryptor, PlainText);
	}

	static std::string Encrypt(const std::string &domain, const std::string &app, const std::string &sText);
	static std::string Decrypt(const std::string &domain, const std::string &app, const std::string &sEnc);

	static bool EncryptKeyFile(const std::string &plainfile, const std::string &keyfile);

	static int ExistsKey(const std::string &domain, const std::string &app) 
	{
		int result = 0;
		KeyType& keys = GetKeyDomain(domain);
		if (keys.find(app) != keys.end()) {
			result = 1;
		}

		return result;
	}

	static int DeleteCached() 
	{
		int result = 0;

		KeyReppType& repo = GetKeyReop();
    	result = static_cast<int>(repo.size());

    	repo.clear();
		return result;
	}

	static int IsCached(const std::string &domain) 
	{
		int result = 0;

		KeyReppType& repo = GetKeyReop();
    	// eixsts
		if (repo.find(domain) != repo.end()) {
			result = 1;
		}

		return result;
	}


private:
	static KeyReppType& GetKeyReop();
	static KeyType& GetKeyDomain(const std::string &domain);
	static KeyType GetKey(std::istream &iss);
	static std::string GetHttp(const std::string &url);

};



#endif