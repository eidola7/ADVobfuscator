//
//  main.cpp
//  ADVobfusctor
//
// Copyright (c) 2010-2014, Sebastien Andrivet
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// To remove Boost assert messages
#if !defined(DEBUG) || DEBUG == 0
#define BOOST_DISABLE_ASSERTS
#endif

#include <iostream>
#include "MetaFactorial.h"
#include "MetaFibonacci.h"
#include "MetaRandom.h"
#include "MetaString1.h"
#include "MetaString2.h"
#include "MetaString3.h"
#include "MetaString4.h"
#include "ObfuscatedCall.h"

using namespace std;
using namespace andrivet::ADVobfuscator;

void SampleFactorial()
{
    cout << "--------------------" << endl;
    cout << "Computation of factorial entirely at compile-time" << endl;
    cout << "Factorial(5) = " << Factorial<5>::value << endl;
}

void SampleFibonacci()
{
    cout << "--------------------" << endl;
    cout << "Computation of Fibonacci sequence entirely at compile-time" << endl;
    cout << "Fibonacci(8)  = " << Fibonacci<8>::value << endl;
    cout << "Fibonacci(20) = " << Fibonacci<20>::value << endl;
}

void SampleEncrypted1()
{
    cout << "--------------------" << endl;
    cout << "Encryption of string literals - version 1 - Fix algorithm, fix key, truncated" << endl;
    cout << "Britney Spears"_obfuscated1 << endl;
    cout << "Miley Cyrus"_obfuscated1 << endl;
    cout << OBFUSCATED1("Katy Perry") << endl;
}

void SampleEncrypted2()
{
    cout << "--------------------" << endl;
    cout << "Encryption of string literals - version 2 - Fix algorithm, fix key, not truncated" << endl;
    cout << OBFUSCATED2("Britney Spears") << endl;
    cout << OBFUSCATED2("Miley Cyrus") << endl;
    cout << OBFUSCATED2("Katy Perry") << endl;
}


void SampleMetaRandom()
{
    // Do not use a loop, it will not work (it will print 10 tims the same number):
    // loops are executed at run-time,
    // we want to generate 10 different numbers are compile-time.
    cout << "--------------------" << endl;
    cout << "Generate random numbers at compile-time" << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
    cout << MetaRandom<__COUNTER__, 10>::value << endl;
}

void SampleEncryped3()
{
    cout << "--------------------" << endl;
    cout << "Encryption of string literals - version 3 - Fix algorithm, random key" << endl;
    cout << OBFUSCATED3("Britney Spears")<< endl;
    cout << OBFUSCATED3("Miley Cyrus") << endl;
    cout << OBFUSCATED3("Katy Perry") << endl;
}

void SampleEncryped4()
{
    cout << "--------------------" << endl;
    cout << "Encryption of string literals - version 4 - Random algorithm, random key" << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
    cout << OBFUSCATED4("Britney Spears") << endl;
}

void SampleEncryped4_differed()
{
    cout << "--------------------" << endl;
    cout << "Encryption of string literals - version 4 - Separated declaration and usage" << endl;

    auto miley   = DEF_OBFUSCATED4("Miley Cyrus");
    auto britney = DEF_OBFUSCATED4("Britney Spears");
    auto katy    = DEF_OBFUSCATED4("Katy Perry");
    
    cout << britney.decrypt() << endl;
    cout << katy.decrypt()    << endl;
    cout << miley.decrypt()   << endl;
}

void SampleEncryped4_simple()
{
    OBFUSCATED4("Britney Spears");
    OBFUSCATED4("Britney Spears");
    OBFUSCATED4("Britney Spears");
    OBFUSCATED4("Britney Spears");
}

void SampleFiniteStateMachine_function_to_protect()
{
    cout << OBFUSCATED4("Womenizer") << endl;
};

int SampleFiniteStateMachine_function_to_protect_with_parameter(const char* text1, const char* text2)
{
    cout << OBFUSCATED4("Oops I ") << text1 << OBFUSCATED4(" it ") << text2 << endl;
    return 12345;
};

void SampleFiniteStateMachine()
{
    cout << "--------------------" << endl;
    cout << "Obfuscate calls by using a finite state machine" << endl;

    cout << "Call a function without parameters and without returning a value" << endl;
    OBFUSCATED_CALL(SampleFiniteStateMachine_function_to_protect);
    
    cout << "Call a function with a parameter and returning a value" << endl;
    int result = OBFUSCATED_CALL_RET(int, SampleFiniteStateMachine_function_to_protect_with_parameter, OBFUSCATED4("did"), OBFUSCATED4("again"));
    cout << "Result: " << result << endl;
}

int main(int argc, const char * argv[])
{
    SampleFactorial();
    SampleFibonacci();
    SampleEncrypted1();
    SampleEncrypted2();
    SampleEncryped3();
    SampleEncryped4();
    SampleEncryped4_differed();
    SampleFiniteStateMachine();
    
    return 0;
}
