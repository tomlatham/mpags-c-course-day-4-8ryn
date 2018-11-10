//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Playfair Cipher encryption", "[playfair]"){
  PlayfairCipher cipher{"testplayfairj"};
  REQUIRE(cipher.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "CLPZPQXNHRHW");
}

TEST_CASE("Playfair XX encryption", "[playfair]"){
  PlayfairCipher cipher{"testplayfair"};
  REQUIRE(cipher.applyCipher("XXX", CipherMode::Encrypt) == "ZOZOZU");
}

TEST_CASE("Playfair Cipher decryption", "[playfair]"){
  PlayfairCipher cipher{"testplayfairj"};
  REQUIRE(cipher.applyCipher("CLPZPQXNHRHW", CipherMode::Decrypt) == "HELXLOWORLDZ");
}
