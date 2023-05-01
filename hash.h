#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
		size_t len = k.length();
		std::vector<std::vector<int>> W;
		
		size_t l;
		if(len % 6 == 0)
			l = len/6;
		else
			l = len/6+1;

		//creates vector of w accurate number of 6-digit arrays w_ initialized to 0
		for(size_t i=0; i < l; i++)
		{
			std::vector<int> w(6, 0);
			W.push_back(w);
		}

		int vl = W.size(); //1
		int counter = len-1; //2
		int wresCounter = 4;
		std::vector<unsigned long long> wres(5, 0);
		//puts each char as a digit into the proper array in the vector
		for(int i=vl-1; i>=0; i--)
		{
			if(counter < 0)
				break;
			for(int j=5; j>-1; j--)
			{
				if(counter >= 0)
				{
					int digit = letterDigitToNumber(k[counter]);
					W[i][j] = digit;
					counter--;
				}
			}
			//finds our w[i] values 
			unsigned long long decVal = 0;
			for (auto digit : W[i])
        decVal = decVal * 36 + digit;
			//using wres[i] as w[i] from instructions
			wres[wresCounter] = decVal;
			wresCounter--;
		}

		HASH_INDEX_T result =  rValues[0] * wres[0]
													+rValues[1] * wres[1]
													+rValues[2] * wres[2]
													+rValues[3] * wres[3]
													+rValues[4] * wres[4];
		
		return result;
	}

	// A likely helper function is to convert a-z,0-9 to an integral value 0-35
	HASH_INDEX_T letterDigitToNumber(char letter) const
	{
			// Add code here or delete this helper function if you do not want it
			if(letter >= 'A')
			{
				letter = tolower(letter);
				return static_cast<int>(letter) - 'a';
			}
			else
				return static_cast<int>(letter) - '0' + 26;

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
