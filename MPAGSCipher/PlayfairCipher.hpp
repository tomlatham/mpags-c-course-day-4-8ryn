#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFARICIPHER_HPP

// Standard library includes
#include <string>

// Our project header
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher{

  public:
  /**
   * Create a new PlayfairCipher with the given key
   *
   * \param key the key to use in the cipher
   */
  explicit PlayfairCipher(const std::string& key);

  /**
   * Set the value of _key with the given key
   *
   * \param key the key to set the value of _key to
   */
  void setKey(const std::string& key);

  /**
   * Apply the cipher to the provided text
   *
   * \param inputText the text to encrypt or decrypt
   * \param cipherMode whether to encrypt or decrypt the input text
   * \return the result of applying the cipher to the input text
   */
  std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;
  
  private:
  std::string key_;

};
  
#endif 
