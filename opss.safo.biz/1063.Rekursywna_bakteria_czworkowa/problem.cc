#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

static const int MAX_LENGTH = 100000;


class Chromosome;

class ChromosomeFactory
{
	private:
		static int index;

	public:
		static void init();
		static Chromosome* create(const char** aInput);
};

class Chromosome
{
	public:
		Chromosome()
		{
			for (int i = 0; i < 4; _cell[i++] = NULL);
		}

		~Chromosome() {}

		int reduce()
		{
			int lifeCycles = 1;

			if (_type == 'S') {
				for (int i = 0; i < 4; i++) {
					if (_cellType[i] == 'S') {
						lifeCycles = max(lifeCycles, _cell[i]->reduce());
						_cellType[i] = _cell[i]->_type;
					}
				}

				if (areAllCellsB()) {
					_type = 'B';
					lifeCycles++;
				} else if (areAllCellsC()) {
					_type = 'C';
					lifeCycles++;
				}
			}

			return lifeCycles;
		}

		void read(const char** aInput)
		{
			_type = **aInput;
			(*aInput)++;

			for (int i = 0; _type == 'S' && i < 4; i++) {
				_cellType[i] = **aInput;
				if (_cellType[i] == 'S') {
					_cell[i] = ChromosomeFactory::create(aInput);
				} else {
					(*aInput)++;
				}
			}
		}

		void write(char** aOutput) const
		{
			*((*aOutput)++) = _type;

			for (int i = 0; _type == 'S' && i < 4; i++) {
				if (_cellType[i] == 'S') {
					_cell[i]->write(aOutput);
				} else {
					*((*aOutput)++) = _cellType[i];
				}
			}
		}

	private:
		char _type;
		Chromosome* _cell[4];
		char _cellType[4];

		bool areAllCellsB() const
		{
			return strncmp(_cellType, "BBBB", 4) == 0;
		}

		bool areAllCellsC() const
		{
			return strncmp(_cellType, "CCCC", 4) == 0;
		}
};



static Chromosome bacteria[MAX_LENGTH / 2];

int ChromosomeFactory::index = 0;

void ChromosomeFactory::init()
{
	index = 0;
}

Chromosome* ChromosomeFactory::create(const char** aInput)
{
	Chromosome* chromosome = bacteria + index++;

	chromosome->read(aInput);
	return chromosome;
}

char input[MAX_LENGTH + 2];
char output[MAX_LENGTH + 2];

void bakteria()
{
	int lifeCycle = 1;
	
	fgets(input, sizeof(input), stdin);

	const char *inputPtr = input;

	ChromosomeFactory::init();
	Chromosome* chromosome = ChromosomeFactory::create(&inputPtr);

	lifeCycle = chromosome->reduce();

	char *outputPtr = output;

	chromosome->write(&outputPtr);
	*outputPtr = 0;

	printf(output);
	printf(" %d\n", lifeCycle);
}


int main()
{
	int c;

	scanf("%d\n", &c);

	while (c--) {
		bakteria();
	}

	return 0;
}
