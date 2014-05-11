#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


unsigned int potegaArray0[10]  = 
{
    1, 2, 4, 8, 6, 2, 4, 8, 6, 2
};
unsigned int potegaArray1[20] = 
{
    6, 2, 4, 8, 6, 2, 4, 8, 6, 2,
    4, 8, 6, 2, 4, 8, 6, 2, 4, 8
};



unsigned int potega0(const string& value) 
{
    if (value.size() == 1) {
        return potegaArray0[value[0] - '0'];
    }
    else {
        const char *twoDigits = value.c_str() + value.size() - 2;
        return potegaArray1[atoi(twoDigits) % 20];
    }
}




int main() 
{
    string input;

    cin >> input;
    cout << potega0(input);

    return 0;
}
