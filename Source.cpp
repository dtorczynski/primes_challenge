#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

bool input_test(const int &k) {
	return k > 0;
}

bool primes_test(const vector<int> &n_primes) {
	int primes[20] = { 2,  3,  5,  7, 11, 
		              13, 17, 19, 23, 29, 
					  31, 37, 41, 43, 47, 
					  53, 59, 61, 67, 71};

	bool result = true;
	// Test Up to First 20 Primes are Correct
	for (int i = 0; i < 20 && i < n_primes.size()-1; i++ ) {
		if (primes[i] != n_primes[i+1]) {
			result = false;
			break;
		}
	}
	return result;
}

vector<int> sieve_of_eratosthenes(const int &numPrimes) {
  // Nth prime approximation
  // Source: https://en.wikipedia.org/wiki/Prime_number_theorem#Approximations_for_the_nth_prime_number
  int prime_ceiling;
  vector<int> primes;
	
  // Put on 1 to print primes in table
  primes.emplace_back(1);
  primes.emplace_back(2);
  prime_ceiling = ceil(numPrimes * log( numPrimes ) + 
                       numPrimes * log( log ( numPrimes )));
		                 
  // Skip 0,1,2, and all evens when sizing
  int sieve_size = floor ( 0.5 * (prime_ceiling - 3) ) + 1;
    
  // is_prime[i] represents whether or not (2i + 3) is a prime
  vector<bool> is_prime(sieve_size, true);
	
  for (int i = 0; i < sieve_size; i++) {
    if (is_prime[i]) {
      int prime = (i << 1) + 3;
      primes.emplace_back(prime);
      // Start sieve at prime^2 or index (prime^2 - 3) / 2
      for (int j = (((prime * prime) - 3) >> 1); j < sieve_size; j +=prime ) {
        is_prime[j] = false;
      }
    }
  }
	
  return primes;
}

void print_prime_table(const vector<int> &n_primes, const int &numPrimes) {
  for (int i = 0; i < numPrimes+1; i++) {
    for (int j = 0; j < numPrimes+1; j++) {
      if (i != 0 || j != 0) {
        printf("|%5d", n_primes[i]*n_primes[j]);
      } else {
        printf("|     ");
      }
    }
    printf("|\n");
  }
}

int main() {
	
  // Initialize variables
  int first_primes[7] = {1,2,3,5,7,11,13};
  vector<int> n_primes; 
  int numPrimes = 10, prime_ceiling = 1;
  string input;	
  // Prompt user for desired number of primes, with 10 used as default
  cout << "Enter number of desired primes, must be greater than 0 (default is 10): " ;
  do {
    getline(cin,input);
	if (!input.empty()) {
	  numPrimes = stoi(input);
	}
  } while (numPrimes <= 0);	

  if (numPrimes <= 6) {
    for (int i = 0; i < numPrimes+1; i++) {
      n_primes.emplace_back(first_primes[i]);
    }
  } else {
    n_primes = sieve_of_eratosthenes(numPrimes);
  }

  print_prime_table(n_primes, numPrimes);


  //-- Test Section --// 
  cout << "\nTest Result: " << input_test(numPrimes) && primes_test(n_primes);
  getline(cin,input);	
  return 0;
}