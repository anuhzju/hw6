#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string lowerCaseK;
        for (char c : k){
          if (c >= 'A' && c <= 'Z'){
            lowerCaseK += c + ('a' - 'A');
          }
          else {
            lowerCaseK += c;
          }
        }

        unsigned long long w[5] = {0};
        int chunkIndex = 4;

        for (int i = static_cast<int>(lowerCaseK.size()); i > 0 && chunkIndex >= 0; i -= 6, --chunkIndex){
          unsigned long long value = 0;

          for (int j = std::max(0, i-6); j < i; ++j){
            value = value * 36 + letterDigitToNumber(lowerCaseK[j]);
          }

          w[chunkIndex] = value;
        }

        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i){
          hash += static_cast<unsigned long long>(rValues[i] * w[i]);
        }

        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z'){
          return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9'){
          return letter - '0' + 26;
        }
        return 0; 
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
