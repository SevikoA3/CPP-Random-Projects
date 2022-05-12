#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    unsigned long long n;
    int steps = 0;
    unsigned long long highest = 0;
    cout << "Enter a number: ";
    cin >> n;
    while (n != 1){
        n % 2 == 0 ? n /= 2 : n = 3 * n + 1;
        n > highest ? highest = n : highest;
        cout << n << endl;
        steps++;
    }
    cout << "It took " << steps << " steps to reach 1.\n";
    cout << "the highest number is " << highest << ".\n";
}