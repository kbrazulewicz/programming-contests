/* @JUDGE_ID: 16232QS 1600 C */

#include <stdio.h>

#define MAX_N 500

struct object_t {
	int index;
	double x, y, z;
	double vx, vy, vz;
} objects[MAX_N];

int main()
{
	int n;
	double r;
	int i, j;
	char alarm = 0;

	scanf("%d%lf", &n, &r);
	for (i = 0; i < n; ++i) {
		scanf("%lf%lf%lf%lf%lf%lf", 
				&objects[i].x, &objects[i].y, &objects[i].z,
				&objects[i].vx, &objects[i].vy, &objects[i].vz);
	}

	/**
	 * for each pair A & B:
	 * shift coordinates so A is (0; 0; 0) and B is (xb - xa, yb - ya, zb - za)
	 * make A non-moving and B velocity is (vxb - vxa, vyb - vya, vzb - vza)
	 */
	for (i = 0; i < n && alarm == 0; ++i) {
		for (j = i + 1; j < n && alarm == 0; ++j) {
			/* for each pair A & B */
			double x, y, z;
			double vx, vy, vz;
			double a, b, c, d, s, s1, s2;

			/* shift coordinates so A is (0; 0; 0) and B is (xb - xa; yb - ya; zb - za) */
			x  = objects[j].x - objects[i].x;
			y  = objects[j].y - objects[i].y;
			z  = objects[j].z - objects[i].z;
			/* compensate velocity so A is non-moving and B velocity is (vxb - vxa, vyb - vya, vzb - vza) */
			vx = objects[j].vx - objects[i].vx;
			vy = objects[j].vy - objects[i].vy;
			vz = objects[j].vz - objects[i].vz;

			/* solve 2nd level equation for crossing the d-radius sphere and accept minimal positive solution */
			a = vx * vx + vy * vy + vz * vz;
			b = 2 * (x * vx + y * vy + z * vz);
			c = x * x + y * y + z * z - r * r;

			/* check if solution exists */
/*			if (b * b < 4 * a * c) continue; */
			/* check if not a double negative solution */
/*			if (c * a > 0.0 && b * a > 0.0) continue; */

			d = b * b - 4 * a * c;

			if (d < -0.000000000001) continue;

			s1 = (-b - sqrt(d)) / (2 * a);
			s2 = (-b + sqrt(d)) / (2 * a);
			if (s1 < 0.000000000001 && s2 < 0.000000000001) continue;

			s = (s1 < 0.000000000001) ? s2 : (s2 < 0.000000000001) ? s1 : (s1 < s2) ? s1 : s2;

			alarm = 1;

			printf("ALARM!\n%.3f %d %d\n", s, i + 1, j + 1);

		}
	}

	if (alarm == 0) {
		puts("OK");
	}

	return 0;
}
