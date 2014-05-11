/* @JUDGE_ID: 16232QS 1206 C++ */

#include <iostream>
#include <string>
using namespace std;

class BigInteger {
	public:
		BigInteger()
		{
			*this = 0;
		}

		BigInteger(int aValue)
		{
			*this = aValue;
		}


		BigInteger& operator = (int aValue)
		{
			len = 0;
			do {
				val[len++] = aValue % MAX_VALUE;
				aValue /= MAX_VALUE;
			} while (aValue);
			return *this;
		}


		BigInteger& operator = (const BigInteger& aValue)
		{
			len = aValue.len;
			memcpy(val, aValue.val, sizeof(val));

			return *this;
		}


		BigInteger& operator += (short aValue)
		{
			int a, c = aValue, i;
			for (i = 0; c != 0 && i < MAX_SIZE; i++) {
				a = val[i] + c;
				val[i] = a % MAX_VALUE;
				c = a / MAX_VALUE;
			}
			len = max(i, len);
		}


		BigInteger& operator -= (const BigInteger& aValue)
		{
			int a, c = 0;
			for (int i = 0; i < max(len, aValue.len); i++) {
				a = val[i] - aValue.val[i] + c;
				val[i] = (a + MAX_VALUE) % MAX_VALUE;
				c = a < 0 ? -1 : 0;
#ifdef __DEBUG__
				cout << "-= " << i << ":" << a << ":" << val[i] << endl;
#endif
			}
			normalize(max(len, aValue.len));

			return *this;
		}


		BigInteger& operator *= (unsigned short aValue)
		{
			int c = 0, a = 0;
			for (int i = 0; i < len; i++) {
				a = c + val[i] * aValue;
				val[i] = a % MAX_VALUE;
				c = a / MAX_VALUE;
			}
			if (c > 0) {
				val[len++] = c;
			}
			return *this;
		}


		friend std::ostream& operator << (std::ostream& aOut, const BigInteger& aValue) 
		{
			static char strVal[MAX_LENGTH + 1];
			int index = 0, offset = 0;
			
			for (int i = aValue.len - 1; i >= 0; i--) {
				int a = aValue.val[i];
				for (int j = FIELD_LENGTH - 1; j >= 0; j--) {
					strVal[index + j] = '0' + a % 10;
					a /= 10;
				}
				index += FIELD_LENGTH;
			}
			strVal[index] = 0;

			while (strVal[offset] == '0') offset++;
			if (offset == index) offset--;
			
#ifdef __DEBUG__
			aOut << aValue.len << ":" << strVal + offset;
#else
			aOut << strVal + offset;
#endif
			return aOut;
		}

	private:
		void initialize()
		{
			len = 0;
			memset(val, 0, sizeof(val));
		}

		void normalize(int aOffset) 
		{
			int i = aOffset;
			while (i > 1 && val[i - 1] == 0) i--;
			len = i;
		}

		void normalize() 
		{
			normalize(MAX_SIZE);
		}

		static const int MAX_SIZE     = 100;
		static const int FIELD_LENGTH = 5;
		static const int MAX_LENGTH   = MAX_SIZE * FIELD_LENGTH;
		static const int MAX_VALUE    = 100000;
		int len;
		int val[MAX_SIZE];
};

int main()
{
	int k;
	BigInteger r(36);

	cin >> k;

	while (k-- > 1) {
		r *= 55;
	}

	cout << r << endl;

	return 0;
}
