//
//  test.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/24/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
//
#include <iostream>
#include <string>

// Create some alphabet tables

const char AlphabetUpper[26] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z'
};

const char AlphabetLower[26] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z'
};

// Recursive function, keeps clocking characters
// until length is reached

void Generate(unsigned int length, std::string s)
{
    if(length == 0) // when length has been reached
    {
        std::cout << s << "\n"; // print it out
        return;
    }
    
    for(unsigned int i = 0; i < 26; i++) // iterate through alphabet
    {
        // Create new string with next character
        // Call generate again until string has reached it's length
        std::string appended = s + AlphabetLower[i];
        Generate(length-1, appended);
    }
}

void Crack()
{
    while(1){
        // Keep growing till I get it right
        static unsigned int stringlength = 1;
        Generate(stringlength, "");
        stringlength++;
    }
}

int main()
{
    std::cerr << "Attempting to crack...";
    Crack();
    return 0;
}



