#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
using namespace std;

class Podroze
{
	private:
		const static int MAX_NUMBER_OF_CITIES = 500000;
		const static int MAX_HIGHWAY_GROUPS = 100000;
		enum begin_end_t { BEGIN, END };

		int numberOfCities;
		int startingCityIndex;

		typedef struct highway_t {
			begin_end_t type;
			int bL, bR;
			int eL, eR;
		};
		highway_t highwayGroups[2 * MAX_HIGHWAY_GROUPS];
		int highwayGroupCount;

		int distances[MAX_NUMBER_OF_CITIES + 1];

		typedef map<int, begin_end_t> covered_area_t;
		covered_area_t coveredArea;






		list< pair<int,int> > addCoveredArea(int l, int r)
		{
			list< pair<int,int> > result;

			{
				covered_area_t::iterator i = coveredArea.lower_bound(l - 1);

				if (i != coveredArea.end() && i->second == END) {
					i--;
					l = i->first;
				}
			}
			{
				covered_area_t::iterator i = coveredArea.upper_bound(r);

				if (i != coveredArea.end() && i->second == END) {
					r = i->first;
				}
			}

			covered_area_t::iterator i = coveredArea.lower_bound(l - 1);
			int lastL = l;
			while (i != coveredArea.end() && i->first <= r) {
				if (lastL <= i->first - 1) {
					result.push_back(make_pair(lastL, i->first - 1));
				}
				coveredArea.erase(i++);
				lastL = i->first + 1;
				coveredArea.erase(i++);
			}

			if (lastL <= r) {
				result.push_back(make_pair(lastL, r));
			}

			coveredArea[l] = BEGIN;
			coveredArea[r] = END;

			return result;
		}

		void printCoveredArea()
		{
			for (covered_area_t::const_iterator i = coveredArea.begin(); i != coveredArea.end(); i++) {
				printf("%d: %s\n", i->first, i->second == BEGIN ? "BEGIN" : "END");
			}
			puts("--------------");
		}

		void printCoveredAreaResult(list< pair<int,int> > r)
		{
			for (list< pair<int,int> >::const_iterator i = r.begin(); i != r.end(); i++)
			{
				printf("%d - %d\n", i->first, i->second);
			}
		}

		void testAddCoveredArea()
		{
			printCoveredAreaResult(addCoveredArea(1, 2));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(3, 4));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(0, 5));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(6, 9));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(4, 8));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(4, 8));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(100, 110));
			printCoveredArea();

			printCoveredAreaResult(addCoveredArea(95, 105));
			printCoveredArea();
		}


		void printHighwayGroups()
		{
			for (int i = 0; i < highwayGroupCount; i++)
			{
				highway_t &hg = highwayGroups[i];
				printf("%d,%d -> %d,%d\n", hg.bL, hg.bR, hg.eL, hg.eR);
			}
		}

	public:
		Podroze(int numberOfCities, int startingCityIndex)
		{
			this->numberOfCities = numberOfCities;
			this->startingCityIndex = startingCityIndex;
			this->highwayGroupCount = 0;
		}
		
		void addHighwayGroup(int bL, int bR, int eL, int eR)
		{
			highway_t &highwayGroupA = highwayGroups[highwayGroupCount++];
			highway_t &highwayGroupB = highwayGroups[highwayGroupCount++];

			highwayGroupB.eL = highwayGroupA.bL = bL;
			highwayGroupB.eR = highwayGroupA.bR = bR;
			highwayGroupB.bL = highwayGroupA.eL = eL;
			highwayGroupB.bR = highwayGroupA.eR = eR;
		}

		int getNumberOfCities()
		{
			return numberOfCities;
		}

		int* solve()
		{
			memset(distances, 0, sizeof(distances));

			queue< pair<int, int> > queueInput;
			queue< pair<int, int> > queueOutput;

			int actualDistance = 0;
			queueInput.push(make_pair(startingCityIndex, startingCityIndex));
			addCoveredArea(startingCityIndex, startingCityIndex);

			while (!queueInput.empty()) {
				while (!queueInput.empty()) {
					int b = queueInput.front().first;
					int e = queueInput.front().second;

					// find highway groups overlapping with range b-e
					// for each highway group take it's destination, execute addCoveredArea and process result 
				}

				queueInput = queueOutput;
				actualDistance++;
			}

			printHighwayGroups();
			testAddCoveredArea();

			return distances;
		}
};


int main()
{
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);

	Podroze podroze(n, p);

	for (int i = 0; i < m; i++)
	{
		int bL, bR, eL, eR;
		scanf("%d %d %d %d", &bL, &bR, &eL, &eR);
		podroze.addHighwayGroup(bL, bR, eL, eR);
	}

	int* result = podroze.solve();
	copy(result, result + podroze.getNumberOfCities(), ostream_iterator<int>(cout, "\n"));

	return 0;
}
