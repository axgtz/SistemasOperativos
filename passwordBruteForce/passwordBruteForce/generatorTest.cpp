//
//  generatorTest.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/23/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
#include <iostream>
#include <string>
#include "md5.cpp"

using namespace std;
// Create some alphabet tables

char AlphabetUpper[69] = {'0','1','2','3','4','5','6','7','8','9','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// Recursive function, keeps clocking characters
// until length is reached

bool Generate(unsigned int length, string s, string hash){
    if(length == 0){ // when length has been reached
        if(md5(s) == hash){
            cout << "Se encontro: " << s << "\n";
            return false;
        }
        //cout << s << "\n"; // print it out
        return true;
    }
    // iterate through alphabet
    for(unsigned int i = 0; i < 69; i++){
        // Create new string with next character
        // Call generate again until string has reached it's length
        string appended = s + AlphabetUpper[i];
        if(!Generate(length-1, appended, hash)){
            return false;
        }
    }
    return true;
}

bool static Crack(string hash){
    bool seguir = true;
    while(seguir){
        // Keep growing till I get it right
        static unsigned int stringlength = 1;
        seguir= Generate(stringlength, "", hash);
        if(seguir){
            cout << "No se encontro la palabra en ninguna permutacion con longitud: " << stringlength<< "\n";
        }
        stringlength++;
    }
    return true;
}

int main(){
    Crack("32390fa731a71f4cdcf6b76a05334545");
    return 0;
}
