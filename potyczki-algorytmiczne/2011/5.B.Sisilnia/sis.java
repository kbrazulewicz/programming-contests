
import java.math.BigInteger;
import java.util.Scanner;
import java.io.BufferedInputStream;

class sis
{
	private static BigInteger TWO = new BigInteger("2");

	private static BigInteger calculate(long n)
	{
		BigInteger numberOfZeroes = new BigInteger("0");
		long powerOfFive = 5;

		while (n > powerOfFive) 
		{
			long a = n + 1 - powerOfFive;
			long b = (n + 1) % powerOfFive;
			long x = (a - b) / powerOfFive + 1;

			BigInteger aBI = new BigInteger(Long.toString(a));
			BigInteger bBI = new BigInteger(Long.toString(b));
			BigInteger xBI = new BigInteger(Long.toString(x));

			numberOfZeroes = aBI.add(bBI).multiply(xBI).divide(TWO).add(numberOfZeroes);

			powerOfFive *= 5;
		}

		return numberOfZeroes;
	}

	public static void main(String[] args) 
	{
		Scanner scanner = new Scanner(new BufferedInputStream(System.in));
		final long n = scanner.nextLong();
		scanner.close();

		System.out.println(calculate(n));
		System.exit(0);
	}
}
