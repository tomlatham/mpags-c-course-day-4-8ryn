#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <map>

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
   * Apply the cipher to the provided text
   *
   * \param inputText the text to encrypt or decrypt
   * \param cipherMode whether to encrypt or decrypt the input text
   * \return the result of applying the cipher to the input text
   */
  std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;
  
  private:

  /// Type definition for the coordinates in the 5x5 table
  using PlayfairCoords = std::pair<size_t,size_t>;

  /// The cipher key
  std::string key_;

  /// Map of character to the coordinates stored as a zero indexed (row,col) pair
  std::map<char,PlayfairCoords> char2coords_;

  /// Map of the coordinates stored as a zero indexed (row,col) pair to the character
  std::map<PlayfairCoords,char> coords2char_;


  /**
   * Set the value of key_ using the given key
   *
   * \param key the key to set the value of key_ to
   */
  void setKey(const std::string& key);
  
};
  
#endif 
