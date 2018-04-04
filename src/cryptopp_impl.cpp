
#include "cryptopp_impl.h"
#include <boost/algorithm/string.hpp>
using namespace std;

#include "http_client.h"
using namespace CryptoPP;

const std::string CryptoppImpl::KEY_HEADER("intcrypt://");
const byte CryptoppImpl::KEY_FILE[] = { byte('I'), byte('N'), byte('T'), byte('C'), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const byte CryptoppImpl::IV_FILE[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, byte('I'), byte('P'), byte('A'), byte('R'), byte('K') };


std::string CryptoppImpl::Encrypt(const std::string &domain, const std::string &app, const std::string &sText)
{
    std::string r;

    KeyType &keys = GetKeyDomain(domain);
    if (keys.find(app) != keys.end()) {
        r = CBC_Encrypt<CryptoPP::AES>(&keys[app].first[0], &keys[app].second[0], sText);
    }

    return r;
}


std::string CryptoppImpl::Decrypt(const std::string &domain, const std::string &app, const std::string &sEnc)
{
    std::string r;

    KeyType &keys = GetKeyDomain(domain);
    if (keys.find(app) != keys.end()) {
        r = CBC_Decrypt<CryptoPP::AES>(&keys[app].first[0], &keys[app].second[0], sEnc);
    }

    return r;
}


CryptoppImpl::KeyReppType& CryptoppImpl::GetKeyReop() 
{
    static KeyReppType repo;
    return repo;
}

CryptoppImpl::KeyType& CryptoppImpl::GetKeyDomain(const std::string &domain)
{
    KeyType keys;
    KeyReppType& repo = GetKeyReop();

    // not eixsts
    if (repo.find(domain) == repo.end()) {

        try {
            const std::string HTTP_ADDR = "http";

            if (domain.length() >= HTTP_ADDR.length() 
                && boost::to_lower_copy(domain.substr(0, HTTP_ADDR.length())) == HTTP_ADDR) 
            {
                std::string body = GetHttp(domain);
                istringstream is(body);
                keys = std::move(GetKey(is));
            }
            else {
                ifstream fin(domain.c_str());
                if (fin) {
                    keys = std::move(GetKey(fin));
                }
            }
        }
        catch (...) {}

        repo.insert(
            std::move(KeyReppType::value_type(domain, std::move(keys)))
        );
    }

    return repo[domain];
}


CryptoppImpl::KeyType CryptoppImpl::GetKey(istream &iss)
{
    using namespace boost;
    const int KEY_SIZE = 16;

    string s;
    vector<string> v;
    KeyType keys;

    while (!iss.eof()) {
        getline(iss, s);

        // encryption key file 
        if (s.find(KEY_HEADER) == 0) {
            std::string enc_string = s.substr(KEY_HEADER.length());
            std::string plain = CBC_Decrypt<CryptoPP::AES>((byte*)KEY_FILE, (byte*)IV_FILE, enc_string);

            istringstream is_(plain);
            return std::move(GetKey(is_));
        }

        v.clear();
        split(v, s, is_any_of(","));

        if (v.size() == 3) {
            string id = trim_copy(v[0]);
            string k = trim_copy(v[1]);
            string iv = trim_copy(v[2]);

            if (!k.empty() && id[0] == '#') continue;
            if (!(k.length() == (KEY_SIZE * 2) && iv.length() == (KEY_SIZE * 2))) continue;

            KeyType::value_type kv = { id, KeyIVType() };

            for (int i = 0; i < KEY_SIZE; ++i) {
                kv.second.first[i] = (byte)stoi(k.substr(i * 2, 2), nullptr, 16);
                kv.second.second[i] = (byte)stoi(iv.substr(i * 2, 2), nullptr, 16);
            }

            keys.insert(std::move(kv));
        }
    }

    return std::move(keys);
}

std::string CryptoppImpl::GetHttp(const string &url)
{
    using namespace GLASS;
    const int PAGE_TIMEOUT = 5000;

    std::string body;
    GLASS::http_service service;
    GLASS::http_client c(service);

    bool b = c.open(url, "", PAGE_TIMEOUT);
    if (b) {
        int status = c.get().get();

        if (status > HTTP_TIMEOUT) {
        //if (status == HTTP_200) {                                        
            http_parser ps = http_parser::parse(c.response());
            body = ps.body().str();
        //}                                                                
        }
    }
    return body;
}

bool CryptoppImpl::EncryptKeyFile(const std::string &plainfile, const std::string &keyfile)
{
    bool r = false;

    try {
        std::ifstream fin(plainfile);
        if (!fin) throw "Not open file";

        std::ostringstream oss;
        std::string s;
        while (!fin.eof()) {
            getline(fin, s);

            if (!s.empty()) {
                oss << s << endl;
            }
        }
        fin.close();

        std::string enc_string = CBC_Encrypt<CryptoPP::AES>((byte*)KEY_FILE, (byte*)IV_FILE, oss.str());

        std::ofstream fout(keyfile);
        fout << KEY_HEADER << enc_string;
        fout.close();

        r = true;
    }
    catch (...) {}


    return r;
}