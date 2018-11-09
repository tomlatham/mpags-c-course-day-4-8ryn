//Standard library includes
#include <iostream>
#include <algorithm>

//Our project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher(const std::string& key){
  setKey(key);
}

void PlayfairCipher::setKey(const std::string& key){
  // store the original key
  key_ = key;

  // Append the alphabet
  key_ += "ABCDEFGHIKLMNOPQRSTUVWXYZ";

  // Make sure the key is upper case
  std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
  
  // Remove non-alpha characters
  auto alphaIter = std::remove_if(key_.begin(), key_.end(), [] (char c) {return !std::isalpha(c);});
  key_.erase(alphaIter,key_.end());
  
  // Change J -> I
  auto j2i = [] (char c){
    if( c== 'J') return 'I';
    else return c;
  };
  std::transform(key_.begin(), key_.end(), key_.begin(), j2i);

  
  // Remove duplicated letters
  std::string encountered{};
  auto rmDup = [&] (char c){
    if (encountered.find(c) == std::string::npos){
      encountered += c;
      return false;
    }
    else return true;
  };
  auto dupIter = std::remove_if(key_.begin(), key_.end(), rmDup);
  key_.erase(dupIter, key_.end());
  std::cout << key_ << std::endl;
  
				
  // Store the coords of each letter

  // Store the playfair cipher key map
}

std::string PlayfairCipher::applyCipher( \
					const std::string& inputText, \
					const CipherMode cipherMode ) const
{
  std::string input{inputText};
  // Change J → I

  // If repeated chars in a digraph add an X or Q if XX

  // if the size of input is odd, add a trailing Z

  // Loop over the input in Digraphs

  // - Find the coords in the grid for each digraph
  // - Apply the rules to these coords to get 'new' coords
  // - Find the letter associated with the new coords
  // return the text

  std::cerr<< "[warning] Playfair Cipher in not yet implemented input returned" << std::endl;
  
  return input;
}
