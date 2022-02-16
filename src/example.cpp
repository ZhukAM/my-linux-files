#include <iostream>
#include <vector>

using namespace std;
//typedef string(*fun)(int*, char**, double&);
string fun(int*, char**, double&);
void f(int, int) {}
const string& f1(const string& s){
    return s;
}

int main (){
    int** ap = new int*[5];
    //using fun = string(*)(int*, char**, double&);
    long long a;
    bool x = true;
    bool y = false;
    cin >> a;
    vector<int> v1;
    cout.setf(ios_base::fixed);
    cout.precision(0);
    v1.capacity();
    //double pi = M_PI;
    cout << static_cast<long long>(static_cast<float>(a)) - a  << '\n';
    //cout << ((a%b) + b)%b  << '\n';
    return 0;
}
