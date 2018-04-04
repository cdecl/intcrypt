Intcrypt 
======
 
암호화 모듈 

### 개발 환경

#### Linux  
- OS : CentOS 6.7 
- C++ : gnu g++ >= 4.8 (C++11 support)
  - Boost >= 1.58 (asio, system) - [boost 라이브러리](http://www.boost.org/users/history/version_1_58_0.html)
  - Cryptopp >= 5.6.3 - [Cryptopp 라이브러리](https://www.cryptopp.com/)
  - openssl_devel >= 1.0.1 (패키지 설치)
      - yum install openssl_devel

- Java : Java >= 1.7 
  - Jna = 4.2.2 - [Jna 라이브러리](https://github.com/java-native-access/jna)

#### Windows 
- OS : Windows 7
- C++ : Visual Studio 2015 
  - Boost, Cryptopp, OpenSSL 소스 컴파일 및 정적링크 