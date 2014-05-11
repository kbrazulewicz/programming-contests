#include <math.h>
#include <stdio.h>
#include <time.h>

int main()
{
	long long unsigned int encryptedInput;
	long long unsigned int guess;
	time_t decryptedInput;
	unsigned int n = 0;
	scanf("%Ld", &encryptedInput);

	guess = sqrt(encryptedInput);
	while (guess * guess != encryptedInput) {
		encryptedInput += 4000000007U;
		guess = sqrt(encryptedInput);
		n++;
	}

	decryptedInput = guess;

	printf("%u: %ld: %s", n, decryptedInput, asctime(gmtime(&decryptedInput)));

	return 0;
}
