//Standard library includes
#include <iostream>
#include <algorithm>

//Our project headers
#include "PlayfairCipher.hpp"

using size_tPair = std::pair<size_t,size_t>;

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
    
				
  // Stores the relevant maps
  for(size_t i{0}; i<25; ++i){
    auto coords {std::make_pair(i/5,i%5)}; //The zero indexed coordinates of each letter
    char2coords_.insert(std::make_pair(key_[i],coords)); //Stores the coords of each letter
    coords2char_.insert(std::make_pair(coords, key_[i])); //Stores the letter of each coord
  }
}

std::string PlayfairCipher::applyCipher( \
					const std::string& inputText, \
					const CipherMode cipherMode ) const
{
  std::string input{inputText};

  // Change J → I
  auto j2i = [] (char c){
    if( c== 'J') return 'I';
    else return c;
  };
  std::transform(input.begin(), input.end(), input.begin(), j2i);

  std::string input2{""};
  /* If repeated chars in a digraph add an X or Q if XX and add a trailing Z if
     size of input is odd. Code is slightly complicated due to only needing to 
     add an X for repeating chars in the same diagraph rather than all repeated chars*/
  for(int i{0}; i<input.length(); ++i){
    /* If this if statement is true then the final digraph has been reached
       and it only has one letter */
    if(i == (input.length()-1)){
      input2 += input[i];
      input2 += "Z";
    }
    else if(input[i] == input[i+1]){
      if(input[i] == 'X'){
	input2 += "XQ";
      }
      else{
	input2 += input[i];
	input2 += "X";
      }
    }
    else{
      input2 += input[i];
      input2 += input[i+1];
      ++i; //Both elements of digraph have been added and so increment i twice this loop
    }
  }

  std::string output{""};
  // Loop over the input in Digraphs
  for(int i{0}; i<input2.length(); i+=2){
  
  // - Find the coords in the grid for each digraph
    auto pos1Iter {char2coords_.find(input2[i])};
    size_tPair coord1{(*pos1Iter).second};
    auto pos2Iter {char2coords_.find(input2[i+1])};
    size_tPair coord2{(*pos2Iter).second};

  // - Apply the rules to these coords to get 'new' coords
    const int shift = cipherMode == CipherMode::Encrypt ? 1 : 4 ; //Causes code to encrypt/decrypt
    size_tPair newCoord1;
    size_tPair newCoord2;
    if( coord1.first == coord2.first){ //Same row -> replace with letter to right
      newCoord1 = std::make_pair( coord1.first, (coord1.second + shift) %5);
      newCoord2 = std::make_pair( coord2.first, (coord2.second + shift) %5);
    }
    else if( coord1.second == coord2.second){ //Same column -> replace with letter below
      newCoord1 = std::make_pair( (coord1.first +shift)%5, coord1.second);
      newCoord2 = std::make_pair( (coord2.first +shift)%5, coord2.second);
    }
    else{ //Rectangle -> Replace with corner from same row
      newCoord1 = std::make_pair( coord1.first, coord2.second);
      newCoord2 = std::make_pair( coord2.first, coord1.second);
    }
  // - Find the letter associated with the new coords
    auto letter1Iter {coords2char_.find(newCoord1)};
    char newLetter1 { (*letter1Iter).second};
    output += newLetter1;
    auto letter2Iter {coords2char_.find(newCoord2)};
    char newLetter2 { (*letter2Iter).second};
    output += newLetter2;
  }

  // return the text
  return output;
}
