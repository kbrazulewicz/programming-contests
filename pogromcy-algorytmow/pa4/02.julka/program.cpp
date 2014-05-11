#include <stdexcept>
#include <iostream>

namespace math {

	template<int N = 256>
		class BigInteger
		{
			public:
				BigInteger()
				{
					clear();
				};
				
				void assign(const std::string& aValue) throw (std::length_error)
				{
					if (aValue.size() > N) 
						throw std::length_error("BigInteger::assign: value too long");

					clear();
					int size = aValue.size();
					int offset = N - size;
					for (int i = 0; i < size; i++)
						bytes[i + offset] = aValue[i] - '0';
				};

				void clear()
				{
					memset(bytes, 0, sizeof(bytes));
				};

				void div2()
				{
					int cf = 0;

					for (int i = 0; i < N; i++) {
						bytes[i] += 10 * cf;
						cf = bytes[i] % 2;
						bytes[i] >>= 1;
					}
				};

				template<int K>
					BigInteger<K> operator + (const BigInteger<K>& rhs)
					{
						BigInteger<K> k(*this);
						k += rhs;
						return k;
					}

				template<int K>
					BigInteger<K>& operator += (const BigInteger<K>& rhs)
					{
						int cf = 0;
						for (int i = K - 1; i >= 0; i--) {
							bytes[i] += rhs.bytes[i] + cf;
							cf = bytes[i] > 9 ? 1 : 0;
							bytes[i] %= 10;
						}
						if (cf) 
							throw std::overflow_error("BigInteger::operator += : overflow error");
					}

				template<int K>
					BigInteger<K> operator - (const BigInteger<K>& rhs)
					{
						BigInteger<K> k(*this);
						k -= rhs;
						return k;
					}

				template<int K>
					BigInteger<K>& operator -= (const BigInteger<K>& rhs)
					{
						int cf = 0;
						for (int i = K - 1; i >= 0; i--) {
							bytes[i] = 10 + bytes[i] - rhs.bytes[i] - cf;
							cf = bytes[i] <= 9 ? 1 : 0;
							bytes[i] %= 10;
						}
						if (cf) 
							throw std::overflow_error("BigInteger::operator += : overflow error");
					}
					
				template<int K>
					friend std::ostream& operator << (std::ostream& os, const BigInteger<K>& bi);

			private:
				// [0]     - MSB
				// [N - 1] - LSB
				unsigned char bytes[N];
		};

	template<int N>
	std::ostream& operator<<(std::ostream& os, const BigInteger<N>& bi)
	{
		int i = -1;
		while (i < N && !bi.bytes[++i]);
		if (i == N) {
			os << '0';
		} else {
			while (i < N) os << (char) (bi.bytes[i++] + '0');
		}

		return os;
	};

} // namespace math

using namespace std;

int main()
{
	string sJablka;
	string sRoznica;

	math::BigInteger<101> jablka;
	math::BigInteger<101> roznica;
	math::BigInteger<101> klaudia;
	math::BigInteger<101> natalia;

	cin >> sJablka >> sRoznica;
	
	jablka.assign(sJablka);
	roznica.assign(sRoznica);
	klaudia = jablka + roznica;
	klaudia.div2();
	natalia = jablka - klaudia;

	cout << klaudia << endl << natalia << endl;
	return 0;
}
