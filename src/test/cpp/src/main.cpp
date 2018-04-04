

#include <iostream>
using namespace std;

#include <intcrypt.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("url", "test")
{
	char sz[256] = {0,};
	char szr[256] = {0,};

	const char *app = "_0";
	const char *str = "abc";
	const char *estr = "tBg2ScMfq+x8Tr4k8Tq66w==";

	SECTION("URL Domain Test - Encrypt") {
		const char *domain = "https://gist.githubusercontent.com/cdecl/1fe61e63cb7148e3cf6abbd1df40e5dd/raw/86554852acefeb576b8b5ec3aa3261475b908142/key.txt";

		CAPTURE(str);
		REQUIRE(Encrypt(domain, app, str, sz) > 0);
		CAPTURE(sz);

		REQUIRE(strcmp(estr, sz) == 0);

		REQUIRE(Decrypt(domain, app, sz, szr) > 0);
		CAPTURE(szr);
		REQUIRE(strcmp(str, szr) == 0);

		REQUIRE(IsCached(domain) == 1);
	}

	// SECTION("File Domain Test") {
	// 	const char *domain = "../../sample.key";

	// 	CAPTURE(str);
	// 	REQUIRE(Encrypt(domain, app, str, sz) > 0);
	// 	CAPTURE(sz);

	// 	REQUIRE(strcmp(estr, sz) == 0);

	// 	REQUIRE(Decrypt(domain, app, sz, szr) > 0);
	// 	CAPTURE(szr);
	// 	REQUIRE(strcmp(str, szr) == 0);

	// 	REQUIRE(IsCached(domain) == 1);
	// }

	// SECTION("File Domain Test - Encrypt") {
	// 	const char *domain = "../../sample.key.enc";

	// 	CAPTURE(str);
	// 	REQUIRE(Encrypt(domain, app, str, sz) > 0);
	// 	CAPTURE(sz);

	// 	REQUIRE(strcmp(estr, sz) == 0);

	// 	REQUIRE(Decrypt(domain, app, sz, szr) > 0);
	// 	CAPTURE(szr);
	// 	REQUIRE(strcmp(str, szr) == 0);

	// 	REQUIRE(IsCached(domain) == 1);
	// }
}



// void run(int argc, char *argv[], int no)	
// {
// 	char sz[256] = {0,};
// 	char szr[256] = {0,};

// 	const char *domain = argv[1];
// 	const char *app = argv[2];
// 	const char *str = argv[3];

// 	cout << "strlen : " << ::StrLen(str) << endl;
// 	cout << "plain : " << str << endl;
// 	cout << "IsCached : " << IsCached(domain) << endl;

// 	::Encrypt(domain, app, str, sz);
// 	cout << "encrypt : " << sz << endl;
// 	::Decrypt(domain, app, sz, szr);
// 	cout << "decrypt : " <<  szr << endl;
// 	cout << "IsCached : " << IsCached(domain) << endl;

// 	cout << "===============================================" << endl;
// }

// int main(int argc, char *argv[])
// {
// 	if (argc != 4) {
// 		cout << "usage : " << argv[0] << " domain app string" << endl;
// 		return -1;
// 	}

// 	const char *domain = argv[1];
// 	const char *app = argv[2];

// 	cout << ">> domain : " << domain << endl;
// 	cout << ">> app : " << app << endl;

// 	for (int i = 0; i < 3; ++i) {
// 		cout << "> TEST : " << i << endl;
// 		run(argc, argv, i);
// 	}

// 	cout << "end" << endl;

// 	// ::Encrypt("http://iteam.interpark.com/dev.txt", "_0", argv[1], sz);
// 	// cout << "encrypt : " << sz << endl;
// }

