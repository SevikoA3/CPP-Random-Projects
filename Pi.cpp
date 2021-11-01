#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    unsigned long long total_point;
    double xpoint, ypoint, total_cpoint = 0, total_spoint = 0;
    cin >> total_point;
    srand(time(0));
    while(total_point--){
        xpoint = double(rand()) / RAND_MAX;
        ypoint = double(rand()) / RAND_MAX;
        if (sqrt(xpoint*xpoint + ypoint*ypoint) < 1){
            total_cpoint++;
        }
        total_spoint++;
    }
    cout << 4.0*(double(total_cpoint/total_spoint));
    return 0;
}