#include <cstdio>
#include <list>
#include <math.h>
#include <string>
using namespace std;

long long int A[2], B[2], C[2];
double D[3];

long long int dotProduct(long long int a[2], long long int b[2])
{
	return (-b[0]) * (-b[1]) + a[0] * a[1];
}

long long int crossProductLength(long long int a[2], long long int b[2])
{
	return (-b[0]) * a[1] - a[0] * (-b[1]);
}


class Candidate {
	public:
		Candidate(long long int aX, long long int aY)
		{
			x = aX;
			y = aY;
			distance = 0.0;
		}

		bool operator < (const Candidate& rhs) 
		{
			return distance < rhs.distance;
		}

		long long int x;
		long long int y;
		double distance;
};

class DoublePoint {
	public:
		double x;
		double y;
};
class DoubleVector {
	public:
		double x;
		double y;

		void reverse() 
		{
			x = -x;
			y = -y;
		}
};

int main()
{
	long long int rX, rY;
	DoublePoint oPoint;
	DoubleVector oVector, vA, vB;

	list<Candidate> candidates;

	scanf("%Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld", &A[0], &B[0], &C[0], &A[1], &B[1], &C[1], &rX, &rY);

	if (B[0] != 0) D[0] = - (double) A[0] / (double) B[0];
	if (B[1] != 0) D[1] = - (double) A[1] / (double) B[1];

	candidates.push_back(Candidate(rX, rY));

	long long int cpl = crossProductLength(A, B);

	oPoint.x = (C[0] * B[1] - C[1] * B[0]) / - cpl;
	oPoint.y = (C[1] * A[0] - C[0] * A[1]) / - cpl;

	oVector.x = rX; oVector.y = rY;
	oVector.x -= oPoint.x; oVector.y -= oPoint.y;

	if (oVector.x == 0) {
		if (D[0] > D[1]) {
			vA.x = -B[0]; vA.y =  A[0];
			vB.x = -B[1]; vB.y =  A[1];
		} else {
			vA.x = -B[1]; vA.y =  A[1];
			vB.x = -B[0]; vB.y =  A[0];
		}

		if ((oVector.y > 0 && vA.x > 0) || (oVector.y < 0 && vA.x < 0)) 
			vA.reverse();
		if ((oVector.y > 0 && vB.x < 0) || (oVector.y < 0 && vB.x > 0)) 
			vA.reverse();
	} else {
		D[2] = oVector.y / oVector.x;
		if (B[0] == 0) {
			
		} else if (B[1] == 0) {
		} else {
		}
	}



	bool needSwap = false;

	if (B[1] == 0) needSwap = true;
	else if (B[0] != 0) {
		D[0] = (double) A[0] / (double) - B[0];
		D[1] = (double) A[1] / (double) - B[1];

		if (fabs(D[1]) > fabs(D[0])) needSwap = true;
	}

	if (needSwap) {
		swap(A[0], A[1]);
		swap(B[0], B[1]);
		swap(C[0], C[1]);
		swap(D[0], D[1]);
	}

	long long int dp  = dotProduct(A, B);





	long long int V[2];

	V[0] = A[0] * rX + B[0] * rY + C[0];
	V[1] = A[1] * rX + B[1] * rY + C[1];

	V[0] = V[0] > 0 ? 1 : -1;
	V[1] = V[1] > 0 ? 1 : -1;

	double cosAlpha = dp;
	cosAlpha /= sqrt(A[0] * A[0] + B[0] * B[0]) * sqrt(A[1] * A[1] + B[1] * B[1]);

	printf("dp [%lld] cpl [%lld]\n", dp, cpl);
	printf("1st line %lld %lld %lld %f\n", A[0], B[0], C[0], D[0]);
	printf("2nd line %lld %lld %lld %f\n", A[1], B[1], C[1], D[1]);
	printf("%f %f | %lld %lld | %f\n", oX, oY, V[0], V[1], cosAlpha);

	if (cosAlpha > 0) {
		printf("narrow angle\n");

		printf("1st line %lld %lld %lld %f\n", A[0], B[0], C[0], D[0]);
		printf("2nd line %lld %lld %lld %f\n", A[1], B[1], C[1], D[1]);
		printf("%f %f | %lld %lld\n", oX, oY, V[0], V[1]);

		double xCoefficient = A[1] * B[0] - A[0] * B[1];
		xCoefficient /= B[0] * B[1];

		double yCoefficient = B[1] * A[0] - B[0] * A[1];
		yCoefficient /= A[0] * A[1];
	} else {
		long long int llOX = floor(oX);
		long long int llOY = floor(oY);

		for (int i = -1; i <= 2; i++) {
			for (int j = -1; j <= 2; j++) {
				candidates.push_back(Candidate(llOX + i, llOY + j));
			}
		}
	}


	{
		list<Candidate>::iterator i = candidates.begin();
		while (i != candidates.end()) {
			long long int cV[2];

			cV[0] = A[0] * i->x + B[0] * i->y + C[0];
			cV[1] = A[1] * i->x + B[1] * i->y + C[1];

			if (cV[0] * V[0] <= 0 || cV[1] * V[1] <= 0) {
				i = candidates.erase(i);
			} else {
				double dX = oX - i->x, dY = oY - i->y;
				i->distance = sqrt(dX * dX + dY * dY);
				i++;
			}
		}
	}

	candidates.sort();

	if (!candidates.empty()) {
		printf("%lld %lld\n", candidates.front().x, candidates.front().y);
	}
	
	return 0;
}
