#include <iostream>

#include <iterator>
#include <vector>

using namespace std;

int solution_00[] = {8, 1, 5, 0};
int solution_01[] = {3, 6, 0, 8, 2};
int solution_02[] = {17, 0, 13, 3, 14, 9, 13, 8};
int solution_03[] = {};
int solution_04[] = {};
int solution_05[] = {};
int solution_06[] = {};
int solution_07[] = {};
int solution_08[] = {};
int solution_09[] = {};
int solution_10[] = {};

vector< vector<int> > solution;

int main()
{
	int k;
	cin >> k;

	solution.push_back(vector<int>(solution_00, solution_00 + sizeof(solution_00) / sizeof(int)));
	solution.push_back(vector<int>(solution_01, solution_01 + sizeof(solution_01) / sizeof(int)));
	solution.push_back(vector<int>(solution_02, solution_02 + sizeof(solution_02) / sizeof(int)));
	solution.push_back(vector<int>(solution_03, solution_03 + sizeof(solution_03) / sizeof(int)));
	solution.push_back(vector<int>(solution_04, solution_04 + sizeof(solution_04) / sizeof(int)));
	solution.push_back(vector<int>(solution_05, solution_05 + sizeof(solution_05) / sizeof(int)));
	solution.push_back(vector<int>(solution_06, solution_06 + sizeof(solution_06) / sizeof(int)));
	solution.push_back(vector<int>(solution_07, solution_07 + sizeof(solution_07) / sizeof(int)));
	solution.push_back(vector<int>(solution_08, solution_08 + sizeof(solution_08) / sizeof(int)));
	solution.push_back(vector<int>(solution_09, solution_09 + sizeof(solution_09) / sizeof(int)));
	solution.push_back(vector<int>(solution_10, solution_10 + sizeof(solution_10) / sizeof(int)));

	cout << solution[k].size() << endl;

	copy(solution[k].begin(), solution[k].end(), ostream_iterator<int>(cout, "\n"));

	return 0;
}
